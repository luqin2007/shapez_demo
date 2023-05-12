#pragma once

#include <iostream>
#include <map>

#include <glad/glad.h>

#include "BorderDrawer.h"
#include "TextureInstanceDrawer.h"
#include "Atlas.h"
#include "GameWindow.h"
#include "Timer.h"
#include "GameMap.h"
#include "Resouces.h"
#include "Common.h"

using std::map;
using std::cout;
using std::cerr;
using std::endl;

class GameRenderer
{
public:
	void initialize();

	void update_env(const GameMap& map);

	void draw(const GameMap& map);

	void destroy();

private:
	vec2 edge_pos_[CELL_COUNT + 1], center_;
	float width_ = 0, height_ = 0, cell_size_ = 0, edge_pos_base_[CELL_COUNT + 1] = {0};
	GLuint buf_index_ = 0;

	BorderDrawer border_drawer_{CELL_COUNT * 2 + 2};
	TextureInstanceDrawer tex_drawer_{200};

	Atlas colors_{256, 72};
	Atlas shapes_{512, 72, true};
	Atlas icons_{512, 128};
	Atlas buildings_small_{2048, 192};
	Atlas buildings_middle_{1024, 2048, 384, 192};
	Atlas buildings_large_{1024, 768};

	void update_cell_size(const GameMap& map);

	void update_cell_position(const GameMap& map, bool force);

	void draw_cells();

	void draw_map_resources(const GameMap& map);

	void draw_building(const GameMap& map);

	void draw_ui();

	void draw_overlay();
};
