#ifndef SCROLLING_SPRITE_RENDERER_H
#define SCROLLING_SPRITE_RENDERER_H

#include "Components/Render/RenderComponent.h"
#include "Resources/SpriteSheet.h"
#include "Components/Render/ScrollingQuad.h"

class ScrollingSpriteRenderer : public RenderComponent
{
public:
	ScrollingSpriteRenderer(GameObject& owner, SpriteSheet* spriteSheet, int layerNum, bool scrollX=true, bool scrollY=false);
	virtual ~ScrollingSpriteRenderer();

	void initQuads();
	void setLayer(int layer);
	virtual void start(Scene& scene) {};
	virtual void render(GameWindow& gameWindow, float percBehind);

private:
	SpriteSheet* spriteSheet_;
	ScrollingQuad quads[N_QUADRANTS];
	bool sx_, sy_;
	int layerNum_;
	Point oldCamPos_;

	void checkDims();
	void advanceQuads(GameWindow& gameWindow);
	void renderQuads(GameWindow& gameWindow, float percBehind);
	int findXBound(Point currCam);
	int findYBound(Point currCam);
};

#endif //SCROLLING_SPRITE_RENDERER_H