#pragma once

#include "PIL\meTypes.h"
#include "PIL\meCollections.h"
#include "PIL\meIO.h"

#include "core\meLogger.h"
#include "core\meError.h"

namespace meEngine
{
	namespace meParser
	{
		class meCSVParser
		{
		public:
			/* 
			=====================
			IO Handling Functions
			===================== 
			*/

			/// <summary> Class for working with CSV files </summary>
			meCSVParser();

			/// <summary> Class for working with CSV files </summary>
			/// <param name="filename"> The filename of the file. It will be opend and parsed directly </param>
			meCSVParser(meString filename);

			/// <summary> Class for working with CSV files </summary>
			/// <param name="file"> A handle to an opened file. The file will be parsed. </param>
			meCSVParser(meIO::meFile* file);

			/// <summary> Open a file for parsing or writing </summary>
			/// <param name="filename"> The filename of the file to be opend </param>
			/// <returns> 0 on success, error number else. </returns>
			meError open(meString filename);

			/// <summary> Close the file if any is opend. </summary>
			/// <returns> 0 on success, error number else. </returns>
			meError close();

			/// <summary> Parse the an opend file into the internal structure </summary>
			/// <returns> 0 on success, error number else. </returns>
			meError parse();

			/// <summary> Write the internal data into a csv file </summary>
			/// <param name="filename"> (Optional) The target filename. If it's the empty String, try to write to an opend file</param>
			/// <returns> 0 on success, error number else. </returns>
			meError write(meString filename = L"");

			/*
			=======================
			Data Handling Functions
			=======================
			*/

			/// <summary> Add a new header to the internal data structure </summary>
			/// <param name="header"> The name of the header </param>
			/// <returns> 0 on success, error number else. </returns>
			meError addHeader(meString header);

			/// <summary> Add a new row with the given data </summary>
			/// <param name="data"> The data as a vector of strings </param>
			/// <returns> 0 on success, error number else. </returns>
			meError addRow(meVector<meString> data);

		private:
			meBool fileowner;	// True if we opend the file, false otherwise.
			meIO::meFile* file;

			meVector<meString> header;
			meVector< meVector<meString> > data;
		};
	}
}