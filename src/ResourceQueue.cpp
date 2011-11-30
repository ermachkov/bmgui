#include "Precompiled.h"
#include "ResourceQueue.h"
#include "Application.h"
#include "Resource.h"
#include "ResourceManager.h"

template<> ResourceQueue *Singleton<ResourceQueue>::mSingleton = NULL;

ResourceQueue::ResourceQueue()
: mLoadingActive(false), mCurrTime(0), mLastTime(0), mNumMainFiles(0), mLoadingProgress(1.0f)
{
	mSlotUpdate = Application::getSingleton().getSigUpdate().connect(this, &ResourceQueue::onUpdate);
}

ResourceQueue::~ResourceQueue()
{
	mStopThread.set(1);
	mThread.join();
}

void ResourceQueue::addResource(const std::string &name, const std::string &fileName)
{
	if (mLoadingActive)
		throw Exception("Cannot queue resources during the background loading");

	CL_SharedPtr<Resource> resource = ResourceManager::getSingleton().createResource(name, fileName);
	addResource(resource, fileName);
}

void ResourceQueue::addAllResources(const std::string &fileName)
{
	if (mLoadingActive)
		throw Exception("Cannot queue resources during the background loading");

	std::vector<CL_SharedPtr<Resource> > resources = ResourceManager::getSingleton().createAllResources(fileName);
	for (std::vector<CL_SharedPtr<Resource> >::iterator it = resources.begin(); it != resources.end(); ++it)
		addResource(*it, fileName);
}

void ResourceQueue::startLoading()
{
	if (mLoadingActive)
		throw Exception("Another background loading is already active");

	if (!mFiles.empty())
	{
		mLoadingActive = true;
		mCurrTime = 0;
		mLastTime = 0;
		mNumMainFiles = 0;
		mNumBackgroundFiles.set(0);
		mLoadingProgress = 0.0f;
		mError.set(0);
		mErrorMessage.clear();
		mStopThread.set(0);
		mThread.start(this);
	}
}

bool ResourceQueue::isLoadingActive() const
{
	return mLoadingActive;
}

float ResourceQueue::getLoadingProgress() const
{
	return mLoadingProgress;
}

void ResourceQueue::addResource(CL_SharedPtr<Resource> &resource, const std::string &fileName)
{
	if (!resource->isLoaded())
	{
		std::vector<std::string> dependencies = resource->getDependencies();
		for (std::vector<std::string>::const_iterator it = dependencies.begin(); it != dependencies.end(); ++it)
			addResource(*it, fileName);

		std::vector<std::string> fileNames = resource->getFileNames();
		for (std::vector<std::string>::const_iterator nameIt = fileNames.begin(); nameIt != fileNames.end(); ++nameIt)
		{
			FileList::iterator fileIt;
			for (fileIt = mFiles.begin(); fileIt != mFiles.end(); ++fileIt)
				if (fileIt->first == *nameIt)
					break;

			if (fileIt == mFiles.end())
				fileIt = mFiles.insert(mFiles.end(), std::make_pair(*nameIt, ResourceList()));

			if (std::find(fileIt->second.begin(), fileIt->second.end(), resource) == fileIt->second.end())
				fileIt->second.push_back(resource);
		}
	}
}

void ResourceQueue::onUpdate(int delta)
{
	if (mLoadingActive)
	{
		mCurrTime += delta;

		if (mError.get() != 0)
		{
			mThread.join();
			throw Exception(mErrorMessage);
		}

		// prepare all files processed in the background thread
		for (int numBackgroundFiles = mNumBackgroundFiles.get(); mNumMainFiles < numBackgroundFiles; ++mNumMainFiles)
		{
			FileList::iterator fileIt = mFiles.begin() + mNumMainFiles;
			for (ResourceList::iterator resIt = fileIt->second.begin(); resIt != fileIt->second.end(); ++resIt)
				(*resIt)->loadInMainThread(fileIt->first, fileIt->second.front());
			mLastTime = mCurrTime;
		}

		// estimate the loading progress from the following proportion:
		// mNumMainFiles / mFiles.size() = mLastTime / totalTime
		// totalTime = (mFiles.size() * mLastTime) / mNumMainFiles
		// progress = mCurrTime / totalTime = (mNumMainFiles * mCurrTime) / (mFiles.size() * mLastTime)
		int num = mNumMainFiles * mCurrTime;
		int denom = mFiles.size() * mLastTime;
		float progress = denom != 0 ? static_cast<float>(num) / denom : 0.0f;
		mLoadingProgress = cl_clamp(progress, mLoadingProgress, 1.0f);

		// check whether all files are loaded
		if (static_cast<unsigned>(mNumMainFiles) == mFiles.size())
		{
			mThread.join();

			for (FileList::iterator fileIt = mFiles.begin(); fileIt != mFiles.end(); ++fileIt)
				for (ResourceList::iterator resIt = fileIt->second.begin(); resIt != fileIt->second.end(); ++resIt)
					(*resIt)->load();

			mFiles.clear();
			mLoadingActive = false;
			mLoadingProgress = 1.0f;
		}
	}
}

void ResourceQueue::run()
{
	try
	{
		for (FileList::iterator fileIt = mFiles.begin(); fileIt != mFiles.end(); ++fileIt)
		{
			if (mStopThread.get() != 0)
				return;

			for (ResourceList::iterator resIt = fileIt->second.begin(); resIt != fileIt->second.end(); ++resIt)
				(*resIt)->loadInBackgroundThread(fileIt->first, fileIt->second.front());

			mNumBackgroundFiles.increment();
		}
	}
	catch (const std::exception &exception)
	{
		mErrorMessage = exception.what();
		mError.set(1);
	}
	catch (...)
	{
		mErrorMessage = "Unknown exception has been caught during the background loading";
		mError.set(1);
	}
}
