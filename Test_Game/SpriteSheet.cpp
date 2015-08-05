#include "SpriteSheet.h"

void calculateSpriteLocations(std::vector<SDL_Rect>& locations, SpritesheetInfo spritesheetInfo)
{
	for (int r = 0; (r < spritesheetInfo.numRows) && (locations.size() < spritesheetInfo.num); ++r) 
	{
		for (int c = 0; (c < spritesheetInfo.numCols) && (locations.size() < spritesheetInfo.num); ++c) 
		{
			locations.push_back(SDL_Rect{ c * (spritesheetInfo.width + spritesheetInfo.padding),
										r * (spritesheetInfo.height + spritesheetInfo.padding),
										spritesheetInfo.width, 
										spritesheetInfo.height });
		}
	}
}
