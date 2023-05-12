#include "AbstractDrawer.h"

void AbstractDrawer::resize(const GLfloat width, const GLfloat height) const
{
	if (program_)
	{
		glUseProgram(program_);
		glUniform2f(0, width, height);
	}
}

void AbstractDrawer::create_program(GLuint& program, string&& vert, string&& frag) const
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

GLuint AbstractDrawer::create_shader(const GLenum type, const path& p) const
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
