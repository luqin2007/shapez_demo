#pragma once

namespace MouseHelper
{
	extern void update();

	extern void initialize();

	extern bool is_left_clicked();

	extern bool is_left_drag();

	extern bool is_right_clicked();

	extern bool is_right_drag();

	extern bool is_mid_clicked();

	extern float x();

	extern float y();

	extern float dx();

	extern float dy();

	extern float wheel();

	extern void set_left_click(bool click);

	extern void set_mid_click(bool click);

	extern void set_right_click(bool click);

	extern void set_position(double x, double y);

	extern void set_wheel(double v);
};
