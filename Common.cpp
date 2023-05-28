#include "common.h"

#include <exception>
#include <iostream>
#include <glad/glad.h>

GameLogic* current_game = nullptr;
GameWindow* current_window = nullptr;
GameRenderer* current_renderer = nullptr;

void log_error(const char* name)
{
	using std::cerr;
	using std::endl;

	const GLenum error = glGetError();
	if (error == GL_NO_ERROR)return;
	switch (error)
	{
	case GL_INVALID_ENUM:
		cerr << "Found error in " << name << ": " << "GL_INVALID_ENUM" << endl;
		break;
	case GL_INVALID_VALUE:
		cerr << "Found error in " << name << ": " << "GL_INVALID_VALUE" << endl;
		break;
	case GL_INVALID_OPERATION:
		cerr << "Found error in " << name << ": " << "GL_INVALID_OPERATION" << endl;
		break;
	case GL_INVALID_FRAMEBUFFER_OPERATION:
		cerr << "Found error in " << name << ": " << "GL_INVALID_FRAMEBUFFER_OPERATION" << endl;
		break;
	case GL_OUT_OF_MEMORY:
		cerr << "Found error in " << name << ": " << "GL_OUT_OF_MEMORY" << endl;
		break;
	case GL_STACK_UNDERFLOW:
		cerr << "Found error in " << name << ": " << "GL_STACK_UNDERFLOW" << endl;
		break;
	case GL_STACK_OVERFLOW:
		cerr << "Found error in " << name << ": " << "GL_STACK_OVERFLOW" << endl;
		break;
	default:
		cerr << "Found error in " << name << ": " << "Unknown error code" << endl;
		break;
	}

	throw std::exception("GL ERROR!");
}
