#include "SpriteSheet.h"

#include "Application/Log.h"
#include <limits>

#include "SpriteSheetInfoReader.h"

SpriteSheet::SpriteSheet(std::shared_ptr<SDL_Texture> texture, const std::string& fullpath)
	: texture_(texture)
{
	SpritesheetInfoReader reader(fullpath);
	SpriteSheetInfo* info = reader.info();
	setFrames(info);
}

SDL_Texture* SpriteSheet::getTexture()
{
	return texture_.get();
}

SDL_Rect* SpriteSheet::getFrameRect(int index)
{
	return &frames_.at(index).rect;
}

int SpriteSheet::getFrameDuration(int index)
{
	return frames_.at(index).milliseconds;
}

int SpriteSheet::getNextIndex(int index)
{
	return (index + 1) % frames_.size();
}

int SpriteSheet::getNumFrames()
{
	return frames_.size();
}

void SpriteSheet::setFrames(SpriteSheetInfo* sInfo)
{
	//MAKE SURE FRAME TIME IS > 0
	if (sInfo)
	{
		for (int r = 0; (r < sInfo->numRows) && (frames_.size() < sInfo->num); ++r)
		{
			for (int c = 0; (c < sInfo->numCols) && (frames_.size() < sInfo->num); ++c)
			{
				SDL_Rect rect = SDL_Rect{ c * (sInfo->width + sInfo->padding),
										r * (sInfo->height + sInfo->padding),
										sInfo->width,
										sInfo->height };
				int milliseconds;
				if (sInfo->frameTimes.size() > 0)
				{
					milliseconds = sInfo->frameTimes[frames_.size()];
				}
				else
				{
					milliseconds = std::numeric_limits<int>::max();
				}
				frames_.push_back( Frame{ rect, milliseconds } );
			}
		}
	}

	if (frames_.size() == 0)
	{
		int w, h;
		SDL_QueryTexture(texture_.get(), NULL, NULL, &w, &h);
		frames_.push_back(Frame{ SDL_Rect{0, 0, w, h}, std::numeric_limits<int>::max() });
	}
}
