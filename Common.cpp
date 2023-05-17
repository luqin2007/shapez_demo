#include "Common.h"

GameLogic* current_game = nullptr;
GameWindow* current_window = nullptr;
GameRenderer* current_renderer = nullptr;

static int image_id = 0;

Side operator++(const Side side)
{
	switch (side)
	{
	case Side::UP: return Side::RIGHT;
	case Side::RIGHT: return Side::DOWN;
	case Side::DOWN: return Side::LEFT;
	case Side::LEFT: return Side::UP;
	}
	return side;
}

Side operator--(const Side side)
{
	switch (side)
	{
	case Side::UP: return Side::LEFT;
	case Side::LEFT: return Side::DOWN;
	case Side::DOWN: return Side::RIGHT;
	case Side::RIGHT: return Side::UP;
	}
	return side;
}

Side operator-(const Side side)
{
	switch (side)
	{
	case Side::UP: return Side::DOWN;
	case Side::DOWN: return Side::UP;
	case Side::LEFT: return Side::RIGHT;
	case Side::RIGHT: return Side::LEFT;
	}
	return side;
}

ivec2 operator+(const ivec2& pos, const Side side)
{
	switch (side)
	{
	case Side::UP:
		return ivec2{pos.x, pos.y + 1};
	case Side::DOWN:
		return ivec2{pos.x, pos.y - 1};
	case Side::LEFT:
		return ivec2{pos.x - 1, pos.y};
	case Side::RIGHT:
		return ivec2{pos.x + 1, pos.y};
	}
	return {pos.x, pos.y};
}

Color* colors[10];

Color::Color(std::string name, const int mix) : name(std::move(name)), mix(mix)
{
	colors[mix] = this;
}

const Color Color::uncolored{"uncolored", 0b000};
const Color Color::red{"red", 0b001};
const Color Color::green{"green", 0b010};
const Color Color::blue{"blue", 0b100};
const Color Color::yellow{"yellow", 0b011};
const Color Color::cyan{"cyan", 0b110};
const Color Color::purple{"purple", 0b101};
const Color Color::white{"white", 0b111};

const Color& Color::operator+(const Color& o) const
{
	return *colors[mix | o.mix];
}

bool Color::operator==(const Color& o) const
{
	return mix == o.mix;
}

bool Color::operator|(const Color& o) const
{
	return mix & o.mix == 0;
}

void log_error(const char* name)
{
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

	throw exception("GL ERROR!");
}

int next_texture_id()
{
	return image_id++;
}

GLsizei ex2(const GLsizei n)
{
	GLsizei nn = 512;
	if (n <= nn)
	{
		while (nn / 2 > n)
		{
			nn /= 2;
		}
	}
	else
	{
		while (nn < n)
		{
			nn *= 2;
		}
	}
	return nn;
}

template<>
void debug_buffer<float>(const GLuint name, int count)
{
	const float *buf = static_cast<float*>(glMapNamedBuffer(name, GL_READ_ONLY));
	cout << "[";
	while (count--)
		cout << *buf++ << " ";
	cout << "]" << endl;
	glUnmapNamedBuffer(name);
}

template<>
void debug_buffer<unsigned int>(const GLuint name, int count)
{
	const unsigned int* buf = static_cast<unsigned int*>(glMapNamedBuffer(name, GL_READ_ONLY));
	cout << "[";
	while (count--)
		cout << *buf++ << " ";
	cout << "]" << endl;
	glUnmapNamedBuffer(name);
}
