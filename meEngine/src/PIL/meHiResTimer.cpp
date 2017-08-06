#include "PIL/meHiResTimer.h"

using namespace meEngine;

meHiResTimer::meHiResTimer() {};

void meHiResTimer::start()
{
	this->starttime = std::chrono::high_resolution_clock::now();
}

meTime meHiResTimer::restart()
{
	auto tmp = this->starttime;
	this->starttime = std::chrono::high_resolution_clock::now();
	return meTime(std::chrono::duration_cast<meTime_t>(this->starttime - tmp));
}

meTime meHiResTimer::stop()
{
	auto now = std::chrono::high_resolution_clock::now();
	return meTime(now - this->starttime);
}

meTime::meTime(meTime_t t) : t(t) {};

meUInt64 meTime::asMilliseconds()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(this->t).count();
}

meFloat64 meTime::asSeconds()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(this->t).count() / 1000.f;
}