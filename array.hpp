#pragma once
#ifndef ARRAY_HPP_4KSK70IE
#define ARRAY_HPP_4KSK70IE

#include "utils.hpp"
#include "enumerable.hpp"
#include "array_enumerator.hpp"
#include "arrayref.hpp"

namespace ftl {
	template <typename T>
	class Array : public Enumerable<Array<T>, ArrayEnumerator<T>> {
	public:
		typedef ArrayEnumerator<T> Enumerator; // used by wrapping types, such as Bag
		
		Array() : _data(NULL), _size(0), _alloc_size(0) {}
		Array(const ArrayRef<T>& other);
		~Array();
		Array<T>& operator=(const ArrayRef<T>& other);
		operator ArrayRef<T>() const { return ArrayRef<T>(_data, _size); }

		size_t size() const { return _size; }
		void clear(bool unallocate = false);
		void reserve(size_t new_alloc_size);
		void fill(size_t new_size, const T& element = T());
		
		T& push(const T& element);
		T& push();
		void pop();
		bool erase(size_t idx);
		
		T& first();
		const T& first() const;
		T& last();
		const T& last() const;
		T& operator[](size_t idx);
		const T& operator[](size_t idx) const;
		
		ArrayEnumerator<T> get_enumerator() const { return ArrayEnumerator<T>(_data, _data+_size); }
	private:
		T* _data;
		size_t _size;
		size_t _alloc_size;
	};
	
	
	
	template <typename T>
	template <typename E>
	Array<T>& Array<T>::operator=(const E& enumerable) {
		clear();
		reserve(enumerable.size());
		enumerable.each([](const T& x) { push(x); });
	}
}

#endif /* end of include guard: ARRAY_HPP_4KSK70IE */
