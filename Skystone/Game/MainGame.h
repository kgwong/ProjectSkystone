#ifndef MAIN_GAME_H
#define MAIN_GAME_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>

#include <iostream>
#include <string>

#include "Application/Errors.h"
#include "Application/GameWindow.h"
#include "Level/LevelManager.h"

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

private:
	GameWindow window_;

	GameObject player_;
	LevelManager levelManager_;

	bool quit_;

private: 
	void processInput();
	void update();
	void render();

	void updateCameraBounds();

};

#endif //MAIN_GAME_H

