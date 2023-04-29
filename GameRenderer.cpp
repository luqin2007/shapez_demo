#include "GameRenderer.h"

#include "GameWindow.h"
#include "Timer.h"

void GameRenderer::initialize()
{
	glClearColor(0.99f, 0.99f, 0.98f, 1);
	glEnable(GL_BLEND);

	cout << "GameRenderer initializing..." << endl;

	cout << " Create icon texture alias(512x512)..." << endl;
	create_gl_texture(&tex_icons_colors_, GL_TEXTURE0, 512, 512); // 4 * 128, 4 * 128
	push_tex(Resouces::root() / "image" / "building_icons" / "balancer.png", tex_icons_colors_, 0, 0, 512);
	push_tex(Resouces::root() / "image" / "building_icons" / "belt.png", tex_icons_colors_, 128, 0, 512);
	push_tex(Resouces::root() / "image" / "building_icons" / "block.png", tex_icons_colors_, 256, 0, 512);
	push_tex(Resouces::root() / "image" / "building_icons" / "cutter.png", tex_icons_colors_, 384, 0, 512);
	push_tex(Resouces::root() / "image" / "building_icons" / "miner.png", tex_icons_colors_, 0, 128, 512);
	push_tex(Resouces::root() / "image" / "building_icons" / "mixer.png", tex_icons_colors_, 128, 128, 512);
	push_tex(Resouces::root() / "image" / "building_icons" / "painter.png", tex_icons_colors_, 256, 128, 512);
	push_tex(Resouces::root() / "image" / "building_icons" / "rotater.png", tex_icons_colors_, 384, 128, 512);
	push_tex(Resouces::root() / "image" / "building_icons" / "stacker.png", tex_icons_colors_, 0, 256, 512);
	push_tex(Resouces::root() / "image" / "building_icons" / "trash.png", tex_icons_colors_, 128, 256, 512);
	push_tex(Resouces::root() / "image" / "building_icons" / "underground_belt.png", tex_icons_colors_, 256, 256, 512);
	push_tex(Resouces::root() / "image" / "colors" / "blue.png", tex_icons_colors_, 384, 256, 512);
	push_tex(Resouces::root() / "image" / "colors" / "cyan.png", tex_icons_colors_, 0, 384, 512);
	push_tex(Resouces::root() / "image" / "colors" / "green.png", tex_icons_colors_, 72, 384, 512);
	push_tex(Resouces::root() / "image" / "colors" / "purple.png", tex_icons_colors_, 144, 384, 512);
	push_tex(Resouces::root() / "image" / "colors" / "red.png", tex_icons_colors_, 216, 384, 512);
	push_tex(Resouces::root() / "image" / "colors" / "uncolored.png", tex_icons_colors_, 288, 384, 512);
	push_tex(Resouces::root() / "image" / "colors" / "white.png", tex_icons_colors_, 360, 384, 512);
	push_tex(Resouces::root() / "image" / "colors" / "yellow.png", tex_icons_colors_, 432, 384, 512);
	glGenerateMipmap(GL_TEXTURE_2D);

	cout << " Create building texture alias(2048x2048)..." << endl;
	create_gl_texture(&tex_buildings_shapes_, GL_TEXTURE1, 2048, 2048); // 10 * 192, 10 * 192
	push_tex(Resouces::root() / "image" / "buildings" / "forward_0.png", tex_buildings_shapes_, 0, 0, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "forward_1.png", tex_buildings_shapes_, 192, 0, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "forward_2.png", tex_buildings_shapes_, 384, 0, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "forward_3.png", tex_buildings_shapes_, 576, 0, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "forward_4.png", tex_buildings_shapes_, 768, 0, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "forward_5.png", tex_buildings_shapes_, 960, 0, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "forward_6.png", tex_buildings_shapes_, 1152, 0, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "forward_7.png", tex_buildings_shapes_, 1344, 0, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "forward_8.png", tex_buildings_shapes_, 1536, 0, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "forward_9.png", tex_buildings_shapes_, 1728, 0, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "forward_10.png", tex_buildings_shapes_, 0, 192, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "forward_11.png", tex_buildings_shapes_, 192, 192, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "forward_12.png", tex_buildings_shapes_, 384, 192, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "forward_13.png", tex_buildings_shapes_, 576, 192, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "left_0.png", tex_buildings_shapes_, 768, 192, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "left_1.png", tex_buildings_shapes_, 960, 192, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "left_2.png", tex_buildings_shapes_, 1152, 192, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "left_3.png", tex_buildings_shapes_, 1344, 192, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "left_4.png", tex_buildings_shapes_, 1536, 192, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "left_5.png", tex_buildings_shapes_, 1728, 192, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "left_6.png", tex_buildings_shapes_, 0, 384, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "left_7.png", tex_buildings_shapes_, 192, 384, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "left_8.png", tex_buildings_shapes_, 384, 384, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "left_9.png", tex_buildings_shapes_, 576, 384, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "left_10.png", tex_buildings_shapes_, 768, 384, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "left_11.png", tex_buildings_shapes_, 960, 384, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "left_12.png", tex_buildings_shapes_, 1152, 384, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "left_13.png", tex_buildings_shapes_, 1344, 384, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "right_0.png", tex_buildings_shapes_, 1536, 384, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "right_1.png", tex_buildings_shapes_, 1728, 384, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "right_2.png", tex_buildings_shapes_, 0, 576, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "right_3.png", tex_buildings_shapes_, 192, 576, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "right_4.png", tex_buildings_shapes_, 384, 576, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "right_5.png", tex_buildings_shapes_, 576, 576, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "right_6.png", tex_buildings_shapes_, 768, 576, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "right_7.png", tex_buildings_shapes_, 960, 576, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "right_8.png", tex_buildings_shapes_, 1152, 576, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "right_9.png", tex_buildings_shapes_, 1344, 576, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "right_10.png", tex_buildings_shapes_, 1536, 576, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "right_11.png", tex_buildings_shapes_, 1728, 576, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "right_12.png", tex_buildings_shapes_, 0, 768, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "right_13.png", tex_buildings_shapes_, 192, 768, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "hub.png", tex_buildings_shapes_, 384, 768, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "miner.png", tex_buildings_shapes_, 1152, 768, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "miner-chainable.png", tex_buildings_shapes_, 1344, 768, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "rotater.png", tex_buildings_shapes_, 1536, 768, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "trash.png", tex_buildings_shapes_, 1728, 768, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "underground_belt_entry.png", tex_buildings_shapes_, 0, 960, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "underground_belt_exit.png", tex_buildings_shapes_, 192, 960, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "balancer.png", tex_buildings_shapes_, 1152, 960, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "cutter.png", tex_buildings_shapes_, 1536, 960, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "mixer.png", tex_buildings_shapes_, 0, 1152, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "painter.png", tex_buildings_shapes_, 1152, 1152, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "stacker.png", tex_buildings_shapes_, 1536, 1152, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "balancer_blue.png", tex_buildings_shapes_, 1152, 1344, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "belt_left_blue.png", tex_buildings_shapes_, 1536, 1344, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "belt_right_blue.png", tex_buildings_shapes_, 1728, 1344, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "belt_top_blue.png", tex_buildings_shapes_, 0, 1536, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "cutter_blue.png", tex_buildings_shapes_, 192, 1536, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "miner_blue.png", tex_buildings_shapes_, 576, 1536, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "mixer_blue.png", tex_buildings_shapes_, 768, 1536, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "painter_blue.png", tex_buildings_shapes_, 1152, 1536, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "stacker_blue.png", tex_buildings_shapes_, 1536, 1536, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "rotater_blue.png", tex_buildings_shapes_, 0, 1728, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "trash_blue.png", tex_buildings_shapes_, 192, 1728, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "underground_belt_entry_blue.png", tex_buildings_shapes_, 384, 1728, 2048);
	push_tex(Resouces::root() / "image" / "buildings" / "underground_belt_exit_blue.png", tex_buildings_shapes_, 576, 1728, 2048);
	push_res_tex(Resouces::root() / "image" / "shapes" / "circle.png", tex_buildings_shapes_, 0, 1344, 2048);
	push_res_tex(Resouces::root() / "image" / "shapes" / "rect.png", tex_buildings_shapes_, 72, 1344, 2048);
	push_res_tex(Resouces::root() / "image" / "shapes" / "star.png", tex_buildings_shapes_, 144, 1344, 2048);
	glGenerateMipmap(GL_TEXTURE_2D);

	cout << " Create building texture (blue) alias(2048x2048)..." << endl;

	cout << " Create index buffer" << endl;
	constexpr unsigned int index[6]{0u, 1u, 3u, 1u, 2u, 3u};
	glCreateBuffers(1, &buf_index_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buf_index_);
	glNamedBufferStorage(buf_index_, sizeof index, index, GL_MAP_READ_BIT);

	cout << " Create shared vertex buffer: (4 x 11 x 4 x float)" << endl;
	glCreateBuffers(1, &buf_vertex_);
	glBindBuffer(GL_ARRAY_BUFFER, buf_vertex_);
	glNamedBufferStorage(buf_vertex_, 6464, 0, GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);

	create_program(program_cell_, "cell_border.vert", "cell_border.frag");
	create_program(program_tex_, "tex.vert", "tex.frag");
	create_program(program_tex_alpha_, "tex.vert", "tex_alpha.frag");

	cout << " Create cell vertex object..." << endl;
	glCreateVertexArrays(1, &vao_cell_);
	glBindVertexArray(vao_cell_);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, buf_vertex_);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	cout << " Create tex vertex object..." << endl;
	glCreateVertexArrays(1, &vao_tex_);
	glBindVertexArray(vao_tex_);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, buf_vertex_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buf_index_);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	log_error("all renderer initialize codes");
	cout << "GameRenderer initialize finished." << endl;
}

