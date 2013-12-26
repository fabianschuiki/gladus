/* Copyright (c) 2013 Fabian Schuiki */
#pragma once
#include <cassert>

namespace gladus {

template <typename T> struct binding
{
	typedef T type;
	T& object;

	binding(T& object): object(object) { is_bound = false; bind(); }
	~binding() { if (is_bound) unbind(); }

	void bind() { assert(!is_bound); object.bind(); is_bound = true; }
	void unbind() { assert(is_bound); object.unbind(); is_bound = false; }

private:
	bool is_bound;
};

} // namespace gladus
