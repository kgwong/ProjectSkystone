#ifndef SCROLLING_SPRITE_RENDERER_H
#define SCROLLING_SPRITE_RENDERER_H

#include "SpriteRenderer.h"

class ScrollingSpriteRenderer : public SpriteRenderer
{
public:
	ScrollingSpriteRenderer(GameObject& owner, TextureSheet* textureSheet, int layerNum);
	virtual ~ScrollingSpriteRenderer();

	virtual void start(Level& level) {};
	virtual void update(Level& level);



private:
	SDL_Rect drawSrc1_;
	SDL_Rect drawSrc2_;
	SDL_Rect drawDest2_;
	Point oldCameraPos_;
	int layerNum_;
	int scale_;

	void setInitialRects();
	void checkDims();
	int findDelX();
	void advanceRects();
	void updateCamPos();
	bool rectAtEdge(int dx);
};

#endif //SCROLLING_SPRITE_RENDERER_H