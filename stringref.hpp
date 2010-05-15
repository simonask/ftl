#pragma once
#ifndef STRINGREF_HPP_WZKLOJFK
#define STRINGREF_HPP_WZKLOJFK

#include <string.h>
#include "assert.hpp"
#include "enumerable.hpp"
#include "string_enumerator.hpp"

namespace ftl {
	class String;
	
	class StringRef : public Enumerable<StringRef, StringEnumerator> {
	public:
		typedef StringEnumerator Enumerator;
		StringRef(const char* cstr);
		StringRef(const char* cstr, size_t len) : _data(cstr), _length(len) {}
		StringRef(const StringRef& other) : _data(other._data), _length(other._length) {}
		StringRef(const String& other); // definition in string.hpp
		StringRef& operator=(const StringRef& other) { _data = other._data; _length = other._length; return *this; }
		
		size_t length() const { return _length; }
		char operator[](size_t idx) const { FTL_ASSERT(idx < _length); return _data[idx]; }
		
		const char* c_str() const { return _data; }
		
		StringEnumerator get_enumerator() const { return StringEnumerator(_data, _length); }
	private:
		const char* _data;
		size_t _length;
	};
	
	inline StringRef::StringRef(const char* cstr) : _data(cstr), _length(strlen(cstr)) {}
}

#endif /* end of include guard: STRINGREF_HPP_WZKLOJFK */
