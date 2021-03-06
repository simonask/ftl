#pragma once
#ifndef ARRAY_ENUMERATOR_HPP_97HFNNXK
#define ARRAY_ENUMERATOR_HPP_97HFNNXK

namespace ftl {
	template <typename T>
	class ArrayEnumerator {
	public:
		typedef T ValueType;
		ArrayEnumerator() : _end(NULL), _current(NULL) {}
		ArrayEnumerator(T* begin, T* end) :  _current(begin-1), _end(end) {}
		ArrayEnumerator(const ArrayEnumerator& other) : _current(other._current), _end(other._end) {}
		bool move_next() { ++_current; return !at_end(); }
		T& current() { return *_current; }
		const T& current() const { return *_current; }
		bool at_end() const { return _current >= _end; }
		ArrayEnumerator<T>& get_enumerator() { return *this; }
		const ArrayEnumerator<T>& get_enumerator() const { return *this; }
		size_t size() const { return _end - _current; }
	private:
		T* _current;
		T* _end;
	};
}

#endif /* end of include guard: ARRAY_ENUMERATOR_HPP_97HFNNXK */
