#pragma once

#include "PIL/meTypes.h"
#include "PIL/meCollections.h"
#include "PIL/meIO.h"

#include "core/meError.h"

namespace meEngine
{
	namespace meParser
	{
		class meCSVParser
		{
		public:
			/*
			=========
			Constants
			=========
			*/

			/// <summary> Size of a Line batch during writing </summary>
			static const meUInt16 BATCHSIZE = 1000;

			/* 
			=====================
			IO Handling Functions
			===================== 
			*/

			/// <summary> Class for working with CSV files </summary>
			meCSVParser(meChar sep = L';');

			/// <summary> Class for working with CSV files </summary>
			/// <param name="filename"> The filename of the file. It will be opend and parsed directly </param>
			meCSVParser(meString filename, meChar sep = L';');

			/// <summary> Class for working with CSV files </summary>
			/// <param name="file"> A handle to an opened file. The file will be parsed. </param>
			meCSVParser(meIO::meFile* file, meChar sep = L';');

			/// <summary> Open a file for parsing or writing </summary>
			/// <param name="filename"> The filename of the file to be opend </param>
			/// <returns> 0 on success, error number else. </returns>
			meError open(meString filename);

			/// <summary> Close the file if any is opend. </summary>
			/// <returns> 0 on success, error number else. </returns>
			meError close();

			/// <summary> Get the State of the internal file. </summary>
			/// <returns> 0 if the internal file is opend, error number else. </returns>
			meError state();

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

			/// <summary> Get the number of columns </summary>
			/// <param name="num_colums"> The number of colums </param>
			/// <returns> 0 on success, error number else. </returns>
			meError columns(meUInt16& num_colums);

			/// <summary> Get the number of rows (without header) </summary>
			/// <param name="num_colums"> The number of rows </param>
			/// <returns> 0 on success, error number else. </returns>
			meError rows(meUInt16& num_rows);

			/// <summary> Add a new header to the internal data structure </summary>
			/// <param name="header"> The name of the header </param>
			/// <returns> 0 on success, error number else. </returns>
			meError addHeader(meString header);

			/// <summary> Add a new row with the given data </summary>
			/// <param name="data"> The data as a vector of strings </param>
			/// <returns> 0 on success, error number else. </returns>
			meError addRow(meVector<meString>& data);

			/// <summary> Get the name of the Header at the given Index </summary>
			/// <param name="index"> The Index </param>
			/// <param name="header"> The meString where the Header will be saved </param>
			/// <returns> 0 on success, error number else. </returns>
			meError getHeader(meUInt16 index, meString& header);

			/// <summary> Get the name of all Headers </summary>
			/// <param name="headers"> The vector where the headers should be added (all will be appended) </param>
			/// <returns> 0 if Successfull, meErrorCode otherwise </returns>
			meError getHeaders(meVector<meString>& headers);

			/// <summary> Get the row at the given index </summary>
			/// <param name="index"> The index where to look at </param>
			/// <param name="data"> The data as a vector of strings </param>
			/// <returns> 0 on success, error number else. </returns>
			meError getRow(meUInt16 index, meVector<meString>& data);

		private:
			meBool fileowner;	// True if we opend the file, false otherwise.
			meIO::meFile* file;

			meVector<meString> header;
			meVector< meVector<meString> > data;
			meChar seperator;
		};
	}
}