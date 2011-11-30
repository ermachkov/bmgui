#ifndef SPRITE_RESOURCE_H
#define SPRITE_RESOURCE_H

#include "Resource.h"

// Sprite resource class
class SpriteResource : public Resource
{
public:

	// Constructor
	SpriteResource(CL_Resource &resource);

	// Returns a list of resource dependencies
	virtual std::vector<std::string> getDependencies() const;

	// Returns a list of resource files
	virtual std::vector<std::string> getFileNames() const;

	// Returns true if the resource is loaded
	virtual bool isLoaded() const;

	// Loads the resource
	virtual void load();

	// Loads data file in the background thread
	virtual void loadInBackgroundThread(const std::string &fileName, CL_SharedPtr<Resource> &firstResource);

	// Loads data file in the main thread
	virtual void loadInMainThread(const std::string &fileName, CL_SharedPtr<Resource> &firstResource);

	// Returns a sprite object
	CL_Sprite getSprite() const;

private:

	// Sprite frame data used for the background loading
	struct Frame
	{
		// Constructor
		Frame(const std::string &fileName)
		: fileName(fileName)
		{
		}

		std::string     fileName;       // Relative file name
		CL_PixelBuffer  pixelBuffer;    // Pixel buffer object
		CL_Texture      texture;        // Texture object
	};

	// Filename -> Frame map type
	typedef std::map<std::string, Frame> FrameMap;

	CL_Resource     mResource;      // Resource object
	CL_Sprite       mSprite;        // Sprite object
	FrameMap        mFrames;        // List of the frames for background loading
};

#endif
