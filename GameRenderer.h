#pragma once

#include <iostream>
#include <map>

#include <glad/glad.h>

#include "GameMap.h"
#include "Resouces.h"
#include "Common.h"

using std::map;
using std::cout;
using std::cerr;
using std::endl;

struct UV
{
	float u, v, w, h;
};

class GameRenderer
{
public:
	void initialize();

	void update_env();

	void draw(const GameMap& map);

private:
	vec2 edge_pos_[101];
	float cell_size_ = 0;
	float width_ = 0, height_ = 0;
	map<GLuint, map<string, UV>> alias_;

	GLuint tex_icons_colors_ = 0, tex_buildings_shapes_ = 0;
	GLuint program_cell_ = 0, program_tex_ = 0, program_tex_alpha_ = 0;
	GLint uniform_size_ = 0, uniform_tex_ = 1, uniform_alpha_ = 2;
	GLuint buf_vertex_ = 0, buf_index_ = 0;
	GLuint vao_cell_ = 0, vao_tex_ = 0;

	const GLint texture_icons_colors_ = 0, texture_buildings_shapes_ = 1;
	int x0_ = 0, x1_ = 0, y0_ = 0, y1_ = 0;

	void draw_cells() const;

	void draw_dye_resources(const GameMap& map);

	void draw_shape_resources(const GameMap& map);

	void draw_building(const GameMap& map);

	void draw_ui();

	void draw_overlay();

	void create_gl_texture(GLuint* tex, int slot, int width, int height);

	void push_tex(const path& p, GLuint tex, GLint off_y, GLint off_x, float size);

	void push_res_tex(const path& p, GLuint tex, GLint off_y, GLint off_x, float size);

	static void create_program(GLuint& program, string&& vert, string&& frag);

	static GLuint create_shader(GLenum type, const path& p);
};
