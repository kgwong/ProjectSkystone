#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "Scene.h"

class MainMenu : public Scene
{
public:
	MainMenu();
	virtual ~MainMenu();

	virtual void onEnter();
};

#endif // MAIN_MENU_H
