#include "GameRenderer.h"

#include <glad/glad.h>

#include "GameLogic.h"
#include "GameWindow.h"
#include "Timer.h"

void GameRenderer::initialize()
{
	glClearColor(0.99f, 0.99f, 0.98f, 1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	cout << "GameRenderer initializing..." << endl;

	cout << "Initialize font..." << endl;
	// font_drawer_.initialize();

	cout << "Initialize drawers..." << endl;
	map_border_drawer_.initialize();
	tex_drawer_.initialize();
	shape_drawer_.initialize();

	cout << "Initialize image atlas..." << endl;
	colors_.initialize();
	colors_ << ROOT / "image" / "colors" / "blue.png"
		<< ROOT / "image" / "colors" / "cyan.png"
		<< ROOT / "image" / "colors" / "green.png"
		<< ROOT / "image" / "colors" / "purple.png"
		<< ROOT / "image" / "colors" / "red.png"
		<< ROOT / "image" / "colors" / "uncolored.png"
		<< ROOT / "image" / "colors" / "white.png"
		<< ROOT / "image" / "colors" / "yellow.png";
	glGenerateMipmap(GL_TEXTURE_2D);

	shapes_.initialize();
	shapes_ << ROOT / "image" / "shapes" / "circle_blue.png"
		<< ROOT / "image" / "shapes" / "circle_cyan.png"
		<< ROOT / "image" / "shapes" / "circle_green.png"
		<< ROOT / "image" / "shapes" / "circle_purple.png"
		<< ROOT / "image" / "shapes" / "circle_red.png"
		<< ROOT / "image" / "shapes" / "circle_uncolored.png"
		<< ROOT / "image" / "shapes" / "circle_white.png"
		<< ROOT / "image" / "shapes" / "circle_yellow.png"
		<< ROOT / "image" / "shapes" / "rect_blue.png"
		<< ROOT / "image" / "shapes" / "rect_cyan.png"
		<< ROOT / "image" / "shapes" / "rect_green.png"
		<< ROOT / "image" / "shapes" / "rect_purple.png"
		<< ROOT / "image" / "shapes" / "rect_red.png"
		<< ROOT / "image" / "shapes" / "rect_uncolored.png"
		<< ROOT / "image" / "shapes" / "rect_white.png"
		<< ROOT / "image" / "shapes" / "rect_yellow.png"
		<< ROOT / "image" / "shapes" / "star_blue.png"
		<< ROOT / "image" / "shapes" / "star_cyan.png"
		<< ROOT / "image" / "shapes" / "star_green.png"
		<< ROOT / "image" / "shapes" / "star_purple.png"
		<< ROOT / "image" / "shapes" / "star_red.png"
		<< ROOT / "image" / "shapes" / "star_uncolored.png"
		<< ROOT / "image" / "shapes" / "star_white.png"
		<< ROOT / "image" / "shapes" / "star_yellow.png";
	glGenerateMipmap(GL_TEXTURE_2D);

	icons_.initialize();
	icons_ << ROOT / "image" / "building_icons" / "balancer.png"
		<< ROOT / "image" / "building_icons" / "belt.png"
		<< ROOT / "image" / "building_icons" / "block.png"
		<< ROOT / "image" / "building_icons" / "cutter.png"
		<< ROOT / "image" / "building_icons" / "miner.png"
		<< ROOT / "image" / "building_icons" / "mixer.png"
		<< ROOT / "image" / "building_icons" / "painter.png"
		<< ROOT / "image" / "building_icons" / "rotater.png"
		<< ROOT / "image" / "building_icons" / "stacker.png"
		<< ROOT / "image" / "building_icons" / "trash.png"
		<< ROOT / "image" / "building_icons" / "underground_belt.png";
	glGenerateMipmap(GL_TEXTURE_2D);

	buildings_small_.initialize();
	buildings_small_ << ROOT / "image" / "buildings" / "belt_left_blue.png"
		<< ROOT / "image" / "buildings" / "belt_right_blue.png"
		<< ROOT / "image" / "buildings" / "belt_top_blue.png"
		<< ROOT / "image" / "buildings" / "forward_0.png"
		<< ROOT / "image" / "buildings" / "forward_1.png"
		<< ROOT / "image" / "buildings" / "forward_2.png"
		<< ROOT / "image" / "buildings" / "forward_3.png"
		<< ROOT / "image" / "buildings" / "forward_4.png"
		<< ROOT / "image" / "buildings" / "forward_5.png"
		<< ROOT / "image" / "buildings" / "forward_6.png"
		<< ROOT / "image" / "buildings" / "forward_7.png"
		<< ROOT / "image" / "buildings" / "forward_8.png"
		<< ROOT / "image" / "buildings" / "forward_9.png"
		<< ROOT / "image" / "buildings" / "forward_10.png"
		<< ROOT / "image" / "buildings" / "forward_11.png"
		<< ROOT / "image" / "buildings" / "forward_12.png"
		<< ROOT / "image" / "buildings" / "forward_13.png"
		<< ROOT / "image" / "buildings" / "left_0.png"
		<< ROOT / "image" / "buildings" / "left_1.png"
		<< ROOT / "image" / "buildings" / "left_2.png"
		<< ROOT / "image" / "buildings" / "left_3.png"
		<< ROOT / "image" / "buildings" / "left_4.png"
		<< ROOT / "image" / "buildings" / "left_5.png"
		<< ROOT / "image" / "buildings" / "left_6.png"
		<< ROOT / "image" / "buildings" / "left_7.png"
		<< ROOT / "image" / "buildings" / "left_8.png"
		<< ROOT / "image" / "buildings" / "left_9.png"
		<< ROOT / "image" / "buildings" / "left_10.png"
		<< ROOT / "image" / "buildings" / "left_11.png"
		<< ROOT / "image" / "buildings" / "left_12.png"
		<< ROOT / "image" / "buildings" / "left_13.png"
		<< ROOT / "image" / "buildings" / "miner.png"
		<< ROOT / "image" / "buildings" / "miner_blue.png"
		<< ROOT / "image" / "buildings" / "miner-chainable.png"
		<< ROOT / "image" / "buildings" / "right_0.png"
		<< ROOT / "image" / "buildings" / "right_1.png"
		<< ROOT / "image" / "buildings" / "right_2.png"
		<< ROOT / "image" / "buildings" / "right_3.png"
		<< ROOT / "image" / "buildings" / "right_4.png"
		<< ROOT / "image" / "buildings" / "right_5.png"
		<< ROOT / "image" / "buildings" / "right_6.png"
		<< ROOT / "image" / "buildings" / "right_7.png"
		<< ROOT / "image" / "buildings" / "right_8.png"
		<< ROOT / "image" / "buildings" / "right_9.png"
		<< ROOT / "image" / "buildings" / "right_10.png"
		<< ROOT / "image" / "buildings" / "right_11.png"
		<< ROOT / "image" / "buildings" / "right_12.png"
		<< ROOT / "image" / "buildings" / "right_13.png"
		<< ROOT / "image" / "buildings" / "rotater.png"
		<< ROOT / "image" / "buildings" / "rotater_blue.png"
		<< ROOT / "image" / "buildings" / "trash.png"
		<< ROOT / "image" / "buildings" / "trash_blue.png"
		<< ROOT / "image" / "buildings" / "underground_belt_entry.png"
		<< ROOT / "image" / "buildings" / "underground_belt_entry_blue.png"
		<< ROOT / "image" / "buildings" / "underground_belt_exit.png"
		<< ROOT / "image" / "buildings" / "underground_belt_exit_blue.png";
	glGenerateMipmap(GL_TEXTURE_2D);

	buildings_middle_.initialize();
	buildings_middle_ << ROOT / "image" / "buildings" / "balancer.png"
		<< ROOT / "image" / "buildings" / "balancer_blue.png"
		<< ROOT / "image" / "buildings" / "cutter.png"
		<< ROOT / "image" / "buildings" / "cutter_blue.png"
		<< ROOT / "image" / "buildings" / "mixer.png"
		<< ROOT / "image" / "buildings" / "mixer_blue.png"
		<< ROOT / "image" / "buildings" / "painter.png"
		<< ROOT / "image" / "buildings" / "painter_blue.png"
		<< ROOT / "image" / "buildings" / "stacker.png"
		<< ROOT / "image" / "buildings" / "stacker_blue.png";
	glGenerateMipmap(GL_TEXTURE_2D);

	buildings_large_.initialize();
	buildings_large_ << ROOT / "image" / "buildings" / "hub.png";
	glGenerateMipmap(GL_TEXTURE_2D);

	cout << "GameRenderer initialize finished." << endl;
}

void GameRenderer::update(GameLogic& logic)
{
	glClear(GL_COLOR_BUFFER_BIT);

	if (!feq(width_, current_window->width()) && !feq(height_, current_window->height()))
	{
		width_ = current_window->width();
		height_ = current_window->height();
		AbstractDrawer::resize(width_, height_);
	}

	update_cell_size(logic.map());
	update_cell_position(logic.map(), false);

	draw_cells();
	draw_map_resources(logic.map());
	draw_building(logic.map());
	log_error("draw_building");
	draw_ui();
	log_error("draw_ui");
	draw_overlay();
	log_error("draw_overlay");
}

void GameRenderer::destroy()
{
	map_border_drawer_.destroy();
	tex_drawer_.destroy();
	// font_drawer_.destroy();
	shape_drawer_.destroy();
	AbstractDrawer::destroy_static();

	colors_.destroy();
	shapes_.destroy();
	icons_.destroy();
	buildings_small_.destroy();
	buildings_middle_.destroy();
	buildings_large_.destroy();
}

void GameRenderer::update_cell_size(const GameMap& map)
{
	if (!feq(cell_size_, map.cell_size))
	{
		cell_size_ = map.cell_size;

		edge_pos_base_[0] = 0;
		for (int i = 1; i <= CELL_COUNT; ++i)
		{
			edge_pos_base_[i] = edge_pos_base_[i - 1] + cell_size_;
		}

		update_cell_position(map, true);
	}
}

void GameRenderer::update_cell_position(const GameMap& map, const bool force)
{
	if (force || center_ != map.center)
	{
		center_.x = map.center.x;
		center_.y = map.center.y;

		char buf[300];
		sprintf_s(buf, "Shapez Demo %.2fx%.2f center=(%.2f,%.2f)", width_, height_, center_.x, center_.y);
		glfwSetWindowTitle(current_window->window(), buf);

		const float xx = -center_.x * cell_size_ + width_ / 2;
		const float yy = -center_.y * cell_size_ + height_ / 2;

		for (int i = 0; i <= CELL_COUNT; ++i)
		{
			edge_pos_[i].x = edge_pos_base_[i] + xx;
			edge_pos_[i].y = edge_pos_base_[i] + yy;
		}
	}
}

void GameRenderer::draw_cells()
{
	map_border_drawer_.begin();

	for (int i = 0; i <= CELL_COUNT; i++)
	{
		map_border_drawer_.push(edge_pos_[0].x, edge_pos_[i].y, edge_pos_[CELL_COUNT].x, edge_pos_[i].y);
	}

	for (int i = 0; i <= CELL_COUNT; i++)
	{
		map_border_drawer_.push(edge_pos_[i].x, edge_pos_[0].y, edge_pos_[i].x, edge_pos_[CELL_COUNT].y);
	}

	map_border_drawer_.draw();
}

void GameRenderer::draw_map_resources(const GameMap& map)
{
	tex_drawer_.begin();

	tex_drawer_.alpha(0.4f);
	tex_drawer_.tex(colors_);

	for (int i = 0; i < CELL_COUNT; i++)
		for (int j = 0; j < CELL_COUNT; ++j)
			if (const ResourceType& res = map.get_resource(i, j); is_color(res))
			{
				const auto& [u, v, w, h] = colors_[resource_icon(res)];
				tex_drawer_.push(edge_pos_[j].x, edge_pos_[i].y, edge_pos_[j + 1].x, edge_pos_[i + 1].y, u, v, w, h);
			}

	tex_drawer_.tex(shapes_);

	for (int i = 0; i < CELL_COUNT; i++)
		for (int j = 0; j < CELL_COUNT; ++j)
			if (const ResourceType& res = map.get_resource(i, j); is_shape(res))
			{
				const auto& [u, v, w, h] = shapes_[resource_icon(res)];
				tex_drawer_.push(edge_pos_[j].x, edge_pos_[i].y, edge_pos_[j + 1].x, edge_pos_[i + 1].y, u, v, w, h);
			}

	tex_drawer_.draw();
}

void GameRenderer::draw_building(const GameMap& map)
{
}

void GameRenderer::draw_ui()
{
	const float x0 = (width_ - 800) / 2;
	const float y0 = height_ - 80, y1 = y0 + 50;
	shape_drawer_.rect(x0, y0, x0 + 800, y1, 0, 0, 0, 0.2f);

	float p0 = x0 + 20;
	tex_drawer_.begin();
	tex_drawer_.tex(icons_);
	tex_drawer_.alpha(0.5f);

	const auto& uvBalancer = icons_["balancer.png"];
	const auto& uvBelt = icons_["belt.png"];
	const auto& uvCutter = icons_["cutter.png"];
	const auto& uvMiner = icons_["miner.png"];
	const auto& uvMixer = icons_["mixer.png"];
	const auto& uvPainter = icons_["painter.png"];
	const auto& uvRotater = icons_["rotater.png"];
	const auto& uvStacker = icons_["stacker.png"];
	const auto& uvTrash = icons_["trash.png"];
	const auto& uvUnder = icons_["underground_belt.png"];

	constexpr float div = 70, sp = 5;
	tex_drawer_.push(p0 + sp, y0 + sp, p0 + 50 - sp, y1 - sp, uvMiner.u, uvMiner.v, uvMiner.w, uvMiner.h);
	p0 += div;
	tex_drawer_.push(p0 + sp, y0 + sp, p0 + 50 - sp, y1 - sp, uvBelt.u, uvBelt.v, uvBelt.w, uvBelt.h);
	p0 += div;
	tex_drawer_.push(p0 + sp, y0 + sp, p0 + 50 - sp, y1 - sp, uvBalancer.u, uvBalancer.v, uvBalancer.w, uvBalancer.h);
	p0 += div;
	tex_drawer_.push(p0 + sp, y0 + sp, p0 + 50 - sp, y1 - sp, uvRotater.u, uvRotater.v, uvRotater.w, uvRotater.h);
	p0 += div;
	tex_drawer_.push(p0 + sp, y0 + sp, p0 + 50 - sp, y1 - sp, uvUnder.u, uvUnder.v, uvUnder.w,  uvUnder.h);
	p0 += div;
	p0 += div; 
	tex_drawer_.push(p0 + sp, y0 + sp, p0 + 50 - sp, y1 - sp, uvCutter.u, uvCutter.v, uvCutter.w, uvCutter.h);
	p0 += div;
	tex_drawer_.push(p0 + sp, y0 + sp, p0 + 50 - sp, y1 - sp, uvMixer.u, uvMixer.v, uvMixer.w, uvMixer.h);
	p0 += div;
	tex_drawer_.push(p0 + sp, y0 + sp, p0 + 50 - sp, y1 - sp, uvPainter.u, uvPainter.v, uvPainter.w, uvPainter.h);
	p0 += div;
	tex_drawer_.push(p0 + sp, y0 + sp, p0 + 50 - sp, y1 - sp, uvStacker.u, uvStacker.v, uvStacker.w, uvStacker.h);
	p0 += div;
	tex_drawer_.push(p0 + sp, y0 + sp, p0 + 50 - sp, y1 - sp, uvTrash.u, uvTrash.v, uvTrash.w, uvTrash.h);

	tex_drawer_.draw();
}

void GameRenderer::draw_overlay()
{
}
