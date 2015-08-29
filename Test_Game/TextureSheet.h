#ifndef TEXTURE_SHEET_H
#define TEXTURE_SHEET_H

#include <SDL\SDL.h>

#include <vector>
#include <memory>

#include "SpritesheetInfo.h"

class GameWindow;

class TextureSheet
{
public:
	TextureSheet(GameWindow* winow, std::shared_ptr<SDL_Texture> texture, SpritesheetInfo* sInfo);
	virtual ~TextureSheet();

	GameWindow* getWindow();
	SDL_Texture* getTexture();

	SDL_Rect* getFrame(int index);
	SDL_Rect* getFull();

	int getNumFrames();

private: 
	GameWindow* window_;

	bool info_;

	SDL_Rect fullTexture_;
	std::shared_ptr<SDL_Texture> texture_;
	std::vector<SDL_Rect> frames_;
};

#endif //TEXTURE_SHEET_H
