#include "Animation.h"

#include "SpriteSheet.h"

Animation::Animation(GameWindow* window, std::shared_ptr<SDL_Texture> texture, 
					SpritesheetInfo spritesheetInfo)
	: _window(window),  _texture(texture),
	  _numFrames(spritesheetInfo.num), 
	  _width(spritesheetInfo.width), _height(spritesheetInfo.height),
	  _valid (true)
{
	if (spritesheetInfo.num == -1)
		_valid = false; //

	_drawDestination.w = _width;
	_drawDestination.h = _height;

	calculateSpriteLocations(_frames, spritesheetInfo);
}

Animation::~Animation()
{
}

int Animation::getWidth()
{
	return _width;
}

int Animation::getHeight()
{
	return _height;
}

int Animation::getNumFrames()
{
	return _numFrames;
}

void Animation::renderFrame(Point renderPosition, int frameIndex)
{
	Point cameraPos = _window->camera.getPos();
	_drawDestination.x = renderPosition.x - cameraPos.x;
	_drawDestination.y = renderPosition.y - cameraPos.y;
	SDL_RenderCopy(_window->renderer, _texture.get(), &_frames[frameIndex], &_drawDestination);
}

