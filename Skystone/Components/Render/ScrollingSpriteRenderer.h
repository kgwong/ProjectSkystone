#ifndef SCROLLING_SPRITE_RENDERER_H
#define SCROLLING_SPRITE_RENDERER_H

#include "Components/Render/RenderComponent.h"
#include "Resources/SpriteSheet.h"

class ScrollingSpriteRenderer : public RenderComponent
{
public:
	ScrollingSpriteRenderer(GameObject& owner, SpriteSheet* spriteSheet, int layerNum, bool scrollX=true, bool scrollY=false);
	virtual ~ScrollingSpriteRenderer();

	virtual void start(Scene& scene) {};
	virtual void render(GameWindow& gameWindow, float percBehind);



private:
	SpriteSheet* spriteSheet_;
	bool sx_, sy_;
	SDL_Rect tlS_, tlD_, trS_, trD_, blS_, blD_, brS_, brD_;
	Point oldCameraPos_;
	int layerNum_;
	int moveFreq_;

	void checkDims();
	void advanceRects(GameWindow& gameWindow);
	void scrollLargeSprite(GameWindow& gameWindow);
	void scrollQuads(GameWindow& gameWindow);
	int findXBound(Point currCam);
	int findYBound(Point currCam);
	void advanceQuadrant(SDL_Rect* src, SDL_Rect* dest, int xBound, int yBound, bool left, bool top);
	bool cameraChanged(GameWindow& gameWindow);
	int findDelX(GameWindow& gameWindow);
	int findDelY(GameWindow& gameWindow);
	void updateCamPos(GameWindow& gameWindow);
	void scrollHorizToBound(int xBound);
	void scrollVertToBound(int yBound);
};

#endif //SCROLLING_SPRITE_RENDERER_H