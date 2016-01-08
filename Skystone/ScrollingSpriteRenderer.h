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
	SDL_Rect drawSrcCopy_;
	SDL_Rect drawSrcLeft_;
	SDL_Rect drawDestLeft_;
	int layerNum_;
	Point oldCameraPos_;
	int scale_;

	void setInitialRects();
	void checkDims();
	int findDelX();
	void advanceRects();
	void updateCamPos();
	bool cameraValid();
};

#endif //SCROLLING_SPRITE_RENDERER_H