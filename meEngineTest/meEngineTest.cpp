#include "gtest/gtest.h"
#include "PIL/meTypes.h"

TEST(mePIL, Tests)
{
	EXPECT_EQ(20, meEngine::Test(10, 10));
}