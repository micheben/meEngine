#pragma once

// For now we simply wrap c! standard functions
#include <cstdio>
#include <iostream>

#include "PIL/meTypes.h"

namespace meEngine
{
	namespace meIO
	{
		typedef std::FILE meFile;

		int meOpenFile(meFile** stream, const meString& filename, const meString& mode);
		int meCloseFile(meFile* stream);
		int meFlushFile(meFile* stream);

		int meReadFile(meFile* stream, meString& result, meUInt32 count);
		int meWriteFile(meFile* stream, const meString& content);
		
		int meFileError(meFile* stream);
		int meEOF(meFile* stream);
	}
}