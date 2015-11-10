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
#include "LevelManager.h"

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

private:
	GameWindow _window;
	TextureLoader textureLoader_;

	MusicPlayer _musicPlayer;

	Player _player;
	LevelManager levelManager_;

	bool _quit;

private: 
	void processInput();
	void update();
	void render();

	void updateCameraBounds();

};

#endif //MAIN_GAME_H

