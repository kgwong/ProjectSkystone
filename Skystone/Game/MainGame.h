#ifndef MAIN_GAME_H
#define MAIN_GAME_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>

#include "Application/Errors.h"
#include "Application/GameWindow.h"
#include "Scene/SceneManager.h"

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

private:
	GameWindow window_;

	GameObject player_;
	SceneManager sceneManager_;

	bool quit_;

private: 
	void processInput();
	void update();
	void render(float percBehind);

	void updateCameraBounds();

};

#endif //MAIN_GAME_H

