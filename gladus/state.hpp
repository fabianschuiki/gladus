/* Copyright (c) 2013 Fabian Schuiki */
#pragma once
#include <map>
#define GLADUS_HAS_STATE

namespace gladus {

/// This structure maintains changes to OpenGL's capabilities normally done via
/// glEnable() and glDisable(). Upon destruction, this class reverts all changes
/// that were made to the OpenGL capabilities. Hence this class provides an
/// exception-safe way of configuring OpenGL for your needs.
struct state
{
	struct capability
	{
		unsigned initial:1;
		unsigned modified:1;
	};
	typedef std::map<GLenum, capability> capability_map;
	capability_map changes;

	~state() { reset(); }

	inline state& enable(GLenum cap)  { set(cap, true);  return *this; }
	inline state& disable(GLenum cap) { set(cap, false); return *this; }

	state& set(GLenum cap, bool onoff)
	{
		capability_map::iterator it = changes.find(cap);
		if (it == changes.end()) {
			capability& c = changes[cap];
			c.initial = glIsEnabled(cap);
			c.modified = onoff;
			if (onoff) glEnable(cap); else glDisable(cap);
		} else if (it->second.modified != onoff) {
			it->second.modified = onoff;
			if (onoff) glEnable(cap); else glDisable(cap);
		}
		return *this;
	}

	state& reset()
	{
		for (capability_map::iterator it = changes.begin(); it != changes.end(); it++) {
			if (it->second.initial != it->second.modified) {
				if (it->second.initial)
					glEnable(it->first);
				else
					glDisable(it->first);
			}
		}
		changes.clear();
		return *this;
	}

	/** Prevents reset() and the destructor from undoing the state changes you
	 * have performed so far. */
	state& base()
	{
		for (capability_map::iterator it = changes.begin(); it != changes.end(); it++) {
			it->second.initial = it->second.modified;
		}
		return *this;
	}
};

} // namespace gladus
