#include "Application/InitSystems.h"
#include "Game/MainGame.h"
#include <iostream>
using namespace std;
#include "Application/Log.h"

int main(int argc, char* argv[])
{
	LOG("ERROR") << "here";
	initAllSystems();
	MainGame().run();
	quitAllSystems();
	return 0;
}