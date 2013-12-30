/* Copyright (c) 2013 Fabian Schuiki */
#pragma once
#include "error.hpp"
#include "state.hpp"
#include "binding.hpp"
#define GLADUS_HAS_TEXTURE

namespace gladus {

struct texture
{
	GLuint id;
	GLenum target;

	texture(): target(0) { glGenTextures(1, &id); }
	texture(GLenum target): target(target) { glGenTextures(1, &id);; }
	texture(GLenum target, GLuint id): target(target), id(id) {}
	~texture() { if (id > 0) glDeleteTextures(1, &id); }

	void bind() const
	{
		assert(target > 0);
		assert(id > 0 && "texture has no name");
		clear_opengl_error();
		glBindTexture(target, id);
		incase_opengl_error(err) {
			case GL_INVALID_ENUM: throw runtime_error("texture: failed to bind: 'target' is not one of the allowed values", err);
			case GL_INVALID_VALUE: throw runtime_error("texture: failed to bind: 'id' is not a previously allocated texture name", err);
			case GL_INVALID_OPERATION: throw runtime_error("texture: failed to bind: texture was previously created with another target", err);
			default: throw err;
		}
	}
	void unbind() const
	{
		assert(target > 0);
		clear_opengl_error();
		glBindTexture(target, 0);
		incase_opengl_error(err) {
			case GL_INVALID_ENUM: throw runtime_error("texture: failed to unbind: 'target' is not one of the allowed values", err);
			default: throw err;
		}
	}

	void set_wrap_params(GLenum wrap = GL_REPEAT) { set_wrap_params(wrap, wrap, wrap); }
	void set_wrap_params(GLenum wrap_s, GLenum wrap_t, GLenum wrap_r)
	{
		state pipeline; pipeline.enable(target);
		binding<texture> bound(*this);
		glTexParameteri(target, GL_TEXTURE_WRAP_S, wrap_s);
		glTexParameteri(target, GL_TEXTURE_WRAP_T, wrap_t);
		glTexParameteri(target, GL_TEXTURE_WRAP_R, wrap_r);
		incase_opengl_error(err) {
			case GL_INVALID_ENUM: throw runtime_error("texture: failed to set wrap params: 'target' or 'wrap_[str]' is not one of the allowed values", err);
			default: throw err;
		}
	}

	void set_filter_params(GLenum filter = GL_LINEAR) { set_filter_params(filter, filter); }
	void set_filter_params(GLenum min_filter, GLenum mag_filter)
	{
		state pipeline; pipeline.enable(target);
		binding<texture> bound(*this);
		glTexParameteri(target, GL_TEXTURE_MIN_FILTER, min_filter);
		glTexParameteri(target, GL_TEXTURE_MAG_FILTER, mag_filter);
		incase_opengl_error(err) {
			case GL_INVALID_ENUM: throw runtime_error("texture: failed to set filter params: 'target' or 'wrap_[str]' is not one of the allowed values", err);
			default: throw err;
		}
	}

	void set_params(GLenum wrap = GL_REPEAT, GLenum filter = GL_LINEAR) { set_wrap_params(wrap); set_filter_params(filter); }
};

} // namespace gladus

namespace gl {
	typedef gladus::texture Texture;
}
