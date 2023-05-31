#pragma once

#include "Atlas.h"
#include "BuildingRenderer.h"

class RotaterRenderer : public BuildingRenderer
{
public:
	void draw_building(int row, int col, const BuildingContext& context, GameRenderer& renderer,
	                   const GameMap& map) const override;
	void draw_holding(float x, float y, Side direction, GameRenderer& renderer, const GameMap& map) const override;
	void draw_icon(float x, float y, float size, GameRenderer& renderer) const override;

protected:
	[[nodiscard]] virtual const string& get_building_tex() const = 0;
	[[nodiscard]] virtual const string& get_holding_tex() const = 0;
};

class RotaterCWRenderer final : public RotaterRenderer
{
protected:
	[[nodiscard]] const string& get_building_tex() const override;
	[[nodiscard]] const string& get_holding_tex() const override;
};

class RotaterCCWRenderer final : public RotaterRenderer
{
protected:
	[[nodiscard]] const string& get_building_tex() const override;
	[[nodiscard]] const string& get_holding_tex() const override;
};
