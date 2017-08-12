#include "core/meIO.h"

using namespace meEngine;
using namespace meEngine::meIO;

meError meIO::open(meFile** file, const meString& filename, const meString& mode)
{
	int tmp = mePILIO::meOpenFile(file, filename, mode);
	return meStdioerrToMeerr(tmp);
}

meError meIO::close(meFile* file)
{
	if (file == NULL)
	{
		return meFileClosedError;	// TODO: Maybe return error code?
	}
	int tmp = mePILIO::meCloseFile(file);
	return meStdioerrToMeerr(tmp);
}

meError meIO::readLine(meFile* file, meString& line, meUInt32 size)
{
	int tmp = mePILIO::meReadFile(file, line, size);
	return meStdioerrToMeerr(tmp);
}

meError meIO::writeString(meFile* file, const meString& content)
{
	int tmp = mePILIO::meWriteFile(file, content);
	return meStdioerrToMeerr(tmp);
}

meError meIO::meEOF(meFile* file)
{
	return mePILIO::meEOF(file);
}
meError meIO::meFileError(meFile* file)
{
	return meStdioerrToMeerr(mePILIO::meFileError(file));
}