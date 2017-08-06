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
	typedef int64_t meInt64;

	typedef float  meFloat32;
	typedef double meFloat64;

	typedef bool meBool;

	typedef wchar_t      meChar;
	typedef std::wstring meString;

	const auto& toString = static_cast<std::wstring(*)(int)>(to_wstring);
	const auto& toString = static_cast<std::wstring(*)(long)>(to_wstring);
	const auto& toString = static_cast<std::wstring(*)(long long)>(to_wstring);
	const auto& toString = static_cast<std::wstring(*)(unsigned)>(to_wstring);
	const auto& toString = static_cast<std::wstring(*)(unsigned long)>(to_wstring);
	const auto& toString = static_cast<std::wstring(*)(unsigned long long)>(to_wstring);
	const auto& toString = static_cast<std::wstring(*)(float)>(to_wstring);
	const auto& toString = static_cast<std::wstring(*)(double)>(to_wstring);
}