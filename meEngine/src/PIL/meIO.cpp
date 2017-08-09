#include "PIL/meIO.h"
using namespace meEngine;
using namespace meEngine::meIO;
#include <wchar.h>

int meEngine::meIO::meOpenFile(meFile** stream, const meString& filename, const meString& mode)
{
	return _wfopen_s(stream, filename.c_str(), mode.c_str());
}
int meEngine::meIO::meCloseFile(meFile* stream)
{
	return std::fclose(stream);
}
int meEngine::meIO::meFlushFile(meFile* stream)
{
	return std::fflush(stream);
}

int meEngine::meIO::meReadFile(meFile* stream, meString& result, meUInt32 count)
{
	wchar_t* buffer = new wchar_t[count];
	wchar_t* ret = std::fgetws(buffer, count, stream);

	if (ret != buffer)
	{
		return 1;
	}

	result.append(buffer);
	delete[] buffer;
	return 0;
}
int meEngine::meIO::meWriteFile(meFile* stream, const meString& content)
{
	return std::fputws(content.c_str(), stream);
}

int meEngine::meIO::meFileError(meFile* stream)
{
	return std::ferror(stream);
}