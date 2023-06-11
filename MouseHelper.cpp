#include "MouseHelper.h"

void MouseHelper::update()
{
	last_left_clicked_ = left_clicked_;
	last_right_clicked_ = right_clicked_;
	last_x_pos_ = x_pos_;
	last_y_pos_ = y_pos_;
	wheel_distance_ = 0;
}

void MouseHelper::initialize()
{
	last_left_clicked_ = false;
	left_clicked_ = false;
	last_right_clicked_ = false;
	right_clicked_ = false;
	mid_clicked_ = false;
	pos_initialized_ = false;
	update();
}

bool MouseHelper::is_left_clicked() const
{
	return last_left_clicked_ && !left_clicked_;
}

bool MouseHelper::is_right_clicked() const
{
	return last_right_clicked_ && !right_clicked_;
}

bool MouseHelper::is_left_drag() const
{
	return last_left_clicked_ && left_clicked_;
}

bool MouseHelper::is_right_drag() const
{
	return last_right_clicked_ && right_clicked_;
}

bool MouseHelper::is_mid_clicked() const
{
	return mid_clicked_;
}

float MouseHelper::x() const
{
	return x_pos_;
}

float MouseHelper::y() const
{
	return y_pos_;
}

float MouseHelper::dx() const
{
	return x_pos_ - last_x_pos_;
}

float MouseHelper::dy() const
{
	return y_pos_ - last_y_pos_;
}

float MouseHelper::wheel() const
{
	return wheel_distance_;
}

void MouseHelper::set_left_click(const bool click)
{
	left_clicked_ = click;
}

void MouseHelper::set_mid_click(const bool click)
{
	mid_clicked_ = click;
}

void MouseHelper::set_right_click(const bool click)
{
	right_clicked_ = click;
}

void MouseHelper::set_position(const double x, const double y)
{
	x_pos_ = static_cast<float>(x);
	y_pos_ = static_cast<float>(y);
	if (!pos_initialized_)
	{
		last_x_pos_ = x_pos_;
		last_y_pos_ = y_pos_;
		pos_initialized_ = true;
	}
}

void MouseHelper::set_wheel(const double v)
{
	wheel_distance_ = static_cast<float>(v);
}
