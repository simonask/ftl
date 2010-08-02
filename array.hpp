#pragma once
#ifndef ARRAY_HPP_4KSK70IE
#define ARRAY_HPP_4KSK70IE

#include "utils.hpp"
#include "enumerable.hpp"
#include "array_enumerator.hpp"
#include "arrayref.hpp"
#include "allocator.hpp"
#include "allocator_utils.hpp"

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
		void erase(size_t idx);
		
		T& first() { FTL_ASSERT(_size); return _data[0]; }
		const T& first() const { FTL_ASSERT(_size); return _data[0]; }
		T& last() { FTL_ASSERT(_size); return _data[_size-1]; }
		const T& last() const { FTL_ASSERT(_size); return _data[_size-1]; }
		T& operator[](size_t idx) { FTL_ASSERT(idx < _size); return _data[idx]; }
		const T& operator[](size_t idx) const { FTL_ASSERT(idx < _size); return _data[idx]; }
		
		ArrayEnumerator<T> get_enumerator() const { return ArrayEnumerator<T>(_data, _data+_size); }
	private:
		T* _data;
		size_t _size;
		size_t _alloc_size;
	};
	
	template <typename T>
	Array<T>::Array(const ArrayRef<T>& other) : _data(NULL), _size(0), _alloc_size(0) {
		_size = other.size();
		reserve(_size);
		copy_construct_range(_data, other.data(), _size);
	}
	
	template <typename T>
	Array<T>::~Array() {
		clear(true);
	}
	
	template <typename T>
	Array<T>& Array<T>::operator=(const ArrayRef<T>& other) {
		clear();
		_size = other.size();
		reserve(_size);
		copy_construct_range(_data, other.data(), _size);
	}
	
	template <typename T>
	void Array<T>::clear(bool unallocate) {
		destruct_range(_data, _size);
		_size = 0;
		if (unallocate) {
			Allocator::free(_data);
			_alloc_size = 0;
		}
	}
	
	template <typename T>
	void Array<T>::reserve(size_t new_size) {
		if (new_size > _alloc_size) {
			_data = AllocatorUtils<Allocator>::realloc(_data, new_size, _size);
		}
	}
	
	template <typename T>
	void Array<T>::fill(size_t new_size, const T& element) {
		reserve(new_size);
		for (size_t i = _size; i < new_size; ++i) {
			push(element);
		}
	}
	
	template <typename T>
	T& Array<T>::push() {
		reserve(_size+1);
		T* p = _data + _size++;
		new(p) T;
		return *p;
	}
	
	template <typename T>
	T& Array<T>::push(const T& element) {
		reserve(_size+1);
		T* p = _data + _size++;
		new(p) T(element);
		return *p;
	}
	
	template <typename T>
	void Array<T>::pop() {
		FTL_ASSERT(_size);
		_data[_size--].~T();
	}
	
	template <typename T>
	void Array<T>::erase(size_t idx) {
		FTL_ASSERT(idx < _size);
		_data[idx].~T();
		size_t tail = idx + 1;
		move_range(_data + idx, _data + tail, _size - tail);
		--_size;
	}
	
	
}

#endif /* end of include guard: ARRAY_HPP_4KSK70IE */
