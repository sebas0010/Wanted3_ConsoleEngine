#include <iostream>
#include "Engine.h"
#include "Game/Game.h"
// #include "Demo/DemoLevel.h"
#include "Level/SokobanLevel.h"
#include "Level/MenuLevel.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Game sokobanGame;
	sokobanGame.Run();
}