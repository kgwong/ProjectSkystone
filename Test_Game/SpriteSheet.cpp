#include "SpriteSheet.h"

void calculateSpriteLocations(std::vector<SDL_Rect>& locations, SpritesheetInfo* sInfo)
{
	if (sInfo)
	{
		for (int r = 0; (r < sInfo->numRows) && (locations.size() < sInfo->num); ++r)
		{
			for (int c = 0; (c < sInfo->numCols) && (locations.size() < sInfo->num); ++c)
			{
				locations.push_back(SDL_Rect{ c * (sInfo->width + sInfo->padding),
											r * (sInfo->height + sInfo->padding),
											sInfo->width,
											sInfo->height });
			}
		}
	}
}
