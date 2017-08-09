#include "core/meError.h"

using namespace meEngine;
meError meEngine::meStdioerrToMeerr(int stdioerrno)
{
	return 1000 + stdioerrno;
}

meString meEngine::meErrMessage(meError err)
{
	return L"TODO";
}