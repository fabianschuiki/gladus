/* Copyright (c) 2013 Fabian Schuiki */
#pragma once
#include "binding.hpp"
#include <cassert>

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

	void bind() const { assert(target > 0); assert(id > 0 && "buffer has no name"); glBindBuffer(target, id); /* handle error here */ }
	void unbind() { assert(target > 0); glBindBuffer(target, 0); }

	void data(GLsizeiptr size, const GLvoid* data, GLenum usage) { binding<buffer> bound(*this); glBufferData(target, size, data, usage); }
	void subdata(GLintptr offset, GLsizeiptr size, const GLvoid* data) { binding<buffer> bound(*this); glBufferSubData(target, offset, size, data); }

	void map(GLenum access) {
		assert(!mapped_data);
		binding<buffer> bound(*this);
		mapped_data = glMapBuffer(target, access);
		if (!mapped_data) /* handle error here */;
	}
	void unmap() {
		assert(mapped_data);
		binding<buffer> bound(*this);
		if (!glUnmapBuffer(target)) /* handle error here */;
	}
};

} // namespace gladus

namespace gl {
typedef gladus::buffer Buffer;
} // namespace gl
