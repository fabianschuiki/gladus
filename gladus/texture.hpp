/* Copyright (c) 2013-2014 Fabian Schuiki */
#pragma once
#include "gladus/error.hpp"
#include "gladus/state.hpp"
#include "gladus/binding.hpp"
#define GLADUS_HAS_TEXTURE

namespace gladus {

/// Description of a memory region containing texture data. This includes the
/// format of the channels, the data type of each channel, the alignment in the
/// memory region and the memory region itself.
struct texture_data
{
	GLenum format;
	GLenum type;
	GLint alignment;
	const GLvoid* data;

	texture_data(): format(0), type(0), alignment(0), data(NULL) {}
	texture_data(GLenum format, GLenum type): format(format), type(type), alignment(0), data(NULL) {}
	template<typename T> texture_data(GLenum format, GLenum type, GLint alignment, const T& data): format(format), type(type), alignment(alignment), data(data) {}
};

/// Description of a texture image. This includes the MIP-level, internal
/// representation, and the size of the image. Note that the size is of generic
/// type to allow for different texture dimensions.
template<typename S> struct texture_image
{
	GLint level;
	GLint internal_format;
	S size;

	texture_image(): level(0), internal_format(0), size() {}
	texture_image(GLint level, GLint internal_format, const S& size): level(level), internal_format(internal_format), size(size) {}
};

/// Description of a subregion of a texture image. This includes the MIP-level,
/// offset within the original image and size of the region. Note that the
/// offset and size are of generic type to allow for different texture
/// dimensions.
template<typename S> struct texture_subimage
{
	GLint level;
	S offset;
	S size;

	texture_subimage(): level(0), offset(), size() {}
	texture_subimage(GLint level, const S& offset, const S& size): level(level), offset(offset), size(size) {}
};

/// A texture of arbitrary dimension.
struct texture
{
	GLenum target;
	GLuint id;

	texture(): target(0) { glGenTextures(1, &id); }
	explicit texture(GLenum target): target(target) { glGenTextures(1, &id); }
	explicit texture(GLenum target, GLuint id): target(target), id(id) {}
	~texture() { if (id > 0) glDeleteTextures(1, &id); }

	operator GLuint() const { return id; }

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
		scoped_bind<texture> bound(*this);
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
		scoped_bind<texture> bound(*this);
		glTexParameteri(target, GL_TEXTURE_MIN_FILTER, min_filter);
		glTexParameteri(target, GL_TEXTURE_MAG_FILTER, mag_filter);
		incase_opengl_error(err) {
			case GL_INVALID_ENUM: throw runtime_error("texture: failed to set filter params: 'target' or 'wrap_[str]' is not one of the allowed values", err);
			default: throw err;
		}
	}

	void set_params(GLenum wrap = GL_REPEAT, GLenum filter = GL_LINEAR) { set_wrap_params(wrap); set_filter_params(filter); }

	#define image_preamble state pipeline; pipeline.enable(target);	scoped_bind<texture> bound(*this); if (d.data) glPixelStorei(GL_UNPACK_ALIGNMENT, d.alignment);
	template <typename T> void image1d(const texture_image<T>& i, const texture_data& d) { image_preamble; glTexImage1D(target, i.level, i.internal_format, i.size, 0, d.format, d.type, d.data); throw_on_image_gl_error(); }
	template <typename T> void image2d(const texture_image<T>& i, const texture_data& d) { image_preamble; glTexImage2D(target, i.level, i.internal_format, i.size.x, i.size.y, 0, d.format, d.type, d.data); throw_on_image_gl_error(); }
	template <typename T> void image3d(const texture_image<T>& i, const texture_data& d) { image_preamble; glTexImage3D(target, i.level, i.internal_format, i.size.x, i.size.y, i.size.z, 0, d.format, d.type, d.data); throw_on_image_gl_error(); }

	template <typename T> void image1d(const texture_subimage<T>& i, const texture_data& d) { image_preamble; glTexSubImage1D(target, i.level, i.offset, i.size, d.format, d.type, d.data); throw_on_image_gl_error(); }
	template <typename T> void image2d(const texture_subimage<T>& i, const texture_data& d) { image_preamble; glTexSubImage2D(target, i.level, i.offset.x, i.offset.y, i.size.x, i.size.y, d.format, d.type, d.data); throw_on_image_gl_error(); }
	template <typename T> void image3d(const texture_subimage<T>& i, const texture_data& d) { image_preamble; glTexSubImage3D(target, i.level, i.offset.x, i.offset.y, i.offset.z, i.size.x, i.size.y, i.size.z, d.format, d.type, d.data); throw_on_image_gl_error(); }

	inline void throw_on_image_gl_error()
	{
		incase_opengl_error(err) {
			case GL_INVALID_ENUM:  throw runtime_error("texture: failed to load image: 'target', 'data_format' or 'data_type' are not one of the allowed values", err);
			case GL_INVALID_VALUE: throw runtime_error("texture: failed to load image: 'level', 'offset', 'size' or 'internal_format' is negative or too large", err);
			case GL_INVALID_OPERATION: throw runtime_error("texture: failed to load image: 'data_type' and 'data_format' are incompatible; or 'data_format' or 'internal_format' are invalid", err);
			default: throw err;
		}
	}
	#undef image_preamble
};

} // namespace gladus

namespace gl {
	typedef gladus::texture Texture;
}
