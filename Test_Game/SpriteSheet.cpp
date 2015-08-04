#include "SpriteSheet.h"

void calculateSpriteLocations(std::vector<SDL_Rect>& locations, SpritesheetInfo spritesheetInfo)
{
	for (int r = 0; (r < spritesheetInfo.numRows) && (locations.size() < spritesheetInfo.num); ++r) 
	{
		for (int c = 0; (c < spritesheetInfo.numCols) && (locations.size() < spritesheetInfo.num); ++c) 
		{
			SDL_Rect rect; //
			rect.x = c * (spritesheetInfo.width + spritesheetInfo.padding);
			rect.y = r * (spritesheetInfo.height + spritesheetInfo.padding);
			rect.w = spritesheetInfo.width;
			rect.h = spritesheetInfo.height;
			locations.push_back(rect);
		}
	}
}
