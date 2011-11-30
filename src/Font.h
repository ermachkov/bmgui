#ifndef FONT_H
#define FONT_H

// Font class
class CFont
{
public:

	// Constructor
	CFont(const std::string &name);

	// Returns the size of the text string
	void getTextSize(std::string text, int *width = NULL, int *height = NULL);

	// Draws the text string
	void drawText(float x, float y, const std::string &text, float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);

private:

	CL_Font         mFont;      // Font object
	CL_FontMetrics  mMetrics;   // Font metrics
};

#endif
