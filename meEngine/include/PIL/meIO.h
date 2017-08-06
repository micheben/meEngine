#pragma once

// For now we simply wrap c! standard functions
#include <cstdio>

namespace meEngine
{
	namespace IO
	{
		typedef std::FILE meFile;

		const auto& meOpenFile = std::fopen;
		const auto& meCloseFile = std::fclose;
		const auto& meFlushFile = std::fflush;

		const auto& meReadFile = std::fread;
		const auto& meWriteFile = std::fwrite;
	}
}