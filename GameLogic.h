#pragma once

#include "GameMap.h"

class GameLogic
{
public:
	void initialize(long long seed);

	void update();

	GameMap& map();
};
