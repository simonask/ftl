#pragma once
#ifndef ARRAY_ENUMERATOR_HPP_97HFNNXK
#define ARRAY_ENUMERATOR_HPP_97HFNNXK

namespace ftl {
	template <typename T>
	class ArrayEnumerator {
	public:
		typedef T ValueType;
		LinearEnumerator(T* begin, T* end) : _end(end), _current(begin-1) {}
		LinearEnumerator(const LinearEnumerator& other) : _end(other._end), _current(other._current) {}
		bool move_next() { ++_current; return !at_end(); }
		T current() { return *_current; }
		bool at_end() const { return _current >= _end; }
		const T& current() const { return *_current; }
		const LinearEnumerator<T>& get_enumerator() const { return *this; }
		size_t size() const { return _end - _current; }
	private:
		T* _current;
		T* _end;
	};
}

#endif /* end of include guard: ARRAY_ENUMERATOR_HPP_97HFNNXK */
