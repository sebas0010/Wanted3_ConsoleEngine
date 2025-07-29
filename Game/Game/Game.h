#pragma once

#include "Engine.h"

class Game : public Engine
{
public:
	Game();
	static Game& Get();
private:
	static Game* instance;
};