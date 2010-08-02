#pragma once
#ifndef MAXARRAY_HPP_ABKX8L5G
#define MAXARRAY_HPP_ABKX8L5G

#include "utils.hpp"
#include "enumerable.hpp"
#include "array_enumerator.hpp"
#include "arrayref.hpp"

namespace ftl {
	template <typename T, size_t C>
	class MaxArray : public Enumerable<MaxArray<T,C>, ArrayEnumerator<T>> {
	public:
		typedef ArrayEnumerator<T> Enumerator;
		
		MaxArray() : _size(0) {}
		MaxArray(const ArrayRef<T>& other);
		~MaxArray();
		MaxArray<T,C>& operator=(const ArrayRef<T>& other);
		operator ArrayRef<T>() const { return ArrayRef<T>(data(), _size); }
		
		size_t size() const { return _size; }
		size_t capacity() const { return C; }
		void clear();
		void fill(size_t new_size, const T& element = T());
		
		T& push(const T& element);
		T& push();
		void pop();
		bool erase(size_t idx);
		
		T& first() { FTL_ASSERT(_size); return data()[0]; }
		const T& first() const { FTL_ASSERT(_size); return data()[0]; }
		T& last() { FTL_ASSERT(_size); return data()[_size-1]; }
		const T& last() const { FTL_ASSERT(_size); return data()[_size-1]; }
		T& operator[](size_t idx) { FTL_ASSERT(idx < _size); return data()[idx]; }
		const T& operator[](size_t idx) const { FTL_ASSERT(idx < _size); return data()[idx]; }
		
		ArrayEnumerator<T> get_enumerator() const { return ArrayEnumerator<T>(data(), data()+_size); }
		const T* data() const { return reinterpret_cast<const T*>(_data); }
	private:
		struct Element { char _[sizeof(T)]; }; // TODO: Alignment
		Element _data[C];
		size_t _size;
		T* data() { return reinterpret_cast<T*>(_data); }
	};
	
	template <typename T, size_t C>
	MaxArray<T,C>::MaxArray(const ArrayRef<T>& other) {
		FTL_ASSERT(other.size() <= C);
		_size = other.size();
		copy_construct_range(data(), other.data(), _size);
	}
	
	template <typename T, size_t C>
	MaxArray<T,C>::~MaxArray() {
		destruct_range(data(), _size);
	}
	
	template <typename T, size_t C>
	MaxArray<T,C>& MaxArray<T,C>::operator=(const ArrayRef<T>& other) {
		clear();
		FTL_ASSERT(other.size() <= C);
		_size = other.size();
		copy_construct_range(data(), other.data(), _size);
	}
	
	template <typename T, size_t C>
	void MaxArray<T,C>::clear() {
		destruct_range(data(), _size);
		_size = 0;
	}
	
	template <typename T, size_t C>
	void MaxArray<T,C>::fill(size_t n, const T& x) {
		FTL_ASSERT(n <= C);
		if (n > _size) {
			construct_range(data() + _size, n - _size, x);
		}
	}
	
	template <typename T, size_t C>
	T& MaxArray<T,C>::push(const T& x) {
		FTL_ASSERT(_size < C);
		T* p = data() + _size++;
		new(p) T(x);
		return *p;
	}
	
	template <typename T, size_t C>
	T& MaxArray<T,C>::push() {
		FTL_ASSERT(_size < C);
		T* p = data() + _size++;
		new(p) T;
		return *p;
	}
	
	template <typename T, size_t C>
	void MaxArray<T,C>::pop() {
		FTL_ASSERT(_size);
		data()[--_size].~T();
	}
	
	
}

#endif /* end of include guard: MAXARRAY_HPP_ABKX8L5G */
