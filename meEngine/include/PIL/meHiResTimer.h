#pragma once

#include <chrono>
#include "meTypes.h"
namespace meEngine
{
	typedef std::chrono::nanoseconds meTime_t;

	class meTime
	{
	private:
		meTime_t t;
	public:
		meTime(meTime_t t);
		meUInt64 asMilliseconds();
		meFloat64 asSeconds();
	};

	class meHiResTimer
	{
	private:
		std::chrono::high_resolution_clock::time_point starttime;
	public:
		meHiResTimer();
		void start();
		meTime restart();
		meTime stop();
	};

	// TODO: meTime meTimeFunction()
}