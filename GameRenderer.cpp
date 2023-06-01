#include "GameRenderer.h"

#include <glad/glad.h>

#include "Building.h"
#include "Miner.h"
#include "BuildingRenderer.h"
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
	map_border_drawer.initialize();
	tex_drawer.initialize();
	shape_drawer.initialize();

	cout << "Initialize image atlas..." << endl;
	atlas.initialize()
		// icon
		<< ROOT / "image" / "buildings" / "balancer_icon.png"
		<< ROOT / "image" / "buildings" / "belt_icon.png"
		<< ROOT / "image" / "buildings" / "block_icon.png"
		<< ROOT / "image" / "buildings" / "cutter_icon.png"
		<< ROOT / "image" / "buildings" / "miner_icon.png"
		<< ROOT / "image" / "buildings" / "mixer_icon.png"
		<< ROOT / "image" / "buildings" / "painter_icon.png"
		<< ROOT / "image" / "buildings" / "rotater_icon.png"
		<< ROOT / "image" / "buildings" / "stacker_icon.png"
		<< ROOT / "image" / "buildings" / "trash_icon.png"
		<< ROOT / "image" / "buildings" / "underground_belt_icon.png"
		// 1x1
		<< ROOT / "image" / "buildings" / "belt_left_blue.png"
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
		<< ROOT / "image" / "buildings" / "underground_belt_exit_blue.png"
		<< ROOT / "image" / "buildings" / "rotater-ccw.png"
		<< ROOT / "image" / "buildings" / "rotater-ccw_blue.png"
		// 2x2
		<< ROOT / "image" / "buildings" / "balancer.png"
		<< ROOT / "image" / "buildings" / "balancer_blue.png"
		<< ROOT / "image" / "buildings" / "cutter.png"
		<< ROOT / "image" / "buildings" / "cutter_blue.png"
		<< ROOT / "image" / "buildings" / "mixer.png"
		<< ROOT / "image" / "buildings" / "mixer_blue.png"
		<< ROOT / "image" / "buildings" / "painter.png"
		<< ROOT / "image" / "buildings" / "painter_blue.png"
		<< ROOT / "image" / "buildings" / "stacker.png"
		<< ROOT / "image" / "buildings" / "stacker_blue.png"
		// 4x4
		<< ROOT / "image" / "buildings" / "hub.png"
		// misc
		<< ROOT / "image" / "misc" / "slot_bad_arrow.png"
		<< ROOT / "image" / "misc" / "slot_good_arrow.png"
		<< dot9{8, 10}
		<< ROOT / "image" / "misc" / "storage_overlay.png"
		<< dot9{12, 12}
		<< ROOT / "image" / "misc" / "button_background.png"
		// resource
		<< ROOT / "image" / "resources" / "blue.png"
		<< ROOT / "image" / "resources" / "cyan.png"
		<< ROOT / "image" / "resources" / "green.png"
		<< ROOT / "image" / "resources" / "purple.png"
		<< ROOT / "image" / "resources" / "red.png"
		<< ROOT / "image" / "resources" / "uncolored.png"
		<< ROOT / "image" / "resources" / "white.png"
		<< ROOT / "image" / "resources" / "yellow.png"
		<< Action::m4
		<< ROOT / "image" / "resources" / "circle_blue.png"
		<< ROOT / "image" / "resources" / "circle_cyan.png"
		<< ROOT / "image" / "resources" / "circle_green.png"
		<< ROOT / "image" / "resources" / "circle_purple.png"
		<< ROOT / "image" / "resources" / "circle_red.png"
		<< ROOT / "image" / "resources" / "circle_uncolored.png"
		<< ROOT / "image" / "resources" / "circle_white.png"
		<< ROOT / "image" / "resources" / "circle_yellow.png"
		<< ROOT / "image" / "resources" / "rect_blue.png"
		<< ROOT / "image" / "resources" / "rect_cyan.png"
		<< ROOT / "image" / "resources" / "rect_green.png"
		<< ROOT / "image" / "resources" / "rect_purple.png"
		<< ROOT / "image" / "resources" / "rect_red.png"
		<< ROOT / "image" / "resources" / "rect_uncolored.png"
		<< ROOT / "image" / "resources" / "rect_white.png"
		<< ROOT / "image" / "resources" / "rect_yellow.png"
		<< ROOT / "image" / "resources" / "star_blue.png"
		<< ROOT / "image" / "resources" / "star_cyan.png"
		<< ROOT / "image" / "resources" / "star_green.png"
		<< ROOT / "image" / "resources" / "star_purple.png"
		<< ROOT / "image" / "resources" / "star_red.png"
		<< ROOT / "image" / "resources" / "star_uncolored.png"
		<< ROOT / "image" / "resources" / "star_white.png"
		<< ROOT / "image" / "resources" / "star_yellow.png"
		<< Action::mipmap
		<< Action::finished;

	// 适应窗口大小
	const int width = current_window->width();
	const int height = current_window->height();
	AbstractDrawer::resize(width, height);
	update_cell_size(current_game->map());
	update_cell_position(current_game->map(), width, height);
	cout << "GameRenderer initialize finished." << endl;
}

