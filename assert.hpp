#pragma once
#ifndef ASSERT_HPP_5BNPSAGT
#define ASSERT_HPP_5BNPSAGT

#ifdef FTL_NO_EXCEPTIONS

#include <assert.h>

#define FTL_ASSERT assert

#else

namespace ftl {
	class AssertException {
	public:
		AssertException(const char* text) : _text(text) {}
		const char* what() const { return _text; }
	private:
		const char* _text;
	};
	
	inline void assert(bool value, const char* text = "(no description)") {
		if (!value)
			throw AssertException(text);
	}
}

#define FTL_ASSERT(X) ftl::assert(X, #X)

#endif

#endif /* end of include guard: ASSERT_HPP_5BNPSAGT */
