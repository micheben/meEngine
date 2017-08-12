#pragma once
#include "PIL/meTypes.h"
#include "core/meIO.h"
#include "core/meError.h"
#include "core/meConfig.h"

namespace meEngine
{
	namespace meParser
	{
		class meConfigParser
		{

		public:

			/*
			===========================
			Constructor / Deconstructor
			===========================
			*/

			/// <summary> Class for reading and writing config file </summary>
			meConfigParser();
			
			~meConfigParser();

			/*
			=====================
			IO Handling Functions
			=====================
			*/
			
			/// <summary> Read the data from a csv file </summary>
			/// <param name="filename"> The target filename</param>
			/// <param name="conf"> The meConfig where the content will be saved. </param>
			/// <returns> 0 on success, error number else. </returns>
			meError read(meString filename, meConfig& conf);

			/// <summary> Write the internal data into a csv file </summary>
			/// <param name="filename"> The target filename.</param>
			/// <param name="conf"> The meConfig that will be saved. </param>
			/// <returns> 0 on success, error number else. </returns>
			meError write(meString filename, const meConfig& conf);
		};
	}
}