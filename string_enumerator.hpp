#pragma once
#ifndef STRING_ENUMERATOR_HPP_O30L6IO0
#define STRING_ENUMERATOR_HPP_O30L6IO0

namespace ftl {
	class StringEnumerator {
	public:
		typedef char ValueType;
		StringEnumerator(const char* cstr, size_t len) : _current(cstr-1), _end(cstr+len) {}
		StringEnumerator(const StringEnumerator& other) : _current(other._current-1), _end(other._end) {}
		bool at_end() const { return _current >= _end; }
		bool move_next() { ++_current; return !at_end(); }
		char current() const { return *_current; }
		const StringEnumerator& get_enumerator() const { return *this; }
		size_t size() const { return _end - _current; }
	private:
		const char* _current;
		const char* _end;
	};
}

#endif /* end of include guard: STRING_ENUMERATOR_HPP_O30L6IO0 */
