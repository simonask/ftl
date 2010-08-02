#pragma once
#ifndef ALLOCATOR_HPP_XE7VE834
#define ALLOCATOR_HPP_XE7VE834

#include <stdlib.h>

#define FTL_DEFAULT_ALLOCATOR MallocAllocator

namespace ftl {
	class MallocAllocator {
	public:
		typedef unsigned char byte;
		
		template <typename T>
		static T* alloc(size_t n);
		template <typename T>
		static T* realloc(T* old, size_t n);
		template <typename T>
		static void free(T* ptr);
	};
	
	template <typename T>
	inline T* MallocAllocator::alloc(size_t n) {
		return static_cast<T*>(::malloc(sizeof(T)*n));
	}
	
	template <typename T>
	inline T* MallocAllocator::realloc(T* old, size_t n) {
		return static_cast<T*>(::realloc(old, sizeof(T)*n));
	}
	
	template <typename T>
	inline void MallocAllocator::free(T* ptr) {
		return ::free(ptr);
	}
	
	typedef FTL_DEFAULT_ALLOCATOR Allocator;
}

#endif /* end of include guard: ALLOCATOR_HPP_XE7VE834 */
