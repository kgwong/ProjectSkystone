#ifndef INTRO_SCENE_H
#define INTRO_SCENE_H

#include "Scene\Scene.h"
class IntroScene : public Scene
{
public:
	IntroScene();
	virtual ~IntroScene();

	virtual void onExit();
};

#endif // INTRO_SCENE_H