#ifndef SCROLLING_TEXT_LINE_H
#define SCROLLING_TEXT_LINE_H

#include "Components/Render/TextRenderer.h"

#define PAD_X 100 
#define PAD_Y 2

class ScrollingTextLine : public TextRenderer
{
public:
	ScrollingTextLine(GameObject& owner, int lineNumber, const std::string& text);
	virtual ~ScrollingTextLine();

	bool finished();
	void scroll();
	
private:
	int lineNumber_;
	int width_, height_;

	void init();
	void setTextDims();
	void checkDims();
};

#endif // SCROLLING_TEXT_LINE_H