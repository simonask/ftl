#pragma once
#ifndef BAG_HPP_1PPLQ7IF
#define BAG_HPP_1PPLQ7IF

#include "utils.hpp"

namespace ftl {
	template <typename T> class Array;
	
	template <typename T, typename Container>
	class Bag : public Enumerable<Bag<T,Container>, Container::Enumerator> {
	public:
		typedef Container::Enumerator Enumerator;
		Bag(const Container& c) : _c(c) {}
		Bag(const Bag<T,Container>& other) : _c(other._c) {}
		Bag<T,Container>& operator=(const Container& other) { _c = other; return *this; }
		Bag<T,Container>& operator=(const Bag<T,Container>& other) { _c = other._c; return *this; }
		
		size_t size() const { return _c.size(); }
		size_t capacity() const { return _c.capacity(); }
		void clear() { _c.clear(); }
		void reserve(size_t new_alloc_size) { _c.reserve(new_alloc_size); }
		void fill(size_t n, const T& element = T()) { _c.fill(n, element); }
		
		T& push(const T& x) { return _c.push(x); }
		T& push() { return _c.push(); }
		void pop() { _c.pop(); }
		bool erase(size_t idx);
		
		T& first() { return _c.first(); }
		const T& first() const { return _c.first(); }
		T& last() { return _c.last(); }
		const T& last() const { return _c.last(); }
		
		T& operator[](size_t idx) { return _c[idx]; }
		const T& operator[](size_t idx) const { return _c[idx]; }
		
		Enumerator get_enumerator() const { return _c.get_enumerator(); }
	private:
		Container _c;
	};
}

#endif /* end of include guard: BAG_HPP_1PPLQ7IF */
