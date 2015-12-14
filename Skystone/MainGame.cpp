#include "MainGame.h"

#include "Log.h"
#include "Path.h"
#include "Level.h"

#include "GameOverException.h"
#include "TempGameOverScreen.h"

MainGame::MainGame()
	:window_(Constants::GAME_TITLE, Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT),
	textureLoader_(&window_),
	player_(&textureLoader_),
	quit_(false),
	levelManager_(&textureLoader_)
{
	levelManager_.setTextureLoader(&textureLoader_);
	levelManager_.setPlayer(&player_);
	levelManager_.initStartingLevel();

	updateCameraBounds();

	//musicPlayer_.loadSong(Path::getFullPath("Assets/Music/tempSong.wav"));
	//musicPlayer_.play();
}


MainGame::~MainGame()
{
}

void MainGame::run()
{
	while (!quit_)
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
				quit_ = true;
			case SDL_KEYDOWN:
				//std::cout << "KEY PRESSED!!!!! key: " << e.key.keysym.sym << std::endl;
				player_.handleInput(e);
				if (e.key.keysym.sym == SDLK_p)
					levelManager_.getLevelMap()->print();
				break;
			case SDL_KEYUP:
				player_.handleInput(e);
			case SDL_MOUSEMOTION:
				//std::cout << "MOUSE MOVED!!!! pos (x: " << e.motion.x << ", y: " << e.motion.y << ")" << std::endl;
				break;
			case SDL_MOUSEBUTTONDOWN:
				std::cout << "MousePressed(x = " << e.button.x + window_.getCamera().getPosX() << 
								", y = " << e.button.y + window_.getCamera().getPosY() << ")" << std::endl;
				break;
			default:
				break;
		}
	}
	player_.handleInput2();
}

void MainGame::update()
{
	try
	{
		levelManager_.getCurrentLevel()->update();
		if (levelManager_.changeLevelIfNecessary())
			updateCameraBounds();
	}
	catch (GameOverException& e)
	{
		while (!quit_)
		{
			SDL_Event event;
			while (SDL_PollEvent(&event)) { if (event.type == SDL_QUIT) quit_ = true; }
			TempGameOverScreen(&textureLoader_).render();
			SDL_Delay(100);
		}
	}
}

void MainGame::render()
{
	SDL_RenderClear(window_.getRenderer());

	window_.getCamera().followObject(player_);
	levelManager_.getCurrentLevel()->render(window_);

	SDL_RenderPresent(window_.getRenderer());
}

void MainGame::updateCameraBounds()
{
	window_.getCamera().setLevelBounds(levelManager_.getCurrentLevel()->getLevelWidth(), 
										levelManager_.getCurrentLevel()->getLevelHeight());
}
