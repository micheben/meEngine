#include <ctime>
#include <inttypes.h>
#include "core\meRNG.h"

using namespace meEngine;

meUInt64 meEngine::meRNG::meXOrShift::x64 = std::time(NULL);

meUInt64 meRNG::meXOrShift::rand()
{
	x64 ^= x64 << 13;
	x64 ^= x64 >> 7;
	x64 ^= x64 << 17;
	return x64;
}

void meRNG::meXOrShift::setSeed(meUInt64 seed)
{
	x64 = seed;
}
meUInt64 meRNG::meXOrShift::getSeed()
{
	return x64;
}

