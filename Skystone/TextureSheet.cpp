#include "TextureSheet.h"

#include "SpriteSheet.h"

#include <iostream>

TextureSheet::TextureSheet(GameWindow* window, 
	std::shared_ptr<SDL_Texture> texture, 
	SpritesheetInfo* sInfo)
	:window_(window),
	texture_(texture),
	info_(sInfo == nullptr),
	fullTexture_{ 0,0,0,0 }
{
	calculateSpriteLocations(frames_, sInfo);
	SDL_QueryTexture(texture_.get(), NULL, NULL, &fullTexture_.w, &fullTexture_.h);
}

TextureSheet::~TextureSheet()
{
}

GameWindow* TextureSheet::getWindow()
{
	return window_;
}

SDL_Texture* TextureSheet::getTexture()
{
	return texture_.get();
}

SDL_Rect* TextureSheet::getFrame(int index)
{
	return info_ ? &frames_[index] : getFull();
}

SDL_Rect * TextureSheet::getFull()
{
	return &fullTexture_;
}

int TextureSheet::getNumFrames()
{
	return frames_.size();
}
