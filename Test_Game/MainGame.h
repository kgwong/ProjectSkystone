#ifndef MAINGAME_H
#define MAINGAME_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>

#include <iostream>
#include <string>

#include "Errors.h"
#include "GameWindow.h"
#include "Sprite.h"
#include "Player.h"
#include "Animation.h"
#include "MusicPlayer.h"
#include "Camera.h"
#include "TileSet.h"
#include "Level.h"


class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();


private:
	GameWindow gw;
	MusicPlayer musicPlayer;
	TileSet tileSet;
	Level currLevel;

	Player player;

	bool quit;

private: 
	void processInput();
	void update();
	void render();

};

#endif //MAINGAME_H