void GameRenderer::update_env()
{
	glClear(GL_COLOR_BUFFER_BIT);

	if (fneq(width_, current_window->width()) || fneq(height_, current_window->height()))
	{
		width_ = current_window->width();
		height_ = current_window->height();

		glUseProgram(program_tex_);
		glUniform2f(uniform_size_, width_, height_);
		glUseProgram(program_cell_);
		glUniform2f(uniform_size_, width_, height_);
		glUseProgram(program_tex_alpha_);
		glUniform2f(uniform_size_, width_, height_);
	}
}

void GameRenderer::draw(const GameMap& map)
{
	cell_size_ = map.cell_size;

	const float xx = width_ / 2.0f - map.cell_size * map.center.x;
	const float yy = height_ / 2.0f - map.cell_size * map.center.y;
	float px = xx, py = yy;
	x0_ = -1, x1_ = -1, y0_ = -1, y1_ = -1;
	for (int i = 0; i <= 100; ++i, px += map.cell_size)
	{
		edge_pos_[i].x = px;
		if (x0_ == -1 && px + map.cell_size >= 0) x0_ = i;
		if (x1_ == -1 && px + map.cell_size >= width_) x1_ = i == 100 ? 100 : i + 1;
	}
	if (x0_ == -1) x0_ = 0;
	if (x1_ == -1) x1_ = 100;
	for (int i = 0; i <= 100; ++i, py += map.cell_size)
	{
		edge_pos_[i].y = py;
		if (y0_ == -1 && py + map.cell_size >= 0) y0_ = i;
		if (y1_ == -1 && py + map.cell_size >= height_) y1_ = i == 100 ? 100 : i + 1;
	}
	if (y0_ == -1) y0_ = 0;
	if (y1_ == -1) y1_ = 100;

	draw_cells();
	draw_dye_resources(map);
	draw_shape_resources(map);
}

