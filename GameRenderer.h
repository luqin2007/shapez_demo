#pragma once

#include <iostream>
#include <map>

#include "BorderDrawer.h"
#include "FontDrawer.h"
#include "Atlas.h"
#include "GameMap.h"
#include "resouces.h"
#include "Common.h"
#include "TextureDrawer.h"
#include "ShapeDrawer.h"
#include "vec.h"

using std::map;
using std::cout;
using std::cerr;
using std::endl;

class GameRenderer
{
public:
	void initialize();

	void update(GameLogic& logic);

	void destroy();

private:
	Vec2 edge_pos_[CELL_COUNT + 1], center_;
	float width_ = 0, height_ = 0, cell_size_ = 0, edge_pos_base_[CELL_COUNT + 1] = {0};

	BorderDrawer map_border_drawer_{CELL_COUNT * 2 + 2};
	TextureDrawer tex_drawer_{200};
	ShapeDrawer shape_drawer_;
	// FontDrawer font_drawer_{ROOT / "font" / "MicrosoftYaHei.ttf"};

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
