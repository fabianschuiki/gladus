/* Copyright (c) 2013 Fabian Schuiki */
#pragma once
#include "error.hpp"
#include <map>
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

	program_link_result() {}
	program_link_result(bool success): success(success) {}
	template <typename T> program_link_result(bool success, const T& info): success(success), info(info) {}
	operator bool() const { return success; }
};

struct program_uniform
{
	GLint location;
	program_uniform() {}
	program_uniform(GLint location): location(location) {}
	operator GLint() const { return location; }

	void sampler(GLuint v) const { glUniform1i(location, v); throw_on_program_opengl_error(); }
	void sampler(GLsizei n, const GLuint* v) const { glUniform1iv(location, n, (const GLint*)v); throw_on_program_opengl_error(); }

	void f(GLfloat v0) const { glUniform1f(location, v0); throw_on_program_opengl_error(); }
	void f(GLfloat v0, GLfloat v1) const { glUniform2f(location, v0, v1); throw_on_program_opengl_error(); }
	void f(GLfloat v0, GLfloat v1, GLfloat v2) const { glUniform3f(location, v0, v1, v2); throw_on_program_opengl_error(); }
	void f(GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) const { glUniform4f(location, v0, v1, v2, v3); throw_on_program_opengl_error(); }

	void i(GLint v0) const { glUniform1i(location, v0); throw_on_program_opengl_error(); }
	void i(GLint v0, GLint v1) const { glUniform2i(location, v0, v1); throw_on_program_opengl_error(); }
	void i(GLint v0, GLint v1, GLint v2) const { glUniform3i(location, v0, v1, v2); throw_on_program_opengl_error(); }
	void i(GLint v0, GLint v1, GLint v2, GLint v3) const { glUniform4i(location, v0, v1, v2, v3); throw_on_program_opengl_error(); }

	void ui(GLuint v0) const { glUniform1ui(location, v0); throw_on_program_opengl_error(); }
	void ui(GLuint v0, GLuint v1) const { glUniform2ui(location, v0, v1); throw_on_program_opengl_error(); }
	void ui(GLuint v0, GLuint v1, GLuint v2) const { glUniform3ui(location, v0, v1, v2); throw_on_program_opengl_error(); }
	void ui(GLuint v0, GLuint v1, GLuint v2, GLuint v3) const { glUniform4ui(location, v0, v1, v2, v3); throw_on_program_opengl_error(); }

	void fv1(const GLfloat* v) const { glUniform1fv(location, 1, v); throw_on_program_opengl_error(); }
	void fv2(const GLfloat* v) const { glUniform2fv(location, 1, v); throw_on_program_opengl_error(); }
	void fv3(const GLfloat* v) const { glUniform3fv(location, 1, v); throw_on_program_opengl_error(); }
	void fv4(const GLfloat* v) const { glUniform4fv(location, 1, v); throw_on_program_opengl_error(); }

	void iv1(const GLint* v) const { glUniform1iv(location, 1, v); throw_on_program_opengl_error(); }
	void iv2(const GLint* v) const { glUniform2iv(location, 1, v); throw_on_program_opengl_error(); }
	void iv3(const GLint* v) const { glUniform3iv(location, 1, v); throw_on_program_opengl_error(); }
	void iv4(const GLint* v) const { glUniform4iv(location, 1, v); throw_on_program_opengl_error(); }

	void uiv1(const GLuint* v) const { glUniform1uiv(location, 1, v); throw_on_program_opengl_error(); }
	void uiv2(const GLuint* v) const { glUniform2uiv(location, 1, v); throw_on_program_opengl_error(); }
	void uiv3(const GLuint* v) const { glUniform3uiv(location, 1, v); throw_on_program_opengl_error(); }
	void uiv4(const GLuint* v) const { glUniform4uiv(location, 1, v); throw_on_program_opengl_error(); }

	void fv1(GLsizei n, const GLfloat* v) const { glUniform1fv(location, n, v); throw_on_program_opengl_error(); }
	void fv2(GLsizei n, const GLfloat* v) const { glUniform2fv(location, n, v); throw_on_program_opengl_error(); }
	void fv3(GLsizei n, const GLfloat* v) const { glUniform3fv(location, n, v); throw_on_program_opengl_error(); }
	void fv4(GLsizei n, const GLfloat* v) const { glUniform4fv(location, n, v); throw_on_program_opengl_error(); }

	void iv1(GLsizei n, const GLint* v) const { glUniform1iv(location, n, v); throw_on_program_opengl_error(); }
	void iv2(GLsizei n, const GLint* v) const { glUniform2iv(location, n, v); throw_on_program_opengl_error(); }
	void iv3(GLsizei n, const GLint* v) const { glUniform3iv(location, n, v); throw_on_program_opengl_error(); }
	void iv4(GLsizei n, const GLint* v) const { glUniform4iv(location, n, v); throw_on_program_opengl_error(); }

	void uiv1(GLsizei n, const GLuint* v) const { glUniform1uiv(location, n, v); throw_on_program_opengl_error(); }
	void uiv2(GLsizei n, const GLuint* v) const { glUniform2uiv(location, n, v); throw_on_program_opengl_error(); }
	void uiv3(GLsizei n, const GLuint* v) const { glUniform3uiv(location, n, v); throw_on_program_opengl_error(); }
	void uiv4(GLsizei n, const GLuint* v) const { glUniform4uiv(location, n, v); throw_on_program_opengl_error(); }

