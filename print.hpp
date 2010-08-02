#pragma once
#ifndef PRINT_HPP_A98FKY08
#define PRINT_HPP_A98FKY08

#include "string.hpp"
#include "stringref.hpp"
#include "stringbuffer.hpp"
#include "type_conversion.hpp"
#include <stdio.h>
#include <inttypes.h>


namespace ftl {
	template <typename... Args>
	void print(const StringRef& fmt, Args... args) {
		String s = format(fmt, args...);
		printf(s.c_str());
	}
	
	template <typename T>
	inline void convert_variadic_arguments_to_strings(String* target, const T& x) {
		*target = TypeConverter<T, String>::convert(x);
	}
	
	template <typename T, typename... Rest>
	inline void convert_variadic_arguments_to_strings(String* target, const T& x, const Rest&... rest) {
		*target = TypeConverter<T, String>::convert(x);
		convert_variadic_arguments_to_strings(target+1, rest...);
	}
	
	template <typename... Args>
	String format(const StringRef& fmt, Args... args) {
		const size_t num_args = sizeof...(args);
		String converted[num_args];
		convert_variadic_arguments_to_strings(converted, args...);
		StringBuffer buffer;
		const char* c = fmt.c_str();
		bool escaping = false;
		for (size_t i = 0; i < fmt.length(); ++i) {
			switch (c[i]) {
				case '\\': {
					if (escaping) { escaping = false; buffer.push('\\'); continue; }
					escaping = true;
					continue;
				}
				case '{': {
					if (!escaping) {
						size_t idx = 0;
						bool valid = true;
						bool anything = false;
						size_t j = i + 1;
						for (; j < fmt.length(); ++j) {
							if (is_numeric(c[j])) {
								idx *= 10;
								idx += c[j] - '0';
								anything = true;
							} else if (c[j] == '}') {
								break;
							} else {
								// non-numeric, non-terminator
								valid = false;
								break;
							}
						}
						if (valid && anything && idx < num_args) {
							buffer << converted[idx];
							i = j;
							continue;
						}
					}
				}
			}
			escaping = false;
			buffer.push(c[i]);
		}
		return buffer.to_string();
	}
	
	String format(const StringRef& fmt) {
		return fmt;
	}
}

#endif /* end of include guard: PRINT_HPP_A98FKY08 */
