#include "SpriteSheet.h"

void calculateSpriteLocations(std::vector<SDL_Rect>& locations, 
								int numSprites,
								int spriteWidth,
								int spriteHeight,
								int spritesPerRow,
								int spritesPerColumn,
								int padding)
{
	for (int y = 0; y < spritesPerColumn && locations.size() < numSprites; ++y)
	{
		for (int x = 0; x < spritesPerRow && locations.size() < numSprites; ++x)
		{
			SDL_Rect rect; //
			rect.x = x * (spriteWidth + padding);
			rect.y = y * (spriteHeight + padding);
			rect.w = spriteWidth;
			rect.h = spriteHeight;
			locations.push_back(rect);
		}
	}
}