// #include "FontDrawer.h"
//
// #include "GameWindow.h"
// #include "Common.h"
//
// void FontDrawer::initialize()
// {
// 	if (const FT_Error fe = FT_Init_FreeType(&ft_))
// 	{
// 		cerr << " Failed to initialize freetype library, error code=" << fe << endl;
// 	}
//
// 	glCreateBuffers(1, &buffer_);
// 	glBindBuffer(GL_ARRAY_BUFFER, buffer_);
// 	glNamedBufferStorage(buffer_, 4 * sizeof(float) * 4, 0, GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);
//
// 	create_program(program_, "font.vert", "font.frag", false);
// 	glUseProgram(program_);
// 	glUniform1i(1, texture_id_);
// 	glCreateVertexArrays(1, &vao_);
// 	glBindVertexArray(vao_);
// 	bind_indices();
// 	glBindBuffer(GL_ARRAY_BUFFER, buffer_);
// 	glEnableVertexAttribArray(0);
// 	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
//
// 	texture_id_ = next_texture_id();
// }
//
// void FontDrawer::draw(const string &str, const int font_size, const float x, const float y,
//                       const float r, const float g, const float b, const float a)
// {
// 	const float scale_x = current_window->width() / 1024.0f;
// 	const float scale_y = current_window->height() / 768.0f;
//
// 	FT_Face face;
// 	FT_New_Face(ft_, font_path_.string().c_str(), 0, &face);
// 	FT_Set_Pixel_Sizes(face, static_cast<FT_UInt>(font_size * scale_x), static_cast<FT_UInt>(font_size * scale_y));
//
// 	for (const char ch : str)
// 		if (auto err = FT_Load_Char(face, FT_Load_Char(face, ch, FT_LOAD_RENDER), FT_LOAD_RENDER))
// 			cerr << "Failed to load char " << ch << endl;
//
// 	const auto glyph = face->glyph;
// 	const auto width = glyph->bitmap.width;
// 	const auto height = glyph->bitmap.rows;
//
// 	glActiveTexture(GL_TEXTURE0 + texture_id_);
// 	if (texture_)
// 	{
// 		glBindTexture(GL_TEXTURE_2D, 0);
// 		glDeleteTextures(1, &texture_);
// 	}
// 	glCreateTextures(GL_TEXTURE_2D, 1, &texture_);
// 	glBindTexture(GL_TEXTURE_2D, texture_);
// 	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
// 	glUseProgram(program_);
// 	glBindVertexArray(vao_);
// 	glUniform4f(0, r, g, b, a);
// 	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
//
// 	FT_Done_Face(face);
//
// 	const float w = width * scale_x;
// 	const float h = height * scale_y;
//
// 	auto buf = static_cast<float*>(glMapNamedBuffer(buffer_, GL_WRITE_ONLY));
// 	*buf++ = x;
// 	*buf++ = y;
// 	*buf++ = 0;
// 	*buf++ = 0;
//
// 	*buf++ = x;
// 	*buf++ = y + h;
// 	*buf++ = 0;
// 	*buf++ = 1;
//
// 	*buf++ = x + w;
// 	*buf++ = y + h;
// 	*buf++ = 1;
// 	*buf++ = 1;
//
// 	*buf++ = x + w;
// 	*buf++ = y;
// 	*buf++ = 1;
// 	*buf = 0;
// 	glUnmapNamedBuffer(buffer_);
// 	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
// }
//
// void FontDrawer::destroy() const
// {
// 	glUseProgram(0);
// 	glBindVertexArray(0);
// 	glBindBuffer(GL_ARRAY_BUFFER, 0);
// 	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
// 	glDeleteBuffers(1, &buffer_);
//
// 	if (texture_)
// 	{
// 		glActiveTexture(GL_TEXTURE0 + texture_id_);
// 		glBindTexture(GL_TEXTURE_2D, 0);
// 		glDeleteTextures(1, &texture_);
// 		glActiveTexture(GL_TEXTURE0);
// 	}
//
// 	FT_Done_FreeType(ft_);
// }
