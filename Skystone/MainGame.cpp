#include "MainGame.h"

#include "Log.h"
#include "Path.h"

MainGame::MainGame()
	:_window(Constants::GAME_TITLE, Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT),
	textureLoader_(&_window),
	_player(&textureLoader_),
	_quit(false),
	levelManager_(this, &textureLoader_, &_player)
{
	levelManager_.setTextureLoader(&textureLoader_);
	levelManager_.setPlayer(&_player);

	_window.getCamera().setLevelBounds(levelManager_.getCurrentLevel()->getLevelWidth(), levelManager_.getCurrentLevel()->getLevelHeight());

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
					;//_levelMap.print();
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
	levelManager_.getCurrentLevel()->update();
	levelManager_.changeLevel();
	if (levelManager_.getlevelWasChangedFlag())
	{
		updateCameraBounds();
	}
}

void MainGame::render()
{
	SDL_RenderClear(_window.getRenderer());

	_window.getCamera().followObject(_player);
	levelManager_.getCurrentLevel()->render();

	SDL_RenderPresent(_window.getRenderer());
}

void MainGame::updateCameraBounds()
{
	_window.getCamera().setLevelBounds(levelManager_.getCurrentLevel()->getLevelWidth(), levelManager_.getCurrentLevel()->getLevelHeight());
	levelManager_.setLevelWasChangedFlag(false);
}
