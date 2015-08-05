#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <memory>

#include "GameWindow.h"
#include "SpritesheetInfo.h"

class Animation
{
public:
	Animation(GameWindow* window, std::shared_ptr<SDL_Texture> texture, 
		SpritesheetInfo spritesheetInfo);
	~Animation();

	void renderFrame(Point renderPosition, int frameIndex);
	
	int getWidth();
	int getHeight();

	int getNumFrames();

private:
	GameWindow* _window;

	std::shared_ptr<SDL_Texture> _texture;
	std::vector<SDL_Rect> _frames;

	int _numFrames;

	int _width;
	int _height;

	SDL_Rect _drawDestination;

	bool _valid;
};

#endif //ANIMATION_H

