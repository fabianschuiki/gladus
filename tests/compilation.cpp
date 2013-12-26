/* Copyright (c) 2013 Fabian Schuiki */
#include <gladus/opengl.hpp>
#include <gladus/buffer.hpp>
#include <gladus/binding.hpp>
#include <iostream>

int main()
{
	gl::Buffer somebuf;
	gladus::buffer mybuffer(GL_ARRAY_BUFFER);

	{
		gladus::binding<gladus::buffer> binding(mybuffer);
		glBufferData(GL_ARRAY_BUFFER, NULL, NULL, NULL);
	}

	return 0;
}