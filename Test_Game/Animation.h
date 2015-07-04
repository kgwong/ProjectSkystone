#ifndef ANIMATION_H
#define ANIMATION_H

#include "GameWindow.h"
#include "Resources.h"

#include <vector>

class Animation
{
public:
	Animation(GameWindow* window, const std::string& filepath, 
		int numFrames, int width, int height, 
		int framesPerRow, int framesPerColumn, 
		int padding = 0); //change to smaller constructor.... read image data from a seperator file instead?
	~Animation();

	void renderFrame(int x, int y);
	
	int getWidth();
	int getHeight();

private:
	GameWindow* _window;

	SDL_Texture* _image;
	std::vector<SDL_Rect> _frames;

	int _numFrames;
	int _currFrame;

	int _width;
	int _height;

	SDL_Rect _drawDestination;

private:
	void nextFrame();
};

#endif //ANIMATION_H

