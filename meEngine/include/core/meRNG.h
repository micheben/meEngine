#pragma once

#include "PIL\meTypes.h"

namespace meEngine
{
	namespace meRNG
	{
		class meXOrShift
		{
		private:	
			static meUInt64 x64;
		public:
			static void setSeed(meUInt64 seed);
			static meUInt64 getSeed();
			static meUInt64 rand();
		};
	}
}