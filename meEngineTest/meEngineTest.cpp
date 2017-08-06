#include "gtest/gtest.h"
#include "PIL/meHiResTimer.h"

#include <windows.h>

TEST(mePIL, meHiResTimer)
{
	meEngine::meHiResTimer timer;
	timer.start();
	Sleep(1000);
	auto t = timer.stop();

	EXPECT_NEAR(1000, t.asMilliseconds(), 50);
	EXPECT_NEAR(1.0, t.asSeconds(), 0.05);
}