#pragma once

#include "PIL\meTypes.h"
namespace meEngine
{
	/* Lowlevel Errors*/

	typedef meUInt16 meError;

	/* General & undefined Errors */
	const meError meUndefinedError         = 1;
	const meError meNotYetImplementedError = 2;
	const meError meIndexOutOfRangeError   = 3;

	/* IO Errors */
	meError meStdioerrToMeerr(int stdioerrno);
	const meError meOpNotAllowed = 1000 + EPERM;
	const meError meFileNotFound = 1000 + ENOENT;
	const meError meNotEnoughMemory = 1000 + ENOMEM;
	const meError meAccessDenied = 1000 + EACCES;
	const meError meHardwareBusy = 1000 + EBUSY;
	const meError meFileExists = 1000 + EEXIST;
	const meError meNotDirectory = 1000 + ENOTDIR;
	const meError meIsDirectory = 1000 + EISDIR;
	const meError meToManyFilesOpen = 1000 + EMFILE;
	const meError meFileToBig = 1000 + EFBIG;
	const meError meNoDiscSpace = 1000 + ENOSPC;
	const meError meReadOnlyFileSystem = 1000 + EROFS;
	const meError meFilenameToLong = 1000 + ENAMETOOLONG;
	const meError meFileClosedError = 1100;	// 1100 and above is surely not used :P

	/* Parser Errors */
	const meError meNoDataGiven = 2001;
	const meError meToManyRowsError = 2002;

	meString meErrMessage(meError err);
}