void GameRenderer::draw_cells() const
{
	glUseProgram(program_cell_);
	glBindVertexArray(vao_cell_);

	auto buf = static_cast<float*>(glMapNamedBuffer(buf_vertex_, GL_WRITE_ONLY));
	for (int i = x0_; i <= x1_; i++)
	{
		// edge_pos_[i].x, edge_pos_[y0].y, edge_pos_[i].x, edge_pos_[y1].y
		*buf++ = edge_pos_[i].x;
		*buf++ = edge_pos_[y0_].y;
		*buf++ = edge_pos_[i].x;
		*buf++ = edge_pos_[y1_].y;
	}
	glUnmapNamedBuffer(buf_vertex_);
	glDrawArrays(GL_LINES, 0, 2 * (x1_ - x0_ + 1));

	buf = static_cast<float*>(glMapNamedBuffer(buf_vertex_, GL_WRITE_ONLY));
	for (int i = y0_; i <= y1_; i++)
	{
		// edge_pos_[x0].x, edge_pos_[i].y, edge_pos_[x1].x, edge_pos_[i].y
		*buf++ = edge_pos_[x0_].x;
		*buf++ = edge_pos_[i].y;
		*buf++ = edge_pos_[x1_].x;
		*buf++ = edge_pos_[i].y;
	}
	glUnmapNamedBuffer(buf_vertex_);
	glDrawArrays(GL_LINES, 0, 2 * (y1_ - y0_ + 1));
	log_error("draw_cells");
}

