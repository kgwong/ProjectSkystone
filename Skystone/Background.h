#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "GameObject.h"
#include "TextureLoader.h"
#include "SpriteRenderer.h"
#include <memory>

class Background :	public GameObject
{
public:
	Background();
	virtual ~Background();

	virtual ObjectType getType() const; //TypeComponents

private:

};

#endif //BACKGRAOUND_H