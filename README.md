Gladus OpenGL C++ Wrapper
=========================

A lightweight header-only library that wraps the modern portion of the OpenGL API into proper C++ classes that are convenient and safe to use. It follows the Boost style of coding, opting for high genericity.


Coding Style
------------

The coding rules are simple and as follows:

- classes are defined in the `gladus` namespace, names are lowercase underscored as in Boost (e.g. `gladus::buffer`)
- all classes are aliased into the `gl` namespace in camel-case, to reproduce the OpenGL name (e.g. `gl::Buffer`)
