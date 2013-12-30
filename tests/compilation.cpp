/* Copyright (c) 2013 Fabian Schuiki */
#include <gladus/opengl.hpp>
#include <gladus/error.hpp>
#include <gladus/buffer.hpp>
#include <gladus/binding.hpp>
#include <gladus/state.hpp>
#include <gladus/texture.hpp>
#include <gladus/shader.hpp>
#include <gladus/program.hpp>
#include <iostream>

int main()
{
	gl::Buffer somebuf;
	gladus::buffer mybuffer(GL_ARRAY_BUFFER);

	{
		gladus::state state;
		state.enable(GL_BLEND).enable(GL_LIGHTING);
	}

	gladus::program program;
	program.uniform("mat_mvp").value(1.4,2,6);

	return 0;
}