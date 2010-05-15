#pragma once
#ifndef UTILS_HPP_SHV50JHA
#define UTILS_HPP_SHV50JHA

#include <new>

namespace ftl {
	template <typename T, typename... Args>
	void construct_range(T* p, size_t n, Args... args) {
		for (size_t i = 0; i < n; ++i) {
			new(p+i) T(args...);
		}
	}
	
	template <typename T>
	void destruct_range(T* p, size_t n) {
		for (size_t i = 0; i < n; ++i) {
			p[i].~T();
		}
	}
	
	template <typename T>
	void copy_range(T* dst, const T* src, size_t n) {
		for (size_t i = 0; i < n; ++i) {
			dst[i] = src[i];
		}
	}
	
	template <typename T>
	void copy_construct_range(T* dst, const T* src, size_t n) {
		for (size_t i = 0; i < n; ++i) {
			new(dst+i) T(src[i]);
		}
	}
	
	template <typename T>
	void move_range(T* dst, T* src, size_t n) {
		for (size_t i = 0; i < n; ++i) {
			new(dst+i) T(src[i]);
			src[i].~T();
		}
	}
	
	template <typename T>
	T min(T a, T b) {
		return a <= b ? a : b;
	}
	
	template <typename T>
	T max(T a, T b) {
		return a > b ? a : b;
	}
}

#endif /* end of include guard: UTILS_HPP_SHV50JHA */
