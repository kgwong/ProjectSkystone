#include "MainGame.h"

#include "Resources.h"

#include <windows.h> // for "sleep"

const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

MainGame::MainGame()
	:gw("Test Game!", SCREEN_WIDTH, SCREEN_HEIGHT),
	player(&gw),
	quit(false),
	tileSet(&gw, "bw.png", 2, 40, 2, 1),
	currLevel(&gw, &tileSet)
{
	currLevel.load("LevelTest");
	currLevel.setPlayer(&player);

	musicPlayer.loadSong("tempSong.wav");
	musicPlayer.play();

	gw.camera.setLevelBounds(currLevel.getLevelWidth(), currLevel.getLevelHeight());

	player.setPos(SCREEN_WIDTH / 2 + 100, SCREEN_HEIGHT / 2);
}


MainGame::~MainGame()
{
}

void MainGame::run()
{
	while (!quit)
	{
		processInput();
		update();
		render();
	}
}

void MainGame::processInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch(e.type)
		{
			case SDL_QUIT:
				quit = true;
			case SDL_KEYDOWN:
				std::cout << "KEY PRESSED!!!!! key: " << e.key.keysym.sym << std::endl;
				player.handleInput(e);
				break;
			case SDL_MOUSEMOTION:
				std::cout << "MOUSE MOVED!!!! pos (x: " << e.motion.x << ", y: " << e.motion.y << ")" << std::endl;
				break;
			case SDL_MOUSEBUTTONDOWN:
				std::cout << "MOUSE PRESSED!!!! pos (x: " << e.button.x << ", y: " << e.button.y << ")" << std::endl;
				break;
			default:
				break;
		}
	}
	player.handleInput2();
}

void MainGame::update()
{
	Sleep(20);
	currLevel.update();
}

void MainGame::render()
{
	SDL_RenderClear(gw.renderer);

	gw.camera.followObject(player);
	currLevel.render();

	SDL_RenderPresent(gw.renderer);
}