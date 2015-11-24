#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "GameObject.h"
#include "TextureLoader.h"
#include "SpriteRenderer.h"
#include <memory>

class Background :	public GameObject
{
public:
	Background(std::shared_ptr<SpriteRenderer> spriteRenderer);
	virtual ~Background();
	
	void render(Level& level);

private:
	std::shared_ptr<SpriteRenderer> spriteRenderer_;
};

#endif //BACKGRAOUND_H