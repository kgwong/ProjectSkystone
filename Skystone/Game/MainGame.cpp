#include "MainGame.h"

#include "Application/Log.h"
#include "Application/Path.h"
#include "GameObject/Builders/GameObjectBuilder.h"

#include "Game/GameTime.h"

#include "Resources/Resources.h"

#include "Application/Log.h"

MainGame::MainGame()
	:window_(Constants::GAME_TITLE, Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT),
	quit_(false)
{
	GameObjectBuilder::buildPlayer(player_);
	sceneManager_.setPlayer(&player_);

	updateCameraBounds();

	Resources::audioPlayer.init();
	Resources::audioPlayer.PlayMusic();
}


MainGame::~MainGame()
{
}

void MainGame::run()
{
	uint32_t msecBehind = Time::timeStep;
	uint32_t elapsed = 0;
	uint32_t prev = Time::getCurrentTime();
	while (!quit_ && !sceneManager_.hasQuitGame())
	{
		msecBehind += elapsed;
		processInput();
		while (msecBehind >= Time::timeStep) 
		{
			update();
			msecBehind -= Time::timeStep;
		}
		render(msecBehind / (float) Time::timeStep);
		elapsed = Time::getCurrentTime() - prev;
		Time::setElapsedRenderTime(elapsed);
		prev = Time::getCurrentTime();
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
				//LOG("INPUT") << "KEY PRESSED!!!!! key: " << e.key.keysym.sym << std::endl;
				//if (e.key.keysym.sym == SDLK_p)
				//	levelManager_.getLevelMap()->print();
				break;
			case SDL_KEYUP:
		     	if (e.key.keysym.sym == SDLK_1)//audio test ~ may use shared_ptrs now.
					Resources::audioPlayer.PlayClip("laser1");
				if (e.key.keysym.sym == SDLK_2)
					Resources::audioPlayer.PlayClip("laser2");
				break;
			case SDL_MOUSEMOTION:
				//LOG("INPUT") << "MOUSE MOVED!!!! pos (x: " << e.motion.x << ", y: " << e.motion.y << ")" << std::endl;
				break;
			case SDL_MOUSEBUTTONDOWN:
				LOG("INPUT") << "MousePressed(x = " << e.button.x + window_.getCamera().getPosX() <<
					", y = " << e.button.y + window_.getCamera().getPosY() << ")";
				break;
			default:
				break;
		}
		sceneManager_.handleInput(e);
	}
}

void MainGame::update()
{
	sceneManager_.update();
	updateCameraBounds();
}

void MainGame::render(float percBehind)
{
	SDL_RenderClear(window_.getRenderer());

	window_.getCamera().followObject(sceneManager_.getCameraFollowObject(), percBehind);
	sceneManager_.render(window_, percBehind);

	SDL_RenderPresent(window_.getRenderer());
}

void MainGame::updateCameraBounds()
{
	window_.getCamera().setLevelBounds(sceneManager_.getWidth(), sceneManager_.getHeight());
}
