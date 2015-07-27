#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>

#include "GameWindow.h"
#include "Resources.h"
#include "SpritesheetInfo.h"

class Animation
{
public:
	Animation(GameWindow* window, std::shared_ptr<SDL_Texture> texture, 
		SpritesheetInfo spritesheetInfo); //change to smaller constructor.... read image data from a seperate file instead?
	~Animation();

	void renderFrame(int x, int y);
	
	int getWidth();
	int getHeight();

	int getNumFrames();

private:
	GameWindow* _window;

	std::shared_ptr<SDL_Texture> _texture;
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

