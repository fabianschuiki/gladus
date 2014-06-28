/* Copyright (c) 2013-2014 Fabian Schuiki */
#pragma once
#include <stdexcept>
#include <string>
#define GLADUS_HAS_ERROR

namespace gladus {

struct error : public std::exception {};

struct opengl_error : public error
{
	GLenum ec;

	opengl_error(): ec(GL_NO_ERROR) {}
	opengl_error(GLenum ec): ec(ec) {}

	virtual const char* what() const throw()
	{
		switch (ec) {
			case GL_INVALID_ENUM: return "invalid opengl enum";
			case GL_INVALID_VALUE: return "invalid opengl value";
			case GL_INVALID_OPERATION: return "invalid opengl operation";
			case GL_INVALID_FRAMEBUFFER_OPERATION: return "invalid opengl framebuffer operation";
			case GL_OUT_OF_MEMORY: return "opengl out of memory";
			default: return "unknown opengl error"; break;
		}
	}
};

struct runtime_error : public error
{
	std::string message;
	opengl_error underlying_gl_error;

	runtime_error(): message("") {}
	runtime_error(const char* msg): message(msg) {}
	runtime_error(const char* msg, const opengl_error& err): message(msg), underlying_gl_error(err) {}
	runtime_error(const char* msg, const runtime_error& err): message(msg), underlying_gl_error(err.underlying_gl_error) { message += "; after " + err.message; }
	virtual ~runtime_error() throw() {}

	virtual const char* what() const throw()
	{
		std::string composed = "gladus: ";
		composed += (message.empty() ? "unknown error" : message);
		if (underlying_gl_error.ec != GL_NO_ERROR) {
			composed += " (";
			composed += underlying_gl_error.what();
			composed += ')';
		}
		return composed.c_str();
	}
};

#ifdef GLADUS_DONT_CHECK_GL_ERRORS
#	define clear_opengl_error()
#	define check_opengl_error(err) false
#	define throw_on_opengl_error()
#	define if_opengl_error(err) opengl_error err; if (false)
#	define incase_opengl_error(err) opengl_error err; if (false) switch(GL_NO_ERROR)
#else
inline void clear_opengl_error() { glGetError(); }

inline bool check_opengl_error(opengl_error& err)
{
	GLenum e = glGetError();
	if (e != GL_NO_ERROR) {
		err = opengl_error(e);
		return true;
	}
	return false;
}

inline void throw_on_opengl_error()
{
	opengl_error err;
	if (check_opengl_error(err))
		throw err;
}

#define if_opengl_error(err) opengl_error err; if (check_opengl_error(err))
#define incase_opengl_error(err) opengl_error err; if (check_opengl_error(err)) switch (err.ec)
#endif

} // namespace gladus