void GameRenderer::update(const GameLogic& game)
{
	glClear(GL_COLOR_BUFFER_BIT);
	const auto& map = game.map();

	draw_cells();
	draw_map_resources(map);
	draw_building(game, map);
	draw_ui(game);
	draw_overlay(game, map);
}

void GameRenderer::destroy()
{
	map_border_drawer.destroy();
	tex_drawer.destroy();
	// font_drawer_.destroy();
	shape_drawer.destroy();
	AbstractDrawer::destroy_static();

	atlas.destroy();
}

void GameRenderer::update_cell_size(const GameMap& map)
{
	edge_pos_base[0] = 0;
	for (int i = 1; i <= CELL_COUNT; ++i)
	{
		edge_pos_base[i] = edge_pos_base[i - 1] + map.cell_size;
	}
}

auto GameRenderer::update_cell_position(const GameMap& map, const float width, const float height) -> void
{
	const float xx = -map.center.x * map.cell_size + width / 2.0f;
	const float yy = -map.center.y * map.cell_size + height / 2.0f;

	bool is_set[4] = {false, false, false, false};

	for (int i = 0; i <= CELL_COUNT; ++i)
	{
		edge_pos[i].x = edge_pos_base[i] + xx;
		if (!is_set[0])
		{
			// 左上角 列
			if (i == CELL_COUNT)
			{
				cell0_.y = CELL_COUNT;
				is_set[0] = true;
			}
			else if (edge_pos[i].x > 0)
			{
				cell0_.y = i == 0 ? 0 : i - 1;
				is_set[0] = true;
			}
		}
		if (!is_set[1])
		{
			// 右下角 列
			if (edge_pos[i].x >= width || i == CELL_COUNT)
			{
				cell1_.y = i;
				is_set[1] = true;
			}
		}

		edge_pos[i].y = edge_pos_base[i] + yy;
		if (!is_set[2])
		{
			// 左上角 行
			if (i == CELL_COUNT)
			{
				cell0_.x = CELL_COUNT;
				is_set[2] = true;
			}
			else if (edge_pos[i].y > 0)
			{
				cell0_.x = i == 0 ? 0 : i - 1;
				is_set[2] = true;
			}
		}
		if (!is_set[3])
		{
			// 右下角 行
			if (edge_pos[i].y >= width || i == CELL_COUNT)
			{
				cell1_.x = i;
				is_set[3] = true;
			}
		}
	}
}

void GameRenderer::draw_cells()
{
	map_border_drawer.begin();

	for (int i = 0; i <= CELL_COUNT; i++)
	{
		map_border_drawer.push(edge_pos[0].x, edge_pos[i].y, edge_pos[CELL_COUNT].x, edge_pos[i].y);
	}

	for (int i = 0; i <= CELL_COUNT; i++)
	{
		map_border_drawer.push(edge_pos[i].x, edge_pos[0].y, edge_pos[i].x, edge_pos[CELL_COUNT].y);
	}

	map_border_drawer.draw();
}

