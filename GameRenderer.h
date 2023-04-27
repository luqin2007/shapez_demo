#pragma once

#include <cmath>
#include <map>

#include "HiEasyX.h"
#include "GameMap.h"

using namespace std;

class GameRenderer
{
public:
	void initialize();

	void update_env();

	void draw_map(const GameMap& map);

	void draw_building(const GameMap& map);

	void draw_ui();

	void draw_overlay();

private:
	hiex::Canvas canvas_;
	int width_ = 0, height_ = 0;
	ivec2 edge_pos_[101];

	int cell_size_ = 0;
	map<string, IMAGE> images_, zoomed_images_;

	void resize_images();
};
