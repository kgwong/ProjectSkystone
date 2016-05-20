#ifndef SPRITE_H
#define SPRITE_H

#include "SpriteSheet.h"

struct Sprite 
{
	Sprite();
	Sprite(SpriteSheet* newSpriteSheet, int newIndex);

	int getWidth();
	int getHeight();

	SpriteSheet* spriteSheet;
	int index;
};

#endif //SPRITE_H
