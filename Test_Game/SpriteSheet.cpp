#include "SpriteSheet.h"

void calculateSpriteLocations(std::vector<SDL_Rect>& locations, SpritesheetInfo spritesheetInfo)
{
	for (int y = 0; (y < spritesheetInfo.perColumn) && (locations.size() < spritesheetInfo.num); ++y) 
	{
		for (int x = 0; (x < spritesheetInfo.perRow) && (locations.size() < spritesheetInfo.num); ++x) 
		{
			SDL_Rect rect; //
			rect.x = x * (spritesheetInfo.width + spritesheetInfo.padding);
			rect.y = y * (spritesheetInfo.height + spritesheetInfo.padding);
			rect.w = spritesheetInfo.width;
			rect.h = spritesheetInfo.height;
			locations.push_back(rect);
		}
	}
}
