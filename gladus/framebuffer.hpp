/* Copyright (c) 2013 Fabian Schuiki */
#pragma once
#include "error.hpp"
#include "binding.hpp"
#define GLADUS_HAS_FRAMEBUFFER

namespace gladus {

struct framebuffer_validation_result
{
	GLint status;
	std::string info;

	framebuffer_validation_result() {}
	framebuffer_validation_result(GLint status): status(status) {}
	template <typename T> framebuffer_validation_result(GLint status, const T& info): status(status), info(info) {}
	operator bool() const { return status == GL_FRAMEBUFFER_COMPLETE; }
};

struct framebuffer
{
	GLuint id;
	GLenum target;

	framebuffer(): target(0) { glGenFramebuffers(1, &id); throw_on_opengl_error(); }
	framebuffer(GLenum target): target(target) { glGenFramebuffers(1, &id); throw_on_opengl_error(); }
	framebuffer(GLenum target, GLuint id): target(target), id(id) { assert(glIsFramebuffer(id)); }
	~framebuffer() { if (id > 0) glDeleteFramebuffers(1, &id); throw_on_opengl_error(); }

	operator GLuint() const { return id; }

	void bind() const
	{
		assert(id > 0);
		clear_opengl_error();
		glBindFramebuffer(target, id);
		incase_opengl_error(err) {
			case GL_INVALID_ENUM: throw runtime_error("framebuffer: failed to bind: 'target' is not one of the allowed values", err);
			case GL_INVALID_OPERATION: throw runtime_error("framebuffer: failed to bind: 'id' is neither 0 nor a previously allocated framebuffer name", err);
			default: throw err;
		}
	}

	void unbind() const
	{
		clear_opengl_error();
		glBindFramebuffer(target, 0);
		throw_on_opengl_error();
	}

	#ifdef GL_VERSION_3_2
	void attach(GLenum attachment, GLuint texture_id, GLint level) { scoped_bind<framebuffer> bound(*this); glFramebufferTexture(target, attachment, texture_id, level); throw_on_texture_opengl_error(); }
	#endif
	void attach1d(GLenum attachment, GLenum texture_target, GLuint texture_id, GLint level) { scoped_bind<framebuffer> bound(*this); glFramebufferTexture1D(target, attachment, texture_target, texture_id, level); throw_on_texture_opengl_error(); }
	void attach2d(GLenum attachment, GLenum texture_target, GLuint texture_id, GLint level) { scoped_bind<framebuffer> bound(*this); glFramebufferTexture2D(target, attachment, texture_target, texture_id, level); throw_on_texture_opengl_error(); }
	void attach3d(GLenum attachment, GLenum texture_target, GLuint texture_id, GLint level, GLint layer) { scoped_bind<framebuffer> bound(*this); glFramebufferTexture3D(target, attachment, texture_target, texture_id, level, layer); throw_on_texture_opengl_error(); }

	#ifdef GLADUS_HAS_TEXTURE
	#ifdef GL_VERSION_3_2
	void attach(GLenum attachment, const texture& tex, GLint level) { attach(attachment, tex, level); }
	#endif
	void attach1d(GLenum attachment, const texture& tex, GLint level) { attach1d(attachment, tex.target, tex, level); }
	void attach2d(GLenum attachment, const texture& tex, GLint level) { attach2d(attachment, tex.target, tex, level); }
	void attach3d(GLenum attachment, const texture& tex, GLint level, GLint layer) { attach3d(attachment, tex.target, tex, level, layer); }
	#endif

	framebuffer_validation_result validate()
	{
		scoped_bind<framebuffer> bound(*this);
		GLint status = glCheckFramebufferStatus(target);
		incase_opengl_error(err) {
			case GL_INVALID_ENUM: throw runtime_error("framebuffer: failed to validate: 'target' is not one of the allowed values", err);
			default: throw err;
		}

		if (status != GL_FRAMEBUFFER_COMPLETE) {
			const char* message;
			switch (status) {
				case GL_FRAMEBUFFER_UNDEFINED:                     message = "framebuffer undefined: default framebuffer is bound, but it does not exist"; break;
				case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:         message = "incomplete attachment: one or more attachment points are framebuffer-incomplete"; break;
				case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT: message = "missing attachment: framebuffer does not have at least one image attached"; break;
				case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:        message = "incomplete draw buffer"; break;
				case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:        message = "incomplete read buffer"; break;
				case GL_FRAMEBUFFER_UNSUPPORTED:                   message = "framebuffer unsupported: combination of attachments is not supported on this hardware"; break;
				case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:        message = "incomplete multisample"; break;
				#ifdef GL_VERSION_3_2
				case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:      message = "incomplete layer targets"; break;
				#endif
				default: message = "unknown framebuffer status"; break;
			}
			return framebuffer_validation_result(status, message);
		}
		return framebuffer_validation_result(status);
	}

	inline void throw_on_texture_opengl_error()
	{
		incase_opengl_error(err) {
			case GL_INVALID_ENUM: throw runtime_error("framebuffer: failed to attach texture: 'id' is not a previously allocated framebuffer name, or 'attachment' is not one of the allowed attachment points, or 'texture_target' is not one of the allowed values", err);
			case GL_INVALID_VALUE: throw runtime_error("framebuffer: failed to attach texture: 'level' is not 0 and 'texture_id' is not 0", err);
			case GL_INVALID_OPERATION: throw runtime_error("framebuffer: failed to attach texture: default framebuffer is bound, or texture 'texture_id' and 'texture_target' are not compatible", err);
			default: throw err;
		}
	}
};

} // namespace gladus

namespace gl {
	typedef gladus::framebuffer Framebuffer;
}
