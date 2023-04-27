#include "GameRenderer.h"

#include "Timer.h"

void GameRenderer::initialize()
{
	hiex::SetWindowTitle(L"Shapez Demo");
	hiex::BindWindowCanvas(&canvas_);
	canvas_.SetBkColor(0xfcfcfb);

	images_["blue.png"] = canvas_.Load_Image_Alpha(L"./images/colors/blue.png");
}

void GameRenderer::update_env()
{
	canvas_.Clear();
	width_ = canvas_.GetWidth();
	height_ = canvas_.GetHeight();

}

void GameRenderer::draw_map(const GameMap& map)
{
	Timer& timer = *current_timer;

	if (cell_size_ != map.cell_size)
	{
		cell_size_ = map.cell_size;
		resize_images();
	}

	canvas_.SetLineThickness(min(3, (int) (map.cell_size / 5)));

	float xx = width_ / 2.0f - map.cell_size * map.center.x;
	float yy = height_ / 2.0f - map.cell_size * map.center.y;
	int x0 = -1, x1 = -1, y0 = -1, y1 = -1;
	for (int i = 0, px = xx; i <= 100; ++i, px += map.cell_size)
	{
		edge_pos_[i].x = px;
		if (x0 == -1 && px + map.cell_size >= 0) x0 = i;
		if (x1 == -1 && px + map.cell_size > width_) x1 = i == 100 ? 100 : i + 1;
	}
	if (x0 == -1) x0 = 0;
	if (x1 == -1) x1 = 100;
	for (int i = 0, py = yy; i <= 100; ++i, py += map.cell_size)
	{
		edge_pos_[i].y = py;
		if (y0 == -1 && py + map.cell_size >= 0) y0 = i;
		if (y1 == -1 && py + map.cell_size > height_) y1 = i == 100 ? 100 : i + 1;
	}
	if (y0 == -1) y0 = 0;
	if (y1 == -1) y1 = 100;

	for (int i = x0; i <= x1; i++)
	{
		canvas_.Line(edge_pos_[i].x, edge_pos_[y0].y, edge_pos_[i].x, edge_pos_[y1].y, true, 0xf6f6f5);
	}
	for (int i = y0; i <= y1; i++)
	{
		canvas_.Line(edge_pos_[x0].x, edge_pos_[i].y, edge_pos_[x1].x, edge_pos_[i].y, true, 0xf6f6f5);
	}
	for (int i = x0; i < x1; ++i)
	{
		for (int j = y0; j < y1; ++j)
		{
			const auto res = map.get_resource(i, j);
			switch (res)
			{
			case ResourceType::SHAPE_CIRCLE:
			{
				break;
			}
			case ResourceType::SHAPE_RECT:
			{
				break;
			}
			case ResourceType::SHAPE_STAR:
			{
				break;
			}
			case ResourceType::COLOR_BLUE:
			{
				canvas_.PutImageIn_Alpha(edge_pos_[i].x, edge_pos_[j].y, &zoomed_images_["blue.png"], {0}, (int) (timer.current / 100) % 256, true, true);
				break;
			}
			case ResourceType::COLOR_RED:
			{
				break;
			}
			case ResourceType::COLOR_YELLOW:
			{
				break;
			}
			}
		}
	}
}

void GameRenderer::draw_building(const GameMap& map)
{
}

void GameRenderer::draw_ui()
{
}

void GameRenderer::draw_overlay()
{
}

void GameRenderer::resize_images()
{
	zoomed_images_["blue.png"] = hiex::ZoomImage_Win32_Alpha(&images_["blue.png"], cell_size_, cell_size_);
}