void GameRenderer::draw_dye_resources(const GameMap& map)
{
	glUseProgram(program_tex_alpha_);
	glBindVertexArray(vao_tex_);
	glUniform1f(uniform_alpha_, 0.8f);

	glUniform1i(uniform_tex_, texture_icons_colors_);
	for (int i = x0_; i < x1_; i++)
	{
		int cnt = 0;
		auto buf = static_cast<float*>(glMapNamedBuffer(buf_vertex_, GL_WRITE_ONLY));
		for (int j = y0_; j < y1_; ++j)
		{
			if (const ResourceType& res = map.get_resource(j, i); res.is_color)
			{
				const auto& [u, v, w, h] = alias_[tex_icons_colors_][res.name];
				cnt++;
				*buf++ = edge_pos_[i].x;
				*buf++ = edge_pos_[j].y;
				*buf++ = u;
				*buf++ = v;
				*buf++ = edge_pos_[i].x;
				*buf++ = edge_pos_[j + 1].y;
				*buf++ = u + w;
				*buf++ = v;
				*buf++ = edge_pos_[i + 1].x;
				*buf++ = edge_pos_[j + 1].y;
				*buf++ = u + w;
				*buf++ = v + h;
				*buf++ = edge_pos_[i + 1].x;
				*buf++ = edge_pos_[j].y;
				*buf++ = u;
				*buf++ = v + h;
			}
		}
		glUnmapNamedBuffer(buf_vertex_);
		if (cnt)
			glDrawElements(GL_TRIANGLES, 6 * cnt, GL_UNSIGNED_INT, 0);
	}
	log_error("draw_dye_resources");
}

