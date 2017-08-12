#include "gtest/gtest.h"
#include "core/meRNG.h"

TEST(meRNG, generate)
{
	meEngine::meRNG::meXOrShift::setSeed(1);
	EXPECT_EQ(meEngine::meRNG::meXOrShift::rand(), 1082269761ull);
	EXPECT_EQ(meEngine::meRNG::meXOrShift::rand(), 1152992998833853505ull);
	EXPECT_EQ(meEngine::meRNG::meXOrShift::rand(), 11177516664432764457ull);
	EXPECT_EQ(meEngine::meRNG::meXOrShift::rand(), 17678023832001937445ull);
}