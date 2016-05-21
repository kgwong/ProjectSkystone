#ifndef SCROLLING_TEXT_RENDERER_H
#define SCROLLING_TEXT_RENDERER_H

#include "Components/Render/TextRenderer.h"

class ScrollingTextRenderer : public TextRenderer
{
public:
	ScrollingTextRenderer(GameObject& owner, const std::string& relSciptPath);
	virtual ~ScrollingTextRenderer();
	
	virtual void render(GameWindow& window, float percBehind);

private:
	std::string text_;
	float timeSinceLastUpdate_;
};

#endif // SCROLLING_TEXT_RENDERER_H
