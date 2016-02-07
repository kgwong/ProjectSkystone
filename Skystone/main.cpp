#include "Application/InitSystems.h"
#include "Game/MainGame.h"

int main(int argc, char* argv[])
{
	initAllSystems();
	MainGame().run();
	quitAllSystems();
	return 0;
}