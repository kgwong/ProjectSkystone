#include "InitSystems.h"
#include "MainGame.h"

int main(int argc, char* argv[])
{
	initAllSystems();
	MainGame().run();
	quitAllSystems();
	return 0;
}