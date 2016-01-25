#ifndef SCROLLING_SPRITE_RENDERER_H
#define SCROLLING_SPRITE_RENDERER_H

#include "Components/Render/RenderComponent.h"
#include "Resources/SpriteSheet.h"

class ScrollingSpriteRenderer : public RenderComponent
{
public:
	ScrollingSpriteRenderer(GameObject& owner, SpriteSheet* spriteSheet, int layerNum);
	virtual ~ScrollingSpriteRenderer();

	virtual void start(Level& level) {};
	virtual void render(GameWindow& gameWindow);



private:
	SpriteSheet* spriteSheet_;
	SDL_Rect drawSrc1_;
	SDL_Rect drawSrc2_;
	SDL_Rect drawDest1_;
	SDL_Rect drawDest2_;
	Point oldCameraPos_;
	int layerNum_;

	void checkDims();
	int findDelX(GameWindow& gameWindow);
	void advanceRects(GameWindow& gameWindow);
	void scrollNonZero(GameWindow& gameWindow);
	void scrollBoth(GameWindow& gameWindow);
	void updateCamPos(GameWindow& gameWindow);
};

#endif //SCROLLING_SPRITE_RENDERER_H