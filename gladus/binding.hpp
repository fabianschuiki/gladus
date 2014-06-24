/* Copyright (c) 2013-2014 Fabian Schuiki */
#pragma once
#include <cassert>
#define GLADUS_HAS_BINDING

namespace gladus {

/** A pair of bind() and unbind() calls limited to the scope of the declared
 * variable. Provides a convenient exception-safe way of using OpenGL resources
 * that implement a bind/unbind pattern. May not be nested. */
template <typename T> struct scoped_bind
{
	typedef T type;
	const T& object;

	scoped_bind(const T& object): object(object) { is_bound = false; bind(); }
	~scoped_bind() { if (is_bound) unbind(); }

	void bind() { assert(!is_bound); object.bind(); is_bound = true; }
	void unbind() { assert(is_bound); object.unbind(); is_bound = false; }

private:
	bool is_bound;
};

/** A pair of use() and unuse() calls limited to the scope of the declared
 * variable. Provides a convenient exception-safe way of using OpenGL resources
 * that implement a use/unuse pattern. May not be nested. */
template <typename T> struct scoped_use
{
	typedef T type;
	const T& object;

	scoped_use(const T& object): object(object) { is_used = false; use(); }
	~scoped_use() { if (is_used) unuse(); }

	void use() { assert(!is_used); object.use(); is_used = true; }
	void unuse() { assert(is_used); object.unuse(); is_used = false; }

private:
	bool is_used;
};

} // namespace gladus
