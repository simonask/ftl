#pragma once
#ifndef STRING_HPP_1JT2HXDW
#define STRING_HPP_1JT2HXDW

#include <string.h>
#include "utils.hpp"
#include "assert.hpp"
#include "enumerable.hpp"
#include "string_enumerator.hpp"
#include "stringref.hpp"

#include <stdio.h>

namespace ftl {
	class String : public Enumerable<String, StringEnumerator> {
	public:
		friend class StringBuffer;
		friend String operator+(const StringRef&, const StringRef&);
		typedef StringEnumerator Enumerator;
		String() : _data(NULL), _length(0) {}
		String(const char* cstr, size_t len);
		String(const StringRef& other);
		String(const String& other);
		String& operator=(const StringRef& other);
		String& operator=(const String& other);
		~String();
		
		size_t length() const { return _length; }
		const char* c_str() const { return _data; }
		
		char& operator[](size_t idx) { FTL_ASSERT(idx < _length); return _data[idx]; }
		char operator[](size_t idx) const { FTL_ASSERT(idx < _length); return _data[idx]; }
		
		String operator+(const StringRef& other) const;
		StringEnumerator get_enumerator() const { return StringEnumerator(_data, _length); }
	private:
		void assign(const char* data, size_t len);
		void clear();
		char* _data;
		size_t _length;
	};
	
	inline String::String(const char* cstr, size_t len) : _data(NULL) {
		assign(cstr, len);
	}
	
	inline String::String(const StringRef& other) : _data(NULL) {
		assign(other.c_str(), other.length());
	}
	
	inline String::String(const String& other) : _data(NULL) {
		assign(other.c_str(), other.length());
	}
	
	inline String& String::operator=(const StringRef& other) {
		assign(other.c_str(), other.length());
		return *this;
	}
	
	inline String& String::operator=(const String& other) {
		assign(other._data, other._length);
		return *this;
	}
	
	inline String::~String() {
		clear();
	}
	
	inline void String::assign(const char* data, size_t len) {
		clear();
		_length = len;
		_data = new char[_length+1];
		copy_range(_data, data, _length);
		_data[_length] = '\0';
	}
	
	inline void String::clear() {
		delete[] _data;
		_data = NULL;
		_length = 0;
	}
	
	inline String String::operator+(const StringRef& other) const {
		String ret;
		ret._length = _length + other.length();
		ret._data = new char[ret._length + 1];
		copy_range(ret._data, _data, _length);
		copy_range(ret._data + _length, other.c_str(), other.length());
		ret._data[ret._length] = '\0';
		return ret;
	}
	
	inline String operator+(const StringRef& a, const StringRef& b) {
		String ret;
		ret._length = a.length() + b.length();
		ret._data = new char[ret._length + 1];
		copy_range(ret._data, a.c_str(), a.length());
		copy_range(ret._data + a.length(), b.c_str(), b.length());
		ret._data[ret._length] = '\0';
		return ret;
	}
	
	/*
		The parts of StringRef that depend on a definition of String.
		This is placed here to avoid .cpp files.
	*/
	inline StringRef::StringRef(const String& other) : _data(other.c_str()), _length(other.length()) {}
}

#endif /* end of include guard: STRING_HPP_1JT2HXDW */
