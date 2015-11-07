#include "MainGame.h"

#include "Log.h"
#include "Path.h"

MainGame::MainGame()
	:_window(Constants::GAME_TITLE, Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT),
	textureLoader_(&_window),
	_player(&textureLoader_),
	_quit(false),
	_levelMap(10, 10),
	_currLevel(nullptr),
	_nextLevelID(-1),
	_levelLoader(this, &textureLoader_, &_levelMap),
	creator(&_window)
{
	_levelMap.addLevel(1, 2, 2, 1, 1);
	_levelMap.addLevel(2, 1, 2, 1, 3);
	_levelMap.addLevel(3, 2, 1, 0, 2);
	_levelMap.addLevel(4, 1, 1, 0 , 4);

	_currLevel = &_levelLoader.getLevel("Levels/LevelTest4",
										textureLoader_.getTextureSheet("Assets/TileSets/bw.png"),
										&creator);
	_currLevel->setPlayer(&_player, Point{ _currLevel->getLevelWidth() / 2, _currLevel->getLevelHeight() / 2 });
	_currLevel->startEntityComponents();
	_window.getCamera().setLevelBounds(_currLevel->getLevelWidth(), _currLevel->getLevelHeight());

	//_musicPlayer.loadSong(Path::getFullPath("Assets/Music/tempSong.wav"));
	//_musicPlayer.play();
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
			_currLevel = &_levelLoader.getLevel("Levels/LevelTest",
				textureLoader_.getTextureSheet("Assets/TileSets/bw.png"), &creator);
		}
		else if (_nextLevelID == 2)
		{
			_currLevel = &_levelLoader.getLevel("Levels/LevelTest2",
				textureLoader_.getTextureSheet("Assets/TileSets/bw.png"), &creator);
		}
		else if (_nextLevelID == 3)
		{
			_currLevel = &_levelLoader.getLevel("Levels/LevelTest3",
				textureLoader_.getTextureSheet("Assets/TileSets/bw.png"), &creator);
		}
		else if (_nextLevelID == 4)
		{
			_currLevel = &_levelLoader.getLevel("Levels/LevelTest4",
				textureLoader_.getTextureSheet("Assets/TileSets/bw.png"), &creator);
		}
		_currLevel->setPlayer(&_player, _newPlayerPosition);
		_currLevel->startEntityComponents();
		_window.getCamera().setLevelBounds(_currLevel->getLevelWidth(), _currLevel->getLevelHeight());

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
				//std::cout << "KEY PRESSED!!!!! key: " << e.key.keysym.sym << std::endl;
				_player.handleInput(e);
				if (e.key.keysym.sym == SDLK_p)
					_levelMap.print();
				break;
			case SDL_KEYUP:
				_player.handleInput(e);
			case SDL_MOUSEMOTION:
				//std::cout << "MOUSE MOVED!!!! pos (x: " << e.motion.x << ", y: " << e.motion.y << ")" << std::endl;
				break;
			case SDL_MOUSEBUTTONDOWN:
				//std::cout << "MOUSE PRESSED!!!! pos (x: " << e.button.x << ", y: " << e.button.y << ")" << std::endl;
				break;
			default:
				break;
		}
	}
	_player.handleInput2();
}

void MainGame::update()
{
	//SDL_Delay(100);
	_currLevel->update();
	changeLevel();
}

void MainGame::render()
{
	SDL_RenderClear(_window.getRenderer());

	_window.getCamera().followObject(_player);
	_currLevel->render();

	SDL_RenderPresent(_window.getRenderer());
}