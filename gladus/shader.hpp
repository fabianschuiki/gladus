/* Copyright (c) 2013 Fabian Schuiki */
#pragma once
#include "error.hpp"
#include <string>
#include <vector>
#define GLADUS_HAS_SHADER

namespace gladus {

/** Result of a shader compilation. If success is false, the shader's info log
 * is stored in the info member for the caller's convenience. The class has an
 * implicit cast to bool, allowing straightforward use in actual code. */
struct shader_compile_result
{
	bool success;
	std::string info;

	shader_compile_result(bool success): success(success) {}
	template <typename T> shader_compile_result(bool success, const T& info): success(success), info(info) {}
	operator bool() const { return success; }
};

/** A shader, usually attached and linked in a gladus::program. */
struct shader
{
	GLuint id;
	GLenum type;

	shader(GLenum type): id(0), type(type) { id = glCreateShader(type); throw_on_opengl_error(); }
	shader(GLenum type, GLuint id): id(id), type(type) {}
	~shader() { if (id > 0) glDeleteShader(id); throw_on_opengl_error(); }

	operator GLuint() const { return id; }

	void source(const GLchar* src, GLint length) const
	{
		assert(id > 0);
		clear_opengl_error();
		glShaderSource(id, 1, &src, &length);
		incase_opengl_error(err) {
			case GL_INVALID_OPERATION: throw runtime_error("shader: failed to assign source: 'id' is not a shader", err);
			case GL_INVALID_VALUE: throw runtime_error("shader: failed to assign source: 'id' is not a previously created shader", err);
			case GL_INVALID_ENUM: throw runtime_error("shader: failed to assign source: 'type' is not one of the allowed values", err);
			default: throw err;
		}
	}

	shader_compile_result compile() const
	{
		assert(id > 0);
		clear_opengl_error();
		glCompileShader(id);
		incase_opengl_error(err) {
			case GL_INVALID_VALUE: throw runtime_error("shader: failed to compile: 'id' is not a previously created shader", err);
			case GL_INVALID_OPERATION: throw runtime_error("shader: failed to compile: 'id' is not a shader", err);
			default: throw err;
		}

		GLint success;
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
		if (!success) {
			GLint length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			std::vector<GLchar> info; info.resize(length);
			glGetShaderInfoLog(id, info.size(), NULL, &info[0]);
			return shader_compile_result(false, &info[0]);
		}
		return shader_compile_result(true);
	}
};

} // namespace gladus

namespace gl {
	typedef gladus::shader Shader;
}
