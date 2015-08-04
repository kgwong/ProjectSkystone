#ifndef MAIN_GAME_H
#define MAIN_GAME_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>

#include <iostream>
#include <string>

#include "Errors.h"
#include "GameWindow.h"
#include "Player.h"
#include "MusicPlayer.h"
#include "Camera.h"
#include "TileSet.h"
#include "Level.h"
#include "ResourceLocator.h"


class MainGame
{
public:
	static const int SCREEN_WIDTH  = 640;
	static const int SCREEN_HEIGHT = 480;

	MainGame();
	~MainGame();

	void run();

private:
	GameWindow _window;
	ResourceLocator _resourceLocator;

	MusicPlayer _musicPlayer;
	Level _currLevel;

	Player _player;

	bool _quit;

private: 
	void processInput();
	void update();
	void render();

};

#endif //MAIN_GAME_H

