#include "GameRenderer.h"

void GameRenderer::initialize()
{
	glClearColor(0.99f, 0.99f, 0.98f, 1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	cout << "GameRenderer initializing..." << endl;

	cout << "Create shared instance buffer" << endl;
	const unsigned int index[6]{0, 1, 3, 1, 2, 3};
	glCreateBuffers(1, &buf_index_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buf_index_);
	glNamedBufferStorage(buf_index_, sizeof index, index, GL_MAP_READ_BIT);

	cout << "Initialize drawers..." << endl;
	border_drawer_.initialize();
	tex_drawer_.initialize(buf_index_);

	cout << "Initialize images..." << endl;
	colors_.initialize();
	colors_ << Resouces::root() / "image" / "colors" / "blue.png"
		<< Resouces::root() / "image" / "colors" / "cyan.png"
		<< Resouces::root() / "image" / "colors" / "green.png"
		<< Resouces::root() / "image" / "colors" / "purple.png"
		<< Resouces::root() / "image" / "colors" / "red.png"
		<< Resouces::root() / "image" / "colors" / "uncolored.png"
		<< Resouces::root() / "image" / "colors" / "white.png"
		<< Resouces::root() / "image" / "colors" / "yellow.png";
	glGenerateMipmap(GL_TEXTURE_2D);

	shapes_.initialize();
	shapes_ << Resouces::root() / "image" / "shapes" / "circle_blue.png"
		<< Resouces::root() / "image" / "shapes" / "circle_cyan.png"
		<< Resouces::root() / "image" / "shapes" / "circle_green.png"
		<< Resouces::root() / "image" / "shapes" / "circle_purple.png"
		<< Resouces::root() / "image" / "shapes" / "circle_red.png"
		<< Resouces::root() / "image" / "shapes" / "circle_uncolored.png"
		<< Resouces::root() / "image" / "shapes" / "circle_white.png"
		<< Resouces::root() / "image" / "shapes" / "circle_yellow.png"
		<< Resouces::root() / "image" / "shapes" / "rect_blue.png"
		<< Resouces::root() / "image" / "shapes" / "rect_cyan.png"
		<< Resouces::root() / "image" / "shapes" / "rect_green.png"
		<< Resouces::root() / "image" / "shapes" / "rect_purple.png"
		<< Resouces::root() / "image" / "shapes" / "rect_red.png"
		<< Resouces::root() / "image" / "shapes" / "rect_uncolored.png"
		<< Resouces::root() / "image" / "shapes" / "rect_white.png"
		<< Resouces::root() / "image" / "shapes" / "rect_yellow.png"
		<< Resouces::root() / "image" / "shapes" / "star_blue.png"
		<< Resouces::root() / "image" / "shapes" / "star_cyan.png"
		<< Resouces::root() / "image" / "shapes" / "star_green.png"
		<< Resouces::root() / "image" / "shapes" / "star_purple.png"
		<< Resouces::root() / "image" / "shapes" / "star_red.png"
		<< Resouces::root() / "image" / "shapes" / "star_uncolored.png"
		<< Resouces::root() / "image" / "shapes" / "star_white.png"
		<< Resouces::root() / "image" / "shapes" / "star_yellow.png";
	glGenerateMipmap(GL_TEXTURE_2D);

	icons_.initialize();
	icons_ << Resouces::root() / "image" / "building_icons" / "balancer.png"
		<< Resouces::root() / "image" / "building_icons" / "belt.png"
		<< Resouces::root() / "image" / "building_icons" / "block.png"
		<< Resouces::root() / "image" / "building_icons" / "cutter.png"
		<< Resouces::root() / "image" / "building_icons" / "miner.png"
		<< Resouces::root() / "image" / "building_icons" / "mixer.png"
		<< Resouces::root() / "image" / "building_icons" / "painter.png"
		<< Resouces::root() / "image" / "building_icons" / "rotater.png"
		<< Resouces::root() / "image" / "building_icons" / "stacker.png"
		<< Resouces::root() / "image" / "building_icons" / "trash.png"
		<< Resouces::root() / "image" / "building_icons" / "underground_belt.png";
	glGenerateMipmap(GL_TEXTURE_2D);

	buildings_small_.initialize();
	buildings_small_ << Resouces::root() / "image" / "buildings" / "belt_left_blue.png"
		<< Resouces::root() / "image" / "buildings" / "belt_right_blue.png"
		<< Resouces::root() / "image" / "buildings" / "belt_top_blue.png"
		<< Resouces::root() / "image" / "buildings" / "forward_0.png"
		<< Resouces::root() / "image" / "buildings" / "forward_1.png"
		<< Resouces::root() / "image" / "buildings" / "forward_2.png"
		<< Resouces::root() / "image" / "buildings" / "forward_3.png"
		<< Resouces::root() / "image" / "buildings" / "forward_4.png"
		<< Resouces::root() / "image" / "buildings" / "forward_5.png"
		<< Resouces::root() / "image" / "buildings" / "forward_6.png"
		<< Resouces::root() / "image" / "buildings" / "forward_7.png"
		<< Resouces::root() / "image" / "buildings" / "forward_8.png"
		<< Resouces::root() / "image" / "buildings" / "forward_9.png"
		<< Resouces::root() / "image" / "buildings" / "forward_10.png"
		<< Resouces::root() / "image" / "buildings" / "forward_11.png"
		<< Resouces::root() / "image" / "buildings" / "forward_12.png"
		<< Resouces::root() / "image" / "buildings" / "forward_13.png"
		<< Resouces::root() / "image" / "buildings" / "left_0.png"
		<< Resouces::root() / "image" / "buildings" / "left_1.png"
		<< Resouces::root() / "image" / "buildings" / "left_2.png"
		<< Resouces::root() / "image" / "buildings" / "left_3.png"
		<< Resouces::root() / "image" / "buildings" / "left_4.png"
		<< Resouces::root() / "image" / "buildings" / "left_5.png"
		<< Resouces::root() / "image" / "buildings" / "left_6.png"
		<< Resouces::root() / "image" / "buildings" / "left_7.png"
		<< Resouces::root() / "image" / "buildings" / "left_8.png"
		<< Resouces::root() / "image" / "buildings" / "left_9.png"
		<< Resouces::root() / "image" / "buildings" / "left_10.png"
		<< Resouces::root() / "image" / "buildings" / "left_11.png"
		<< Resouces::root() / "image" / "buildings" / "left_12.png"
		<< Resouces::root() / "image" / "buildings" / "left_13.png"
		<< Resouces::root() / "image" / "buildings" / "miner.png"
		<< Resouces::root() / "image" / "buildings" / "miner_blue.png"
		<< Resouces::root() / "image" / "buildings" / "miner-chainable.png"
		<< Resouces::root() / "image" / "buildings" / "right_0.png"
		<< Resouces::root() / "image" / "buildings" / "right_1.png"
		<< Resouces::root() / "image" / "buildings" / "right_2.png"
		<< Resouces::root() / "image" / "buildings" / "right_3.png"
		<< Resouces::root() / "image" / "buildings" / "right_4.png"
		<< Resouces::root() / "image" / "buildings" / "right_5.png"
		<< Resouces::root() / "image" / "buildings" / "right_6.png"
		<< Resouces::root() / "image" / "buildings" / "right_7.png"
		<< Resouces::root() / "image" / "buildings" / "right_8.png"
		<< Resouces::root() / "image" / "buildings" / "right_9.png"
		<< Resouces::root() / "image" / "buildings" / "right_10.png"
		<< Resouces::root() / "image" / "buildings" / "right_11.png"
		<< Resouces::root() / "image" / "buildings" / "right_12.png"
		<< Resouces::root() / "image" / "buildings" / "right_13.png"
		<< Resouces::root() / "image" / "buildings" / "rotater.png"
		<< Resouces::root() / "image" / "buildings" / "rotater_blue.png"
		<< Resouces::root() / "image" / "buildings" / "trash.png"
		<< Resouces::root() / "image" / "buildings" / "trash_blue.png"
		<< Resouces::root() / "image" / "buildings" / "underground_belt_entry.png"
		<< Resouces::root() / "image" / "buildings" / "underground_belt_entry_blue.png"
		<< Resouces::root() / "image" / "buildings" / "underground_belt_exit.png"
		<< Resouces::root() / "image" / "buildings" / "underground_belt_exit_blue.png";
	glGenerateMipmap(GL_TEXTURE_2D);

	buildings_middle_.initialize();
	buildings_middle_ << Resouces::root() / "image" / "buildings" / "balancer.png"
		<< Resouces::root() / "image" / "buildings" / "balancer_blue.png"
		<< Resouces::root() / "image" / "buildings" / "cutter.png"
		<< Resouces::root() / "image" / "buildings" / "cutter_blue.png"
		<< Resouces::root() / "image" / "buildings" / "mixer.png"
		<< Resouces::root() / "image" / "buildings" / "mixer_blue.png"
		<< Resouces::root() / "image" / "buildings" / "painter.png"
		<< Resouces::root() / "image" / "buildings" / "painter_blue.png"
		<< Resouces::root() / "image" / "buildings" / "stacker.png"
		<< Resouces::root() / "image" / "buildings" / "stacker_blue.png";
	glGenerateMipmap(GL_TEXTURE_2D);

	buildings_large_.initialize();
	buildings_large_ << Resouces::root() / "image" / "buildings" / "hub.png";
	glGenerateMipmap(GL_TEXTURE_2D);

	log_error("all renderer initialize");
	cout << "GameRenderer initialize finished." << endl;
}

void GameRenderer::update_env(const GameMap& map)
{
	glClear(GL_COLOR_BUFFER_BIT);

	if (fneq(width_, current_window->width()) || fneq(height_, current_window->height()))
	{
		width_ = current_window->width();
		height_ = current_window->height();

		char buf[300];
		sprintf_s(buf, "Shapez Demo %.2fx%.2f center=(%.2f,%.2f)", width_, height_, center_.x, center_.y);
		glfwSetWindowTitle(current_window->window(), buf);

		border_drawer_.resize(width_, height_);
		tex_drawer_.resize(width_, height_);
	}

	update_cell_size(map);
	update_cell_position(map, false);
}

void GameRenderer::draw(const GameMap& map)
{
	draw_cells();
	draw_map_resources(map);
	draw_building(map);
	draw_ui();
	draw_overlay();
}

void GameRenderer::destroy()
{
	border_drawer_.destroy();
	tex_drawer_.destroy();
	colors_.destroy();
	shapes_.destroy();
	icons_.destroy();
	buildings_small_.destroy();
	buildings_middle_.destroy();
	buildings_large_.destroy();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &buf_index_);
}

