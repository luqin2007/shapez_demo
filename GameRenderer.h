#pragma once
#include "Main.h"

class GameRenderer
{
public:

	void initialize();

	void update_env();

	void draw_map(const GameMap& map);

	void draw_ui();

	void draw_overlay();
};

