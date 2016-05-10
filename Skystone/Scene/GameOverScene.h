#ifndef GAME_OVER_SCENE
#define GAME_OVER_SCENE

#include "Scene.h"

class GameOverScene : public Scene
{
public:
	GameOverScene();
	virtual ~GameOverScene();

	virtual void onEnter();
};

#endif // GAME_OVER_SCENE
