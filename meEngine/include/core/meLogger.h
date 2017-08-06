#pragma once

#include "PIL\meTypes.h"
#include "PIL\meCollections.h"

namespace meEngine
{
	namespace meLogging
	{
		const meUInt8 meErrorLevel = 1; // The lower the Level, the more important
		const meUInt8 meWarningLevel = 2;
		const meUInt8 meInfoLevel = 3;
		class _meLogger
		{
		public:
			/// <summary>Log the given message at a given level for a given categorie</summary>
			/// <param name="msg">The message to be logged</param>
			/// <param name="lvl">The level of the message. 1 => Error, 2 => Warning, 3 => Info</param>
			/// <param name="categorie">(Optional) You can add filters to only show a subset of messages (Bitmask). Use addCategorie to add a named mask</param>
			/// <returns>None</returns>
			void log(meString msg, meUInt8 lvl, meUInt64 categorie = 0);
			//void info(meString msg, meUInt64 categorie = 0);
			//void error(meString msg, meUInt64 categorie = 0);
			//void addCategorie(meString name, meUInt64 mask);
		private:
			_meLogger(); // We use a singelton
			//TODO CSV PARSER...
		};
	}
}