#pragma once
#ifndef STRINGBUFFER_HPP_BE7PHSAO
#define STRINGBUFFER_HPP_BE7PHSAO

#include "appendbuffer.hpp"
#include "stringref.hpp"
#include "string.hpp"

namespace ftl {
	class StringBuffer : public AppendBuffer<char> {
	public:
		String to_string() const;
		size_t length() const { return size(); }
		
		StringBuffer& operator<<(const StringRef& str);
	};
	
	inline StringBuffer& StringBuffer::operator<<(const StringRef& str) {
		str.each([&](char c){ this->push(c); });
		return *this;
	}
	
	inline String StringBuffer::to_string() const {
		String ret;
		ret._length = length();
		ret._data = new char[ret._length];
		size_t written = 0;
		_pages.each([&](const AppendBuffer<char>::Page& page) {
			copy_range(ret._data + written, page.data(), page.size());
			written += page.size();
		});
		return ret;
	}
}

#endif /* end of include guard: STRINGBUFFER_HPP_BE7PHSAO */
