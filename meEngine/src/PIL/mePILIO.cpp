#include "PIL/mePILIO.h"
using namespace meEngine;
using namespace meEngine::mePILIO;
#include <wchar.h>

int meEngine::mePILIO::meOpenFile(meFile** stream, const meString& filename, const meString& mode)
{
	wprintf(L"Open %s", filename.c_str());

	return _wfopen_s(stream, filename.c_str(), mode.c_str());
}
int meEngine::mePILIO::meCloseFile(meFile* stream)
{
	return std::fclose(stream);
}
int meEngine::mePILIO::meFlushFile(meFile* stream)
{
	return std::fflush(stream);
}

int meEngine::mePILIO::meReadFile(meFile* stream, meString& result, meUInt32 count)
{
	wchar_t* buffer = new wchar_t[count];
	wchar_t* ret = std::fgetws(buffer, count, stream);

	if (ret == NULL)
	{
		delete[] buffer;
		if (feof(stream) != 0)
		{
			return 0; // Not an error per se...
		}
		return ferror(stream);
	}

//	else
	result.clear();
	result.append(buffer);
	delete[] buffer;
	return 0;
}
int meEngine::mePILIO::meWriteFile(meFile* stream, const meString& content)
{
	return std::fputws(content.c_str(), stream);
}

int meEngine::mePILIO::meFileError(meFile* stream)
{
	return std::ferror(stream);
}

int meEngine::mePILIO::meEOF(meFile* stream)
{
	return std::feof(stream);
}