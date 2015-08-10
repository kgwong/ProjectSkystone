#include "MainGame.h"

#include <windows.h> // for "sleep"



MainGame::MainGame()
	:_window("Test Game!", SCREEN_WIDTH, SCREEN_HEIGHT),
	_resourceLocator(&_window),
	_player(&_resourceLocator),
	_quit(false),
	_currLevel(this, &_window, &_resourceLocator)
{
	changeLevel(1);

	_musicPlayer.loadSong(_resourceLocator.getFullPath("Assets/Music/tempSong.wav"));
	_musicPlayer.play();
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

void MainGame::changeLevel(int levelID)
{
	if (levelID == 1)
	{
		_currLevel = Level(this, &_window, &_resourceLocator);
		_currLevel.load(_resourceLocator.getFullPath("Levels/LevelTest"), _resourceLocator.getTileSet("Assets/TileSets/bw.png"));
		_currLevel.setPlayer(&_player);
	}
	else
	{
		_currLevel = Level(this, &_window, &_resourceLocator);
		_currLevel.load(_resourceLocator.getFullPath("Levels/LevelTest2"), _resourceLocator.getTileSet("Assets/TileSets/bw.png"));
		_currLevel.setPlayer(&_player);
	}
	_window.camera.setLevelBounds(_currLevel.getLevelWidth(), _currLevel.getLevelHeight());

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
	SDL_RenderClear(_window.renderer);

	_window.camera.followObject(_player);
	_currLevel.render();

	SDL_RenderPresent(_window.renderer);
}