	void matrix2(const GLfloat* v, GLboolean transpose = false) const { glUniformMatrix2fv(location, 1, transpose, v); throw_on_program_opengl_error(); }
	void matrix3(const GLfloat* v, GLboolean transpose = false) const { glUniformMatrix3fv(location, 1, transpose, v); throw_on_program_opengl_error(); }
	void matrix4(const GLfloat* v, GLboolean transpose = false) const { glUniformMatrix4fv(location, 1, transpose, v); throw_on_program_opengl_error(); }

	void matrix2(GLsizei n, const GLfloat* v, GLboolean transpose = false) const { glUniformMatrix2fv(location, n, transpose, v); throw_on_program_opengl_error(); }
	void matrix3(GLsizei n, const GLfloat* v, GLboolean transpose = false) const { glUniformMatrix3fv(location, n, transpose, v); throw_on_program_opengl_error(); }
	void matrix4(GLsizei n, const GLfloat* v, GLboolean transpose = false) const { glUniformMatrix4fv(location, n, transpose, v); throw_on_program_opengl_error(); }

	void matrix2x3(const GLfloat* v, GLboolean transpose = false) const { glUniformMatrix2x3fv(location, 1, transpose, v); throw_on_program_opengl_error(); }
	void matrix2x4(const GLfloat* v, GLboolean transpose = false) const { glUniformMatrix2x4fv(location, 1, transpose, v); throw_on_program_opengl_error(); }
	void matrix3x2(const GLfloat* v, GLboolean transpose = false) const { glUniformMatrix3x2fv(location, 1, transpose, v); throw_on_program_opengl_error(); }
	void matrix3x4(const GLfloat* v, GLboolean transpose = false) const { glUniformMatrix3x4fv(location, 1, transpose, v); throw_on_program_opengl_error(); }
	void matrix4x2(const GLfloat* v, GLboolean transpose = false) const { glUniformMatrix4x2fv(location, 1, transpose, v); throw_on_program_opengl_error(); }
	void matrix4x3(const GLfloat* v, GLboolean transpose = false) const { glUniformMatrix4x3fv(location, 1, transpose, v); throw_on_program_opengl_error(); }

	void matrix2x3(GLsizei n, const GLfloat* v, GLboolean transpose = false) const { glUniformMatrix2x3fv(location, n, transpose, v); throw_on_program_opengl_error(); }
	void matrix2x4(GLsizei n, const GLfloat* v, GLboolean transpose = false) const { glUniformMatrix2x4fv(location, n, transpose, v); throw_on_program_opengl_error(); }
	void matrix3x2(GLsizei n, const GLfloat* v, GLboolean transpose = false) const { glUniformMatrix3x2fv(location, n, transpose, v); throw_on_program_opengl_error(); }
	void matrix3x4(GLsizei n, const GLfloat* v, GLboolean transpose = false) const { glUniformMatrix3x4fv(location, n, transpose, v); throw_on_program_opengl_error(); }
	void matrix4x2(GLsizei n, const GLfloat* v, GLboolean transpose = false) const { glUniformMatrix4x2fv(location, n, transpose, v); throw_on_program_opengl_error(); }
	void matrix4x3(GLsizei n, const GLfloat* v, GLboolean transpose = false) const { glUniformMatrix4x3fv(location, n, transpose, v); throw_on_program_opengl_error(); }

	inline void throw_on_program_opengl_error() const
	{
		incase_opengl_error(err) {
			case GL_INVALID_OPERATION: throw runtime_error("program: failed to assign uniform: size of variable in the program source doesn't match, or data type doesn't match, or the location is invalid", err);
			case GL_INVALID_VALUE: throw runtime_error("program: failed to assign uniform: 'n' is negative", err);
			default: throw err;
		}
	}

	// compatibility with gamma vectors
	#ifdef GAMMA_HAS_VECTOR
	void vectorf(const gamma::vector2<GLfloat>& v) const { fv2(v); }
	void vectorf(const gamma::vector3<GLfloat>& v) const { fv3(v); }
	void vectorf(const gamma::vector4<GLfloat>& v) const { fv4(v); }

	void vectori(const gamma::vector2<GLint>& v) const { iv2(v); }
	void vectori(const gamma::vector3<GLint>& v) const { iv3(v); }
	void vectori(const gamma::vector4<GLint>& v) const { iv4(v); }

	void vectorui(const gamma::vector2<GLuint>& v) const { uiv2(v); }
	void vectorui(const gamma::vector3<GLuint>& v) const { uiv3(v); }
	void vectorui(const gamma::vector4<GLuint>& v) const { uiv4(v); }
	#endif

	// // compatibility with gamma matrices
	#ifdef GAMMA_HAS_MATRIX
	void matrix(const gamma:matrix2<GLfloat>& v) const { matrix2(v, false); }
	void matrix(const gamma:matrix3<GLfloat>& v) const { matrix3(v, false); }
	void matrix(const gamma:matrix4<GLfloat>& v) const { matrix4(v, false); }
	#endif
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

		uniform_location_cache.clear();
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

	const GLint& uniform_location(const std::string& name)
	{
		assert(id > 0);
		std::map<std::string, GLint>::iterator it = uniform_location_cache.find(name);
		if (it == uniform_location_cache.end()) {
			GLint& loc = uniform_location_cache[name];
			loc = glGetUniformLocation(id, name.c_str());
			return loc;
		}
		return it->second;
	}

	program_uniform uniform(const std::string& name) { return program_uniform(uniform_location(name)); }

private:
	std::map<std::string, GLint> uniform_location_cache;
};

} // namespace gladus

namespace gl {
	typedef gladus::program Program;
}
