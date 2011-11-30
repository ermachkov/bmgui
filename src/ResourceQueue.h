#ifndef RESOURCE_QUEUE_H
#define RESOURCE_QUEUE_H

#include "Singleton.h"

class Resource;

// Class for loading game resources in the background thread
class ResourceQueue : public Singleton<ResourceQueue>, public CL_Runnable
{
public:

	// Constructor
	ResourceQueue();

	// Destructor
	virtual ~ResourceQueue();

	// Adds a resource from the specified resource file to the queue
	void addResource(const std::string &name, const std::string &fileName);

	// Adds all resources from the specified resource file to the queue
	void addAllResources(const std::string &fileName);

	// Starts the background loading
	void startLoading();

	// Returns true if the background loading is currently active
	bool isLoadingActive() const;

	// Returns the current background loading progress
	float getLoadingProgress() const;

private:

	// Resource list type
	typedef std::vector<CL_SharedPtr<Resource> > ResourceList;

	// File list type
	typedef std::vector<std::pair<std::string, ResourceList> > FileList;

	// Adds a resource to the queue
	void addResource(CL_SharedPtr<Resource> &resource, const std::string &fileName);

	// Update event handler
	void onUpdate(int delta);

	// Background thread function
	virtual void run();

	FileList                mFiles;                 // File queue
	CL_Thread               mThread;                // Background thread object
	CL_Slot                 mSlotUpdate;            // Update event slot
	bool                    mLoadingActive;         // Background loading flag
	int                     mCurrTime;              // Current time of the background loading
	int                     mLastTime;              // Time of the last file prepared in the main thread
	int                     mNumMainFiles;          // Number of files prepared in the main thread
	CL_InterlockedVariable  mNumBackgroundFiles;    // Number of files prepared in the background thread
	float                   mLoadingProgress;       // Current loading progress
	CL_InterlockedVariable  mError;                 // Background loading error flag
	std::string             mErrorMessage;          // Background loading error message
	CL_InterlockedVariable  mStopThread;            // Background thread stop flag
};

#endif
