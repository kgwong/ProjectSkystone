#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include "Resources/SpriteSheet.h"
#include "Resources/Sprite.h"

#include "RenderComponent.h"
#include "GameTypes/Axis.h"

#include <string>

class SpriteRenderer : public RenderComponent
{
public:
	SpriteRenderer(GameObject& owner, const std::string& relPath);
	SpriteRenderer(GameObject& owner, SpriteSheet* spriteSheet);
	virtual ~SpriteRenderer();

	void flip(Axis axis);
	void setFlipHorz(bool value);
	void setFlipVert(bool value);

	void setRotation(double degrees);

	SpriteSheet* getSpriteSheet();

	void setSpriteSheet(const std::string& relPath);
	void setSpriteSheet(SpriteSheet* spriteSheet);
	void setSpriteIndex(int index);
	void setSprite(Sprite sprite);

	void render(GameWindow& gameWindow, float percBehind);

	virtual int getWidth();
	virtual int getHeight();

private:
	Sprite sprite_;

	bool flipHorz_, flipVert_; 
	double rotationDegrees_;

private:
	SDL_RendererFlip determineFinalFlip();
};

#endif //SPRITE_RENDERER_H