#ifndef SCROLLING_TEXT_RENDERER_H
#define SCROLLING_TEXT_RENDERER_H

#include "Components/Render/TextRenderer.h"
#include <memory>
#include <vector>

class ScrollingTextRenderer : public RenderComponent
{
public:
	ScrollingTextRenderer(GameObject& owner, const std::string& relSciptPath);
	virtual ~ScrollingTextRenderer();
	
	virtual void render(GameWindow& window, float percBehind);

private:
	float timeSinceLastScroll_;
	std::vector<std::shared_ptr<GameObject>> lines_;

	void renderLines(GameWindow& window, float percBehind);
	void readScript(const std::string& relPath);
	void addLine(const std::string& line);
	bool needToScroll();
	void updateLine(GameWindow& window, float percBehind, std::shared_ptr<GameObject> go);
	bool remPred(std::shared_ptr<GameObject> go);
	void scroll();
};

#endif // SCROLLING_TEXT_RENDERER_H
