#include "Precompiled.h"
#include "FontResource.h"
#include "Graphics.h"

FontResource::FontResource(CL_Resource &resource)
: mResource(resource), mSpriteFont(false)
{
	GAME_ASSERT(mResource.get_type() == "font");

	CL_DomElement element = mResource.get_element().named_item("bitmap").to_element();
	if (!element.is_null())
	{
		mSpriteFont = true;

		mSpriteName = element.get_attribute("glyphs");
		if (mSpriteName.empty())
			throw Exception(cl_format("Font '%1' has empty or missing 'glyphs' attribute", mResource.get_name()));

		return;
	}

	element = mResource.get_element().named_item("freetype").to_element();
	if (!element.is_null())
	{
		mSpriteFont = false;

		CL_String fileName = element.get_attribute("file");
		if (fileName.empty())
			throw Exception(cl_format("Font '%1' has empty or missing 'file' attribute", mResource.get_name()));
		mFileName = mResource.get_manager().get_directory(mResource).get_file_system().get_path() + fileName;

		return;
	}

	throw Exception(cl_format("Font '%1' has no 'bitmap' or 'freetype' child elements", mResource.get_name()));
}

std::vector<std::string> FontResource::getDependencies() const
{
	if (mSpriteFont)
		return std::vector<std::string>(1, mSpriteName);
	return std::vector<std::string>();
}

std::vector<std::string> FontResource::getFileNames() const
{
	if (!mSpriteFont)
		return std::vector<std::string>(1, mFileName);
	return std::vector<std::string>();
}

bool FontResource::isLoaded() const
{
	return !mFont.is_null();
}

void FontResource::load()
{
	if (mFont.is_null())
	{
		CL_ResourceManager manager = mResource.get_manager();
		if (mSpriteFont)
			mFont = CL_Font_Sprite(Graphics::getSingleton().getWindow().get_gc(), mResource.get_name(), &manager);
		else
			mFont = CL_Font_Freetype(mResource.get_name(), &manager);
	}
}

void FontResource::loadInBackgroundThread(const std::string &fileName, CL_SharedPtr<Resource> &firstResource)
{
	GAME_ASSERT(!mSpriteFont && fileName == mFileName);
	load();
}

void FontResource::loadInMainThread(const std::string &fileName, CL_SharedPtr<Resource> &firstResource)
{
	GAME_ASSERT(!mSpriteFont && fileName == mFileName);
}

CL_Font FontResource::getFont() const
{
	return mFont;
}
