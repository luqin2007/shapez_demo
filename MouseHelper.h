#pragma once

class MouseHelper
{
public:
	void update();

	void initialize();

	[[nodiscard]] bool is_left_clicked() const;

	[[nodiscard]] bool is_left_drag() const;

	[[nodiscard]] bool is_right_clicked() const;

	[[nodiscard]] bool is_right_drag() const;

	[[nodiscard]] bool is_mid_clicked() const;

	[[nodiscard]] float x() const;

	[[nodiscard]] float y() const;

	[[nodiscard]] float dx() const;

	[[nodiscard]] float dy() const;

	[[nodiscard]] float wheel() const;

	void set_left_click(bool click);

	void set_mid_click(bool click);

	void set_right_click(bool click);

	void set_position(double x, double y);

	void set_wheel(double v);

private:
	bool last_left_clicked_ = false, last_right_clicked_ = false;
	bool left_clicked_ = false, mid_clicked_ = false, right_clicked_ = false;
	bool pos_initialized_ = false;
	float wheel_distance_ = 0;
	float x_pos_ = 0, y_pos_ = 0, last_x_pos_ = 0, last_y_pos_ = 0;
};
