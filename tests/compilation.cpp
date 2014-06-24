/* Copyright (c) 2013-2014 Fabian Schuiki */
#include <gladus/opengl.hpp>
#include <gladus/error.hpp>
#include <gladus/buffer.hpp>
#include <gladus/binding.hpp>
#include <gladus/state.hpp>
#include <gladus/texture.hpp>
#include <gladus/shader.hpp>
#include <gladus/program.hpp>
#include <gladus/framebuffer.hpp>
#include <iostream>

int main()
{
	gl::Buffer somebuf;
	gladus::buffer mybuffer(GL_ARRAY_BUFFER);

	{
		gladus::state state;
		state.enable(GL_BLEND).enable(GL_LIGHTING);
	}

	return 0;
}
