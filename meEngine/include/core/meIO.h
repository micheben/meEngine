#pragma once

#include "PIL/mePILIO.h"
#include "core/meError.h"
namespace meEngine
{
	namespace meIO
	{
		typedef mePILIO::meFile meFile;

		/// <summary> Open a file for parsing or writing (INTERNAL ONLY)</summary>
		/// <param name="file"> File handle where the opened file will be saved </param>
		/// <param name="filename"> The filename of the file to be opend </param>
		/// <param name="mode"> The open mode </param>
		/// <returns> 0 on success, error number else. </returns>
		meError open(meFile** file, const meString& filename, const meString& mode);

		/// <summary> Read the data from a csv file </summary>
		/// <param name="filename"> The target filename</param>
		/// <returns> 0 on success, error number else. </returns>
		meError close(meFile* file);

		/// <summary> Read a line or size Bytes from the file into the line </summary>
		/// <param name="file"> The file handle </param>
		/// <param name="line"> The line for the data </param>
		/// <param name="size"> The maximum size to be read </param>
		/// <returns> 0 on success, error number else. </returns>
		meError readLine(meFile* file, meString& line, meUInt32 size);

		/// <summary> Write a String to the file </summary>
		/// <param name="file"> The file handle </param>
		/// <param name="line"> The string </param>
		/// <returns> 0 on success, error number else. </returns>
		meError writeString(meFile* file, const meString& line);

		/// <summary> Check if the file has reached the eof </summary>
		/// <param name="file"> The file handle </param>
		/// <returns> 0 if there is still content, error number else. </returns>
		meError meEOF(meFile* file);

		/// <summary> Check the error state of the given file </summary>
		/// <param name="file"> The file handle </param>
		/// <returns> 0 if everything is fine, error number else. </returns>
		meError meFileError(meFile* file);
	}
}