void GameRenderer::draw_shape_resources(const GameMap& map)
{
	glUseProgram(program_tex_alpha_);
	glBindVertexArray(vao_tex_);
	glUniform1f(uniform_alpha_, 0.8f);

	glUniform1i(uniform_tex_, texture_buildings_shapes_);
	for (int i = x0_; i < x1_; i++)
	{
		int cnt = 0;
		auto buf = static_cast<float*>(glMapNamedBuffer(buf_vertex_, GL_WRITE_ONLY));
		for (int j = y0_; j < y1_; ++j)
		{
			if (const ResourceType& res = map.get_resource(j, i); res.is_shape)
			{
				const auto& [u, v, w, h] = alias_[tex_buildings_shapes_][res.name];
				cnt++;
				*buf++ = edge_pos_[i].x;
				*buf++ = edge_pos_[j].y;
				*buf++ = u;
				*buf++ = v;
				*buf++ = edge_pos_[i].x;
				*buf++ = edge_pos_[j + 1].y;
				*buf++ = u + w;
				*buf++ = v;
				*buf++ = edge_pos_[i + 1].x;
				*buf++ = edge_pos_[j + 1].y;
				*buf++ = u + w;
				*buf++ = v + h;
				*buf++ = edge_pos_[i + 1].x;
				*buf++ = edge_pos_[j].y;
				*buf++ = u;
				*buf++ = v + h;
			}
		}
		glUnmapNamedBuffer(buf_vertex_);
		if (cnt)
			glDrawElements(GL_TRIANGLES, 6 * cnt, GL_UNSIGNED_INT, 0);
	}
	log_error("draw_shape_resources");
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

void GameRenderer::create_gl_texture(GLuint* tex, const int slot, const int width, const int height)
{
	glActiveTexture(slot);
	glCreateTextures(GL_TEXTURE_2D, 1, tex);
	glBindTexture(GL_TEXTURE_2D, *tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
}

void GameRenderer::push_tex(const path& p, const GLuint tex, const GLint off_x, const GLint off_y, const float size)
{
	cout << "  Loading image " << p.string() << endl;
	const Image image = Resouces::load_image(p);
	glTextureSubImage2D(tex, 0, off_x, off_y, image.width, image.height, GL_RGBA, GL_UNSIGNED_BYTE, image.data);
	alias_[tex][p.filename().string()] = {off_x / size, off_y / size, image.width / size, image.height / size};
}

void GameRenderer::push_res_tex(const path& p, const GLuint tex, const GLint off_x, const GLint off_y, const float size)
{
	cout << "  Loading image " << p.string() << endl;
	const Image image = Resouces::load_image(p);
	glTextureSubImage2D(tex, 0, off_x, off_y, image.width, image.height, GL_RGBA, GL_UNSIGNED_BYTE, image.data);
	const float x0 = off_x, x1 = x0 + image.width / 2.0f;
	const float y0 = off_y, y1 = y0 + image.height / 2.0f;
	const string filename = p.filename().string();
	alias_[tex][filename] = {off_x / size, off_y / size, image.width / size, image.height / size};
	alias_[tex][filename + "_lt"] = {x0 / size, y0 / size, image.width / 2 / size, image.height / 2 / size};
	alias_[tex][filename + "_rt"] = {x1 / size, y0 / size, image.width / 2 / size, image.height / 2 / size};
	alias_[tex][filename + "_lb"] = {x0 / size, y1 / size, image.width / 2 / size, image.height / 2 / size};
	alias_[tex][filename + "_rb"] = {x1 / size, y1 / size, image.width / 2 / size, image.height / 2 / size};
}

void GameRenderer::create_program(GLuint& program, string&& vert, string&& frag)
{
	cout << " Create program with " << vert << " and " << frag << "..." << endl;
	program = glCreateProgram();
	const path vp = Resouces::root() / "glsl" / vert;
	cout << "  Loading shader " << vp.string() << endl;
	const GLuint sp = create_shader(GL_VERTEX_SHADER, vp);
	const path vf = Resouces::root() / "glsl" / frag;
	cout << "  Loading shader " << vf.string() << endl;
	const GLuint sf = create_shader(GL_FRAGMENT_SHADER, vf);
	glAttachShader(program, sp);
	glAttachShader(program, sf);
	glLinkProgram(program);
	glDetachShader(program, sp);
	glDetachShader(program, sf);
	glDeleteShader(sp);
	glDeleteShader(sf);
	GLint param;
	glGetProgramiv(program, GL_LINK_STATUS, &param);
	if (param != GL_TRUE)
	{
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &param);
		const auto msg = new GLchar[param + 1];
		glGetProgramInfoLog(program, param, &param, msg);
		glDeleteProgram(program);
		program = 0;
		cerr << msg << endl;
		delete[] msg;
	}
}

GLuint GameRenderer::create_shader(const GLenum type, const path& p)
{
	const auto [len, str] = Resouces::read_text(p);
	const GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &str, reinterpret_cast<const GLint*>(&len));
	glCompileShader(shader);

	GLint param;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &param);
	if (param != GL_TRUE)
	{
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &param);
		const auto info = new GLchar[param + 1];
		glGetShaderInfoLog(shader, param, &param, info);
		cerr << info << endl;
		glDeleteShader(shader);
		return 0;
	}
	return shader;
}
