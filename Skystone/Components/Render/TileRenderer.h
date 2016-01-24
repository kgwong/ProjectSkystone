#ifndef TILE_RENDERER_H
#define TILE_RENDERER_H

#include "RenderComponent.h"
#include "Resources/Resources.h"

class GameWindow;

class TileRenderer : public RenderComponent
{
public:
	TileRenderer(GameObject& owner, SpriteSheet* spriteSheet, int tileNum);
	virtual ~TileRenderer();

	void render(GameWindow& gameWindow);

	virtual int getWidth();
	virtual int getHeight();

private:
	SpriteSheet* spriteSheet_;

	int tileNum_;

};

#endif //TILE_RENDERER_H