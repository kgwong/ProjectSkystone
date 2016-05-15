#ifndef SCROLLING_QUADS_H
#define SCROLLING_QUADS_H

#include "Components/Render/RenderComponent.h"
#include "GameTypes/Quadrant.h"

#define N_QUADRANTS 4

class SpriteSheet;

class ScrollingQuad : public RenderComponent
{
public:
	ScrollingQuad(GameObject& owner, SpriteSheet* spriteSheet);
	~ScrollingQuad();
	
	void setQuadrant(Quadrant quadrant);
	void advance(int xBound, int yBound);
	virtual void render(GameWindow& gameWindow, float percBehind);

private:
	SpriteSheet* spriteSheet_;
	Quadrant quadrant_;
	SDL_Rect src_, dest_;
};

#endif //SCROLLING_QUADS_H
