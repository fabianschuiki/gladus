/* Copyright (c) 2013 Fabian Schuiki */
#pragma once
#include "error.hpp"
#include "binding.hpp"
#include <cassert>
#define GLADUS_HAS_BUFFER

namespace gladus {

struct buffer
{
	GLuint id;
	GLenum target;
	void* mapped_data;

	buffer(): target(0), mapped_data(NULL) { glGenBuffers(1, &id); }
	buffer(GLenum target): target(target), mapped_data(NULL) { glGenBuffers(1, &id); }
	buffer(GLenum target, GLuint id): target(target), id(id), mapped_data(NULL) {}
	~buffer() { if (id > 0) glDeleteBuffers(1, &id); }

	void bind() const
	{
		assert(target > 0);
		assert(id > 0 && "buffer has no name");
		clear_opengl_error();
		glBindBuffer(target, id);
		incase_opengl_error(err) {
			case GL_INVALID_ENUM:  throw runtime_error("buffer: failed to bind: 'target' is not one of the allowed values", err);
			case GL_INVALID_VALUE: throw runtime_error("buffer: failed to bind: 'id' is not a previously allocated buffer name", err);
			default: throw err;
		}
	}
	void unbind()
	{
		assert(target > 0);
		clear_opengl_error();
		glBindBuffer(target, 0);
		incase_opengl_error(err) {
			case GL_INVALID_ENUM: throw runtime_error("buffer: failed to unbind: 'target' is not one of the allowed values", err);
			default: throw err;
		}
	}

	void data(GLsizeiptr size, const GLvoid* data, GLenum usage) { binding<buffer> bound(*this); glBufferData(target, size, data, usage); }
	void subdata(GLintptr offset, GLsizeiptr size, const GLvoid* data) { binding<buffer> bound(*this); glBufferSubData(target, offset, size, data); }

	void map(GLenum access) {
		assert(!mapped_data && "buffer already mapped");
		binding<buffer> bound(*this);
		mapped_data = glMapBuffer(target, access);
		if (!mapped_data) {
			incase_opengl_error(err) {
				case GL_INVALID_ENUM: throw runtime_error("buffer: failed to map: 'target' or 'access' is not one of the allowed values", err);
				case GL_INVALID_OPERATION: throw runtime_error("buffer: failed to map: no buffers is bound", err);
				default: throw err;
			}
		}
	}
	void unmap() {
		assert(mapped_data && "buffer not mapped");
		binding<buffer> bound(*this);
		if (!glUnmapBuffer(target)) {
			incase_opengl_error(err) {
				case GL_INVALID_ENUM: throw runtime_error("buffer: failed to unmap: 'target' is not one of the allowed values", err);
				case GL_INVALID_OPERATION: throw runtime_error("buffer: failed to map: no buffers is bound", err);
				default: throw err;
			}
		}
	}
};

} // namespace gladus

namespace gl {
typedef gladus::buffer Buffer;
} // namespace gl
