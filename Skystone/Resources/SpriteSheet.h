#ifndef SPRITE_SHEET_H
#define SPRITE_SHEET_H

#include <SDL\SDL.h>

#include <memory>
#include <vector>

#include "Application/Path.h"

#include "SpritesheetInfo.h"

class SpriteSheet
{
public:
	struct Frame
	{
		SDL_Rect rect;
		int milliseconds;
	};

	SpriteSheet(std::shared_ptr<SDL_Texture> texture, const std::string& fullpath);

	SDL_Texture* getTexture();
	SDL_Rect* getFrameRect(int index);

	int getFrameDuration(int index);
	int getNextIndex(int index);

	int getNumFrames();

private:
	std::shared_ptr<SDL_Texture> texture_;
	std::vector<Frame> frames_;

private:
	void setFrames(SpriteSheetInfo* sInfo);
};

#endif //SPRITE_SHEET_H