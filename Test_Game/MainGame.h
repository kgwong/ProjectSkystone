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
#include "LevelMap.h"


class MainGame
{
public:
	static const int SCREEN_WIDTH  = 640;
	static const int SCREEN_HEIGHT = 480;

	static const int TILE_SIZE = 45;

	static const int BLOCK_WIDTH = SCREEN_WIDTH / TILE_SIZE;
	static const int BLOCK_HEIGHT = SCREEN_HEIGHT / TILE_SIZE;

	MainGame();
	~MainGame();

	void run();

	 void setNextLevel(int levelID, Point newPlayerPosition);
	 void changeLevel();

private:
	GameWindow _window;
	ResourceLocator _resourceLocator;

	MusicPlayer _musicPlayer;

	LevelMap _levelMap;
	Level _currLevel;
	int _nextLevelID;
	Point _newPlayerPosition;

	Player _player;

	bool _quit;

private: 
	void processInput();
	void update();
	void render();

};

#endif //MAIN_GAME_H

