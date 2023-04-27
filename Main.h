#pragma once

#include <conio.h>

#include "HiEasyX.h"

#include "GameLogic.h"
#include "GameRenderer.h"

class Main
{
public:
	void run();
private:
	GameLogic game_ = GameLogic();
	GameRenderer renderer_ = GameRenderer();
};

