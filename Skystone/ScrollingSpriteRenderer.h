#ifndef SCROLLING_SPRITE_RENDERER_H
#define SCROLLING_SPRITE_RENDERER_H

/*#include "SpriteRenderer.h"

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

	void checkDims();
	int findDelX();
	void advanceRects();
	void scrollNonZero();
	void scrollBoth();
	void updateCamPos();
};
*/
#endif //SCROLLING_SPRITE_RENDERER_H