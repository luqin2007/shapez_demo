#pragma once

#include "GameLogic.h"
#include "GameRenderer.h"
#include "GameWindow.h"

class Main
{
public:
	void run();
private:
	GameWindow window_;
	GameLogic game_;
	GameRenderer renderer_;
};

