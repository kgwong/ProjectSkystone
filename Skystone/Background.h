#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "GameObject.h"
#include "TextureLoader.h"
#include "SpriteRenderer.h"

class Background :	public GameObject
{
public:
	Background(TextureLoader* textureLoader);
	virtual ~Background();
	
	void render(Level& level);

private:
	SpriteRenderer* spriteRenderer_;
};

#endif //BACKGRAOUND_H