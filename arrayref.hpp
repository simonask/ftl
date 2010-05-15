#pragma once
#ifndef ARRAYREF_HPP_G696Y8BQ
#define ARRAYREF_HPP_G696Y8BQ

#include "enumerable.hpp"
#include "array_enumerator.hpp"

namespace ftl {
	template <typename T>
	class ArrayRef : public Enumerable<ArrayRef<T>, ArrayEnumerator<T>> {
	public:
		ArrayRef(const T* data, size_t size) : _data(data), _size(size) {}
		size_t size() const { return _size; }
		const T* data() const { return _data; }
		const T& operator[](size_t idx) const { ftl::assert(idx < _size); return _data[idx]; }
	private:
		const T* _data;
		size_t _size;
	};
}

#endif /* end of include guard: ARRAYREF_HPP_G696Y8BQ */
