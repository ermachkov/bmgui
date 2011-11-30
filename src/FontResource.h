#ifndef FONT_RESOURCE_H
#define FONT_RESOURCE_H

#include "Resource.h"

// Font resource class
class FontResource : public Resource
{
public:

	// Constructor
	FontResource(CL_Resource &resource);

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

	// Returns a font object
	CL_Font getFont() const;

private:

	CL_Resource     mResource;      // Resource object
	bool            mSpriteFont;    // Sprite/FreeType font flag
	CL_Font         mFont;          // Font object
	std::string     mSpriteName;    // Name of the sprite containing character glyphs
	std::string     mFileName;      // Path to the .ttf file
};

#endif
