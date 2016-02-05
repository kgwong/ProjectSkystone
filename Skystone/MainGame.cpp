#include "MainGame.h"

#include "Log.h"
#include "Path.h"
#include "Level/Level.h"

#include "GameOverException.h"
#include "Game/GameTime.h"

#include "Resources/Resources.h"

MainGame::MainGame()
	:window_(Constants::GAME_TITLE, Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT),
	quit_(false)
{
	GameObjectBuilder::buildPlayer(player_);
	levelManager_.setPlayer(&player_);
	levelManager_.initStartingLevel();

	updateCameraBounds();

	Resources::audioPlayer.init();
	Resources::audioPlayer.PlayMusic();
}


MainGame::~MainGame()
{
}

void MainGame::run()
{
	uint32_t prev = Time::getCurrentTime();
	uint32_t msecBehind = 0;
	while (!quit_)
	{
		uint32_t current = Time::getCurrentTime();
		uint32_t elapsed = current - prev;
		prev = current;
		msecBehind += elapsed;
		processInput();
		// while (lag >= step) {update; msecBehind -= step;}
		update();
		// render(msecBehind/step);
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
				if (e.key.keysym.sym == SDLK_p)
					levelManager_.getLevelMap()->print();
				break;
			case SDL_KEYUP:
		     	if (e.key.keysym.sym == SDLK_1)//audio test ~ may use shared_ptrs now.
					Resources::audioPlayer.PlayClip("laser1");
				if (e.key.keysym.sym == SDLK_2)
					Resources::audioPlayer.PlayClip("laser2");
				break;
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
		levelManager_.getCurrentLevel()->handleInput(e);
	}
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
			std::cout << "GAME OVER" << std::endl;
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
