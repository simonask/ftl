#pragma once
#ifndef MAXARRAY_HPP_ABKX8L5G
#define MAXARRAY_HPP_ABKX8L5G

#include "utils.hpp"
#include "enumerable.hpp"
#include "array_enumerator.hpp"

namespace ftl {
	template <typename T, size_t C>
	class MaxArray : public Enumerable<MaxArray<T,C>, ArrayEnumerator<T>> {
	public:
		typedef ArrayEnumerator<T> Enumerator;
		
		MaxArray() : _size(0) {}
		MaxArray(const ArrayRef<T>& other);
		~MaxArray();
		MaxArray<T>& operator=(const ArrayRef<T>& other);
		operator ArrayRef<T>() const;
		
		size_t size() const { return _size; }
		size_t capacity() const { return C; }
		void clear();
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
		
		ArrayEnumerator<T> get_enumerator() const { return ArrayEnumerator<T>(data(), data()+_size); }
	private:
		struct Element { char _[sizeof(T)]; }; // TODO: Alignment
		Element _data[C];
		size_t _size;
		T* data() { return reinterpret_cast<T*>(_data); }
		const T* data() const { return reinterpret_cast<const T*>(_data); }
	};
}

#endif /* end of include guard: MAXARRAY_HPP_ABKX8L5G */
