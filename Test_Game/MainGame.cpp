#include "MainGame.h"

#include "Resources.h"

#include <windows.h> // for "sleep"

const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

MainGame::MainGame()
	:_gw("Test Game!", SCREEN_WIDTH, SCREEN_HEIGHT),
	_resourceLocator(&_gw),
	_player(&_gw, &_resourceLocator),
	_quit(false),
	_currLevel(&_gw, _resourceLocator.getTileSet("bw.png"), &_resourceLocator)
{
	_currLevel.load("LevelTest");
	_currLevel.setPlayer(&_player);

	_musicPlayer.loadSong("tempSong.wav");
	_musicPlayer.play();

	_gw.camera.setLevelBounds(_currLevel.getLevelWidth(), _currLevel.getLevelHeight());

	_player.setPos(SCREEN_WIDTH / 2 + 100, SCREEN_HEIGHT / 2);
}


MainGame::~MainGame()
{
}

void MainGame::run()
{
	while (!_quit)
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
				_quit = true;
			case SDL_KEYDOWN:
				std::cout << "KEY PRESSED!!!!! key: " << e.key.keysym.sym << std::endl;
				_player.handleInput(e);
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
	_player.handleInput2();
}

void MainGame::update()
{
	//Sleep(50);
	_currLevel.update();
}

void MainGame::render()
{
	SDL_RenderClear(_gw.renderer);

	_gw.camera.followObject(_player);
	_currLevel.render();

	SDL_RenderPresent(_gw.renderer);
}