void GameRenderer::draw_map_resources(const GameMap& map)
{
	tex_drawer.begin();

	tex_drawer.alpha(0.5f);

	const float sp = map.cell_size / 3.5f;

	for (int i = cell0_.x; i < cell1_.x; i++)
	{
		for (int j = cell0_.y; j < cell1_.y; ++j)
		{
			const ResourceType& res = map.get_resource(i, j);
			if (has_icon(res))
			{
				// 是否被挖掘
				const BuildingContext* ctx = map.get_building(i, j);
				const bool mining = ctx && ctx->building == Miner::instance();
				// 绘制
				tex_drawer.push(edge_pos[j].x + sp, edge_pos[i].y + sp, edge_pos[j + 1].x - sp, edge_pos[i + 1].y - sp,
				                atlas, resource_icon(res), Side::up, mining);
			}
		}
	}

	tex_drawer.draw();
}

void GameRenderer::draw_building(const GameLogic& game, const GameMap& map)
{
	tex_drawer.begin();

	// 地图上的建筑
	for (int i = cell0_.x; i < cell1_.x; i++)
	{
		for (int j = cell0_.y; j < cell1_.y; ++j)
		{
			if (const BuildingContext* ctx = map.get_building(i, j); ctx && ctx->pos.x == i && ctx->pos.y == j)
			{
				ctx->building.get_renderer().draw_building(i, j, *ctx, *this, map);
			}
		}
	}

	tex_drawer.draw();
}

void GameRenderer::draw_ui(const GameLogic& game)
{
	tex_drawer.begin();
	// 背景
	const auto x0 = static_cast<float>(game.icon_bg0.x);
	const auto y0 = static_cast<float>(game.icon_bg0.y);
	const auto x1 = static_cast<float>(game.icon_bg1.x);
	const auto y1 = static_cast<float>(game.icon_bg1.y);
	tex_drawer.alpha(0.1f);
	tex_drawer.push(x0, y0, x1, y1, atlas, "button_background.png");

	// 按钮
	tex_drawer.alpha(1);
	for (const auto& [name, p0] : game.buttons)
	{
		const auto x = static_cast<float>(p0.x);
		const auto y = static_cast<float>(p0.y);
		const Building* building = game.buildings.at(name);
		building->get_renderer().draw_icon(x, y, BUTTON_SIZE, *this);

		const float mouse_x = MouseHelper::x();
		const float mouse_y = MouseHelper::y();
		if (!current_game->current_building
			&& is_in(x, mouse_x, BUTTON_SIZE)
			&& is_in(y, mouse_y, BUTTON_SIZE))
		{
			tex_drawer.alpha(0.5f);
			tex_drawer.push(x - BUTTON_PADDING, y - BUTTON_PADDING,
			                x + BUTTON_SIZE + BUTTON_PADDING, y + BUTTON_SIZE + BUTTON_PADDING,
			                atlas, "button_background.png");
			tex_drawer.alpha(1);
		}
	}

	tex_drawer.draw();
}

void GameRenderer::draw_overlay(const GameLogic& game, const GameMap& map)
{
	tex_drawer.begin();

	// 地图上的建筑
	for (int i = cell0_.x; i < cell1_.x; i++)
	{
		for (int j = cell0_.y; j < cell1_.y; ++j)
		{
			if (const BuildingContext* ctx = map.get_building(i, j); ctx && ctx->pos.x == i && ctx->pos.y == j)
			{
				ctx->building.get_renderer().draw_overlay(i, j, *ctx, *this, map);
			}
		}
	}

	// 鼠标持有的建筑
	const float cell_size = map.cell_size;
	if (game.current_building)
	{
		const float xx = MouseHelper::x() - cell_size / 2;
		const float yy = MouseHelper::y() - cell_size / 2;
		game.current_building->get_renderer().draw_holding(xx, yy, game.current_side, *this, map);
	}

	tex_drawer.draw();
}
