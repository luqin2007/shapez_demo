#pragma once

#include <string>
#include <iostream>
#include <filesystem>

#include <glad/glad.h>

#include "Resouces.h"

using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::filesystem::path;

class AbstractDrawer
{
public:
	void resize(GLfloat width, GLfloat height) const;

protected:
	GLuint program_ = 0;

	void create_program(GLuint& program, string&& vert, string&& frag) const;

	GLuint create_shader(const GLenum type, const path& p) const;
};

