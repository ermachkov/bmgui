#include "Precompiled.h"
#include "SpriteResource.h"
#include "Graphics.h"

SpriteResource::SpriteResource(CL_Resource &resource)
: mResource(resource)
{
	GAME_ASSERT(mResource.get_type() == "sprite");

	std::string basePath = mResource.get_manager().get_directory(mResource).get_file_system().get_path();
	for (CL_DomElement element = mResource.get_element().get_first_child_element(); !element.is_null(); element = element.get_next_sibling_element())
		if (element.get_tag_name() == "image")
		{
			std::string fileName = element.get_attribute("file");
			if (fileName.empty())
				throw Exception("Sprite '" + mResource.get_name() + "' has empty or missing 'file' attribute");
			mFrames.insert(std::make_pair(basePath + fileName, Frame(fileName)));
		}

	if (mFrames.empty())
		throw Exception("Sprite '" + mResource.get_name() + "' has no frames");
}

std::vector<std::string> SpriteResource::getDependencies() const
{
	return std::vector<std::string>();
}

std::vector<std::string> SpriteResource::getFileNames() const
{
	std::vector<std::string> fileNames;
	for (FrameMap::const_iterator it = mFrames.begin(); it != mFrames.end(); ++it)
		fileNames.push_back(it->first);
	return fileNames;
}

bool SpriteResource::isLoaded() const
{
	return !mSprite.is_null();
}

void SpriteResource::load()
{
	if (mSprite.is_null())
	{
		CL_ResourceManager manager = mResource.get_manager();
		mSprite = CL_Sprite(Graphics::getSingleton().getWindow().get_gc(), mResource.get_name(), &manager);
	}
}

void SpriteResource::loadInBackgroundThread(const std::string &fileName, CL_SharedPtr<Resource> &firstResource)
{
	FrameMap::iterator it = mFrames.find(fileName);
	GAME_ASSERT(it != mFrames.end());

	// load image into the pixel buffer (only for the first resource)
	if (this == firstResource.get())
	{
		if (it->second.pixelBuffer.is_null())
			it->second.pixelBuffer = CL_PixelBuffer(it->second.fileName, mResource.get_manager().get_directory(mResource));
	}
}

void SpriteResource::loadInMainThread(const std::string &fileName, CL_SharedPtr<Resource> &firstResource)
{
	FrameMap::iterator it = mFrames.find(fileName);
	GAME_ASSERT(it != mFrames.end());

	// convert previously loaded pixel buffer to the texture (only for the first resource)
	if (this == firstResource.get())
	{
		if (it->second.texture.is_null())
		{
			GAME_ASSERT(!it->second.pixelBuffer.is_null());
			it->second.texture = CL_Texture(Graphics::getSingleton().getWindow().get_gc(), it->second.pixelBuffer.get_size(), cl_rgba);
			it->second.texture.set_subimage(0, 0, it->second.pixelBuffer, CL_Rect(it->second.pixelBuffer.get_size()), 0);
			it->second.pixelBuffer = CL_PixelBuffer();
			CL_SharedGCData::add_texture(it->second.texture, it->second.fileName, mResource.get_manager().get_directory(mResource));
		}
	}
}

CL_Sprite SpriteResource::getSprite() const
{
	return mSprite;
}
