#include "Precompiled.h"
#include "Font.h"
#include "FontResource.h"
#include "Graphics.h"
#include "ResourceManager.h"

CFont::CFont(const std::string &name)
{
	CL_SharedPtr<FontResource> resource = cl_dynamic_pointer_cast<FontResource>(ResourceManager::getSingleton().getResource(name));
	if (!resource)
		throw Exception(cl_format("Resource '%1' is not a font resource", name));
	if (!resource->isLoaded())
		throw Exception(cl_format("Font '%1' is not loaded", name));

	mFont = resource->getFont();
	mMetrics = mFont.get_font_metrics();
}

void CFont::getTextSize(std::string text, int *width, int *height)
{
	CL_Size size = mFont.get_text_size(Graphics::getSingleton().getWindow().get_gc(), text);
	*width = size.width;
	*height = size.height;
}

void CFont::drawText(float x, float y, const std::string &text, float r, float g, float b, float a)
{
	x = floor(x + 0.5f);
	y = floor(y + mMetrics.get_ascent() + 0.5f);
	mFont.draw_text(Graphics::getSingleton().getWindow().get_gc(), x, y, text, CL_Colorf(r * a, g * a, b * a, a));
}
