#include "core/meError.h"

using namespace meEngine;
meError meEngine::meStdioerrToMeerr(int stdioerrno)
{
	if (stdioerrno == 0)
	{
		return 0;
	}
	if (stdioerrno == EOF)
	{
		return meFileClosedError;
	}
	return 1000 + stdioerrno;
}

meString meEngine::meErrMessage(meError err)
{
	return L"TODO";
}