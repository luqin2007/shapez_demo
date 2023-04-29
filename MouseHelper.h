#pragma once

namespace MouseHelper
{
	extern void update();

	extern void initialize();

	extern bool is_left_clicked();

	extern bool is_left_drag();

	extern float x();

	extern float y();

	extern float dx();

	extern float dy();

	extern float wheel();

	extern void set_left_click(bool click);

	extern void set_position(const double x, const double y);

	extern void set_wheel(double v);
};
