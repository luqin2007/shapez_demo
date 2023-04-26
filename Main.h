#pragma once

#include <graphics.h>
#include <conio.h>

#include "GameLogic.h"
#include "GameRenderer.h"

class Main
{
public:
	void run();
private:
	GameLogic game;
	GameRenderer renderer;
};

