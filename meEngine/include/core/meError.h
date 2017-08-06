#pragma once

#include "PIL\meTypes.h"
namespace meEngine
{
	/* Lowlevel Errors*/

	typedef meUInt16 meError;

	/* General & undefined Errors */
	const meError meUndefinedError = 0;

	/* IO Errors */
	const meError meFileNotFoundError = 1001;
	const meError meCouldNotOpenFileError = 1002;
}