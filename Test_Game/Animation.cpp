#include "Animation.h"

#include "SpriteSheet.h"

Animation::Animation(GameWindow* window, std::shared_ptr<SDL_Texture> texture, 
					SpritesheetInfo spritesheetInfo)
	: _window(window),  _texture(texture),
	  _numFrames(spritesheetInfo.num), 
	  _width(spritesheetInfo.width), _height(spritesheetInfo.height),
	  _currFrame(0)
{
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

void Animation::renderFrame(int x, int y)
{
	Point cameraPos = _window->camera.getPos();
	_drawDestination.x = x - cameraPos.x;
	_drawDestination.y = y - cameraPos.y;
	SDL_RenderCopy(_window->renderer, _texture.get(), &_frames[_currFrame], &_drawDestination);
	nextFrame();
}

void Animation::nextFrame()
{
	if (++_currFrame >= _numFrames) 
		_currFrame = 0;
}


