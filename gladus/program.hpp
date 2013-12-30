/* Copyright (c) 2013 Fabian Schuiki */
#pragma once
#include "error.hpp"
#define GLADUS_HAS_PROGRAM

namespace gladus {

/** Result of a program linking operation. If success is false, the program's
 * info log is stored in the info member for the caller's convenience. The
 * class has an implicit cast to bool, allowing straightforward use in actual
 * code. */
struct program_link_result
{
	bool success;
	std::string info;

	program_link_result(bool success): success(success) {}
	template <typename T> program_link_result(bool success, const T& info): success(success), info(info) {}
	operator bool() const { return success; }
};

/* A program, i.e. a linked set of shaders. */
struct program
{
	GLuint id;

	program() { id = glCreateProgram(); throw_on_opengl_error(); }
	program(GLuint id): id(id) { assert(glIsProgram(id)); }
	~program() { if (id > 0) glDeleteProgram(id); throw_on_opengl_error(); }

	operator GLuint() const { return id; }

	void attach(GLuint shader_id) const
	{
		assert(id > 0);
		clear_opengl_error();
		glAttachShader(id, shader_id);
		incase_opengl_error(err) {
			case GL_INVALID_VALUE: throw runtime_error("program: failed to attach: 'id' or 'shader_id' is not a previously created program/shader", err);
			case GL_INVALID_OPERATION: throw runtime_error("program: failed to attach: 'id' or 'shader_id' is not a program/shader, or the shader is already attached to the program", err);
			default: throw err;
		}
	}

	void detach(GLuint shader_id) const
	{
		assert(id > 0);
		clear_opengl_error();
		glDetachShader(id, shader_id);
		incase_opengl_error(err) {
			case GL_INVALID_VALUE: throw runtime_error("program: failed to detach: 'id' or 'shader_id' is not a previously created program/shader", err);
			case GL_INVALID_OPERATION: throw runtime_error("program: failed to detach: 'id' or 'shader_id' is not a program/shader, or the shader is was not attached to the program", err);
			default: throw err;
		}
	}

	program_link_result link()
	{
		assert(id > 0);
		clear_opengl_error();
		glLinkProgram(id);
		incase_opengl_error(err1) {
			case GL_INVALID_VALUE: throw runtime_error("program: failed to link: 'id' is not a previously created program", err1);
			case GL_INVALID_OPERATION: throw runtime_error("program: failed to link: 'id' is not a program", err1);
			default: throw err1;
		}

		#define extract_info_log(info)\
			std::vector<GLchar> info; {\
				GLint length;\
				glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length); info.resize(length);\
				glGetProgramInfoLog(id, info.size(), NULL, &info[0]);\
			}

		GLint success;
		glGetProgramiv(id, GL_LINK_STATUS, &success);
		if (!success) {
			extract_info_log(info);
			return program_link_result(false, &info[0]);
		}

		#ifndef GLADUS_DONT_VALIDATE_PROGRAMS
		glValidateProgram(id);
		incase_opengl_error(err2) {
			case GL_INVALID_VALUE: throw runtime_error("program: failed to validate: 'id' is not a previously created program", err2);
			case GL_INVALID_OPERATION: throw runtime_error("program: failed to validate: 'id' is not a program", err2);
			default: throw err2;
		}

		glGetProgramiv(id, GL_VALIDATE_STATUS, &success);
		if (!success) {
			extract_info_log(info);
			return program_link_result(false, &info[0]);
		}
		#endif

		#undef extract_info_log
		return program_link_result(true);
	}

	void use() const
	{
		assert(id > 0);
		clear_opengl_error();
		glUseProgram(id);
		incase_opengl_error(err) {
			case GL_INVALID_VALUE: throw runtime_error("program: failed to use: 'id' is neither 0 nor a previously created program", err);
			case GL_INVALID_OPERATION: throw runtime_error("program: failed to use: 'id' is not a program or failed to be made part of the current state", err);
			default: throw err;
		}
	}

	void unuse() const
	{
		clear_opengl_error();
		glUseProgram(0);
		throw_on_opengl_error();
	}
};

} // namespace gladus

namespace gl {
	typedef gladus::program Program;
}
