#pragma once
#ifndef STRING_CONVERSION_HPP_O2SNKJTM
#define STRING_CONVERSION_HPP_O2SNKJTM

#include <inttypes.h>
#include <stdio.h>
#include "string.hpp"

namespace ftl {
	template <typename From, typename To>
	struct TypeConverter {
		static To convert(const From& f) { return f; }
	};
	
	template <> struct TypeConverter<const char*, String> { static StringRef convert(const char* cstr) { return StringRef(cstr); } };
	template <> struct TypeConverter<StringRef, String> { static StringRef convert(const StringRef& ref) { return ref; } };
	
	#define FTL_STRING_CONVERTER_SNPRINTF(TYPE, FORMAT_STRING) \
		template <> struct TypeConverter<TYPE, String> {              \
			static String convert(TYPE x) {                           \
				char buffer[32];                               \
				snprintf(buffer, 32, FORMAT_STRING, x);        \
				return String(buffer);                         \
			}                                                  \
		};
	
	FTL_STRING_CONVERTER_SNPRINTF(int8_t, "%d")
	FTL_STRING_CONVERTER_SNPRINTF(uint8_t, "%u")
	FTL_STRING_CONVERTER_SNPRINTF(int16_t, "%d")
	FTL_STRING_CONVERTER_SNPRINTF(uint16_t, "%u")
	FTL_STRING_CONVERTER_SNPRINTF(int32_t, "%d")
	FTL_STRING_CONVERTER_SNPRINTF(uint32_t, "%u")
	FTL_STRING_CONVERTER_SNPRINTF(int64_t, "%ld")
	FTL_STRING_CONVERTER_SNPRINTF(uint64_t, "%lu")
	FTL_STRING_CONVERTER_SNPRINTF(float, "%f")
	FTL_STRING_CONVERTER_SNPRINTF(double, "%lf")
	FTL_STRING_CONVERTER_SNPRINTF(void*, "%p")
	FTL_STRING_CONVERTER_SNPRINTF(char, "%c");
	
	#undef FTL_STRING_CONVERTER_SNPRINTF
	
	template <> struct TypeConverter<bool, String> { static StringRef convert(bool b) { return b ? StringRef("true") : StringRef("false"); } };
}

#endif /* end of include guard: STRING_CONVERSION_HPP_O2SNKJTM */
