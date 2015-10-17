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
#include "Level.h"
#include "TextureLoader.h"
#include "LevelMap.h"
#include "LevelLoader.h"

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

	 void setNextLevel(int levelID, Point newPlayerPosition);
	 void changeLevel();

private:
	GameWindow _window;
	TextureLoader textureLoader_;

	MusicPlayer _musicPlayer;

	TileCreator creator;//temporary

	LevelLoader _levelLoader;
	LevelMap _levelMap;
	Level* _currLevel;
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

