#include "Animation.h"

#include "SpriteSheet.h"

Animation::Animation(GameWindow* window, const std::string& filepath, 
					int numFrames, int frameWidth, int frameHeight,
					int framesPerRow, int framesPerColumn, 
					int padding)
	: _window(window),  
	  _numFrames(numFrames), 
	  _width(frameWidth), _height(frameHeight),
	  _currFrame(0)
{
	_image = loadTexture(_window->renderer, filepath);

	_drawDestination.w = frameWidth;
	_drawDestination.h = frameHeight;

	calculateSpriteLocations(_frames, numFrames, frameWidth, frameHeight, framesPerRow, framesPerColumn, padding);
}


Animation::~Animation()
{
	SDL_DestroyTexture(_image);
}

int Animation::getWidth()
{
	return _width;
}

int Animation::getHeight()
{
	return _height;
}

void Animation::renderFrame(int x, int y)
{
	Point cameraPos = _window->camera.getPos();
	_drawDestination.x = x - cameraPos.x;
	_drawDestination.y = y - cameraPos.y;
	SDL_RenderCopy(_window->renderer, _image, &_frames[_currFrame], &_drawDestination);
	nextFrame();
}

void Animation::nextFrame()
{
	if (++_currFrame >= _numFrames) 
		_currFrame = 0;
}


