#pragma once
#include <cstdint>
#include <string>

namespace meEngine
{
	typedef uint8_t  meUInt8;
	typedef uint16_t meUInt16;
	typedef uint32_t meUInt32;
	typedef uint64_t meUInt64;

	typedef int8_t  meInt8;
	typedef int16_t meInt16;
	typedef int32_t meInt32;
	typedef int64_t meint64;

	typedef float  meFloat32;
	typedef double meFloat64;

	typedef bool meBool;

	typedef wchar_t      meChar;
	typedef std::wstring meString;

	meInt16 Test(meInt16 a, meInt16 b);
}