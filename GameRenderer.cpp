#include "GameRenderer.h"

#include <glad/glad.h>

#include "Building.h"
#include "GameLogic.h"
#include "GameWindow.h"
#include "MouseHelper.h"
#include "Timer.h"

void GameRenderer::initialize()
{
	current_renderer = this;

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

	buildings_special_.initialize();
	buildings_special_ << ROOT / "image" / "buildings" / "hub.png";
	glGenerateMipmap(GL_TEXTURE_2D);

	on_resize(current_window->width(), current_window->height());
	cout << "GameRenderer initialize finished." << endl;
}

void GameRenderer::update(GameLogic& logic)
{
	glClear(GL_COLOR_BUFFER_BIT);

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
	buildings_special_.destroy();
}

void GameRenderer::on_resize(const int width, const int height)
{
	width_ = width;
	height_ = height;
	AbstractDrawer::resize(width_, height_);

	char buf[300];
	sprintf_s(buf, "Shapez Demo %dx%d center=(%.2f,%.2f)", width, height, center_.x, center_.y);
	glfwSetWindowTitle(current_window->window(), buf);
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
		sprintf_s(buf, "Shapez Demo %dx%d center=(%.2f,%.2f)", static_cast<int>(width_), static_cast<int>(height_),
		          center_.x, center_.y);
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
	if (current_window && current_game)
	{
		const float mouse_x = MouseHelper::x();
		const float mouse_y = MouseHelper::y();

		// 背景
		const auto x0 = static_cast<float>(current_window->button_p0.x);
		const auto y0 = static_cast<float>(current_window->button_p0.y);
		const auto x1 = static_cast<float>(current_window->button_p1.x);
		const auto y1 = static_cast<float>(current_window->button_p1.y);
		shape_drawer_.rect(x0, y0, x1, y1, 0, 0, 0, 0.2f);

		// 按钮
		tex_drawer_.begin();
		tex_drawer_.tex(icons_);
		tex_drawer_.alpha(0.3f);
		for (const auto& [name, p0] : current_window->buttons)
		{
			constexpr float sp = 5;
			const auto x = static_cast<float>(p0.x);
			const auto y = static_cast<float>(p0.y);

			const bool selected = !current_game->current_building
				&& is_in(x, mouse_x, GameWindow::button_size_f)
				&& is_in(y, mouse_y, GameWindow::button_size_f);

			if (selected)
			{
				tex_drawer_.alpha(1);
			}

			const auto& [u, v, w, h] = icons_[current_game->buildings[name]->tex_icon];
			tex_drawer_.push(x + sp, y + sp, x + GameWindow::button_size_f - sp, y + GameWindow::button_size_f - sp, u, v, w, h);

			if (selected)
			{
				tex_drawer_.alpha(0.3f);
			}
		}
		// 选中
		if (current_game->current_building)
		{
			tex_drawer_.alpha(1);
			float w, h;
			const Rect *uv = nullptr;
			switch (current_game->current_building->size)
			{
			case BuildingSize::small:
				tex_drawer_.tex(buildings_small_);
				w = h = cell_size_;
				uv = &buildings_small_[current_game->current_building->tex_hover];
				break;
			case BuildingSize::middle:
				tex_drawer_.tex(buildings_middle_);
				uv = &buildings_middle_[current_game->current_building->tex_hover];
				w = cell_size_ * 2;
				h = cell_size_;
				break;
			case BuildingSize::large:
				tex_drawer_.tex(buildings_large_);
				uv = &buildings_large_[current_game->current_building->tex_hover];
				w = cell_size_ * 3;
				h = cell_size_;
				break;
			case BuildingSize::special:
				tex_drawer_.tex(buildings_special_);
				uv = &buildings_special_[current_game->current_building->tex_hover];
				w = h = cell_size_ * 4;
				break;
			}

			const float xx = mouse_x - cell_size_ / 2;
			const float yy = mouse_y - cell_size_ / 2;
			tex_drawer_.push(xx, yy, xx + w, yy + h, uv->u, uv->v, uv->w, uv->h, current_game->current_side);
		}
		tex_drawer_.draw();
	}
}

void GameRenderer::draw_overlay()
{
}
