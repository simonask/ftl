#pragma once
#ifndef ALLOCATOR_UTILS_HPP_GU8I6HCJ
#define ALLOCATOR_UTILS_HPP_GU8I6HCJ

#include "type_traits.hpp"
#include "utils.hpp"

namespace ftl {
	template <typename Allocator>
	class AllocatorUtils {
	public:
		template <typename T>
		static T* realloc(T* ptr, size_t new_size, size_t initialized_size) { return Reallocator<T, is_pod<T>::value>::realloc(ptr, new_size, initialized_size); }
	private:
		template <typename T, bool pod> struct Reallocator { static T* realloc(T* ptr, size_t new_size, size_t initialized_size); };
		template <typename T> struct Reallocator<T, true> {
			static T* realloc(T* ptr, size_t new_size, size_t initialized_size) {
				return Allocator::realloc(ptr, new_size);
			}
		};
		template <typename T> struct Reallocator<T, false> {
			static T* realloc(T* ptr, size_t new_size, size_t initialized_size) {
				T* data = Allocator::alloc(new_size);
				move_range(data, ptr, initialized_size);
				Allocator::free(ptr);
				return data;
			}
		};
	};
}

#endif /* end of include guard: ALLOCATOR_UTILS_HPP_GU8I6HCJ */