void GameRenderer::update_cell_size(const GameMap& map)
{
	if (fneq(cell_size_, map.cell_size))
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
	if (force || fneq(center_, map.center))
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
	border_drawer_.begin();

	for (int i = 0; i <= CELL_COUNT; i++)
	{
		border_drawer_.push(edge_pos_[0].x, edge_pos_[i].y, edge_pos_[CELL_COUNT].x, edge_pos_[i].y);
	}

	for (int i = 0; i <= CELL_COUNT; i++)
	{
		border_drawer_.push(edge_pos_[i].x, edge_pos_[0].y, edge_pos_[i].x, edge_pos_[CELL_COUNT].y);
	}

	border_drawer_.draw();

	log_error("draw_cells");
}

void GameRenderer::draw_map_resources(const GameMap& map)
{
	tex_drawer_.begin();

	tex_drawer_.alpha(0.4f);
	tex_drawer_.tex(colors_);

	for (int i = 0; i < CELL_COUNT; i++)
		for (int j = 0; j < CELL_COUNT; ++j)
			if (const ResourceType& res = map.get_resource(j, i); res.is_color)
			{
				const auto& [u, v, w, h] = colors_[res.name];
				tex_drawer_.push(edge_pos_[j].x, edge_pos_[i].y, edge_pos_[j + 1].x, edge_pos_[i + 1].y, u, v, w, h);
			}

	tex_drawer_.tex(shapes_);

	for (int i = 0; i < CELL_COUNT; i++)
		for (int j = 0; j < CELL_COUNT; ++j)
			if (const ResourceType& res = map.get_resource(j, i); res.is_shape)
			{
				const auto& [u, v, w, h] = shapes_[res.name];
				tex_drawer_.push(edge_pos_[j].x, edge_pos_[i].y, edge_pos_[j + 1].x, edge_pos_[i + 1].y, u, v, w, h);
			}

	tex_drawer_.draw();

	log_error("draw_map_resources");
}

void GameRenderer::draw_building(const GameMap& map)
{
	log_error("draw_building");
}

void GameRenderer::draw_ui()
{
	log_error("draw_ui");
}

void GameRenderer::draw_overlay()
{
	log_error("draw_overlay");
}
