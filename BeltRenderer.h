#pragma once
#include "Atlas.h"
#include "BuildingRenderer.h"

class BeltContext;

class BeltDirect;
class BeltLeft;
class BeltRight;

class BeltRenderer : public BuildingRenderer
{
public:
	void draw_building(int row, int col, const BuildingContext& context, GameRenderer& renderer,
	                   const GameMap& map) const override;
	void draw_holding(float x, float y, Side direction, GameRenderer& renderer, const GameMap& map) const override;
	void draw_icon(float x, float y, float size, GameRenderer& renderer) const override;

protected:
	time_t delta_time_ = 40;
	const string holding_;

	explicit BeltRenderer(string holding): holding_(std::move(holding))
	{
	}

	[[nodiscard]] virtual const string& get_building_tex(int index) const = 0;
	virtual void draw_items(float x0, float y0, float x1, float y1,
	                        float cell_size, const BeltContext& context, GameRenderer& renderer) const = 0;
};

class BeltDirectRenderer final : public BeltRenderer
{
	friend BeltDirect;
protected:
	/**
	 * \brief 动画纹理
	 */
	string tex_forward_[14]
	{
		"forward_0.png", "forward_1.png", "forward_2.png", "forward_3.png", "forward_4.png",
		"forward_5.png", "forward_6.png", "forward_7.png", "forward_8.png", "forward_9.png",
		"forward_10.png", "forward_11.png", "forward_12.png", "forward_13.png",
	};

	BeltDirectRenderer() : BeltRenderer("belt_top_blue.png")
	{
	}

	[[nodiscard]] const string& get_building_tex(int index) const override;
	void draw_items(float x0, float y0, float x1, float y1,
	                float cell_size, const BeltContext& context, GameRenderer& renderer) const override;
};

class BeltLeftRenderer final : public BeltRenderer
{
	friend BeltLeft;
protected:
	/**
	 * \brief 动画纹理
	 */
	string tex_left_[14]
	{
		"left_0.png", "left_1.png", "left_2.png", "left_3.png", "left_4.png",
		"left_5.png", "left_6.png", "left_7.png", "left_8.png", "left_9.png",
		"left_10.png", "left_11.png", "left_12.png", "left_13.png",
	};

	BeltLeftRenderer() : BeltRenderer("belt_left_blue.png")
	{
	}

	[[nodiscard]] const string& get_building_tex(int index) const override;
	void draw_items(float x0, float y0, float x1, float y1,
	                float cell_size, const BeltContext& context, GameRenderer& renderer) const override;
};

class BeltRightRenderer final : public BeltRenderer
{
	friend BeltRight;
protected:
	/**
	 * \brief 动画纹理
	 */
	string tex_right_[14]
	{
		"right_0.png", "right_1.png", "right_2.png", "right_3.png", "right_4.png",
		"right_5.png", "right_6.png", "right_7.png", "right_8.png", "right_9.png",
		"right_10.png", "right_11.png", "right_12.png", "right_13.png",
	};

	BeltRightRenderer(): BeltRenderer("belt_right_blue.png")
	{
	}

	[[nodiscard]] const string& get_building_tex(int index) const override;
	void draw_items(float x0, float y0, float x1, float y1,
	                float cell_size, const BeltContext& context, GameRenderer& renderer) const override;
};
