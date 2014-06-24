/* Copyright (c) 2013-2014 Fabian Schuiki */
#pragma once

extern "C" {
#if defined(__APPLE__)
#	include <OpenGL/gl.h>
#else
#	define GL_GLEXT_PROTOTYPES 1
#	include <GL/gl.h>
#	include <GL/glext.h>
#endif
}
