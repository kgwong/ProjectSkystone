#include "MainGame.h"

#include <windows.h> // for "sleep"



MainGame::MainGame()
	:_window("Test Game!", SCREEN_WIDTH, SCREEN_HEIGHT),
	_resourceLocator(&_window),
	_player(&_resourceLocator),
	_quit(false),
	_levelMap(10, 10),
	_currLevel(this, &_window, &_resourceLocator, &_levelMap),
	_nextLevelID(-1)
{
	_levelMap.addLevel(1, 2, 2, 1, 1);
	_levelMap.addLevel(2, 1, 2, 1, 3);
	_levelMap.addLevel(3, 2, 1, 0, 2);

	_currLevel = Level(this, &_window, &_resourceLocator, &_levelMap);
	_currLevel.load(_resourceLocator.getFullPath("Levels/LevelTest"), _resourceLocator.getTileSet("Assets/TileSets/bw.png"));
	_currLevel.setPlayer(&_player, Point{ _currLevel.getLevelWidth() / 2, _currLevel.getLevelHeight() / 2 });
	_window.camera.setLevelBounds(_currLevel.getLevelWidth(), _currLevel.getLevelHeight());

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

void MainGame::setNextLevel(int levelID, Point newPlayerPosition)
{
	_nextLevelID = levelID;
	_newPlayerPosition = newPlayerPosition;
}

void MainGame::changeLevel()
{
	if (_nextLevelID != -1)
	{
		if (_nextLevelID == 1)
		{
			_currLevel = Level(this, &_window, &_resourceLocator, &_levelMap);
			_currLevel.load(_resourceLocator.getFullPath("Levels/LevelTest"), _resourceLocator.getTileSet("Assets/TileSets/bw.png"));
		}
		else if (_nextLevelID == 2)
		{
			_currLevel = Level(this, &_window, &_resourceLocator, &_levelMap);
			_currLevel.load(_resourceLocator.getFullPath("Levels/LevelTest2"), _resourceLocator.getTileSet("Assets/TileSets/bw.png"));
		}
		else if (_nextLevelID == 3)
		{
			_currLevel = Level(this, &_window, &_resourceLocator, &_levelMap);
			_currLevel.load(_resourceLocator.getFullPath("Levels/LevelTest3"), _resourceLocator.getTileSet("Assets/TileSets/bw.png"));
		}
		_currLevel.setPlayer(&_player, _newPlayerPosition);
		_window.camera.setLevelBounds(_currLevel.getLevelWidth(), _currLevel.getLevelHeight());

		_nextLevelID = -1;
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
				if (e.key.keysym.sym == SDLK_p)
					_levelMap.print();
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
	changeLevel();
}

void MainGame::render()
{
	SDL_RenderClear(_window.renderer);

	_window.camera.followObject(_player);
	_currLevel.render();

	SDL_RenderPresent(_window.renderer);
}