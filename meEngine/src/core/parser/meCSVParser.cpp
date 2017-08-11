#include "core/parser/meCSVParser.h"

#include "core/meLogger.h"

using namespace meEngine::meParser;
using namespace meEngine;

meCSVParser::meCSVParser(meChar sep) : 
	seperator(sep)
{

}

meCSVParser::meCSVParser(meString filename, meChar sep) : 
	seperator(sep), fileowner(true)
{
	meError err = this->open(filename);
	if (err == 0)
	{
		this->parse();
	}
}

meCSVParser::meCSVParser(meIO::meFile* file, meChar sep) :
	seperator(sep), fileowner(false), file(file)
{
	this->parse();
}

meError meCSVParser::open(meString filename)
{
	// Open in r+ to check if the file exists.
	int tmp = meIO::meOpenFile(&this->file, filename, L"r+");
	meError err = meStdioerrToMeerr(tmp);
	if (err != 0)
	{
		// TODO: do we want to log the error here, or do we just pass it?
		meLogging::meLogger::getInstance().log(meErrMessage(err), 1, 0);
	}
	return err;
}

meError meCSVParser::close()
{
	int tmp = meIO::meCloseFile(this->file);
	meError err = meStdioerrToMeerr(tmp);
	if (err != 0)
	{
		// TODO: do we want to log the error here, or do we just pass it?
		meLogging::meLogger::getInstance().log(meErrMessage(err), 1, 0);
	}
	return err;
}

meError meCSVParser::state()
{
	int tmp = meIO::meFileError(this->file);
	return meStdioerrToMeerr(tmp);
}

meError meCSVParser::parse()
{
	/* Check if file is ok */
	meError err = this->state();
	if (err != 0)
	{
		// TODO: do we want to log the error here, or do we just pass it?
		meLogging::meLogger::getInstance().log(meErrMessage(err), 1, L"meCSVParser");
		return err;
	}

	
	bool header = true;
	meUInt64 pos = 0;
	meUInt64 newpos = 0;
	meVector<meString> dataset;
	meString line;

	while (!meIO::meEOF(this->file))
	{
		// Read line
		int tmp = meIO::meReadFile(this->file, line, BATCHSIZE * 100);
		if (err != 0)
		{
			// TODO: do we want to log the error here, or do we just pass it?
			meLogging::meLogger::getInstance().log(meErrMessage(err), 1, L"meCSVParser");
			return err;
		}
		if (line.size() == 0)
		{
			break; // end of file AND no data
		}
		if (line[line.size() - 1] == L'\n')
		{
			line.pop_back();	// Remove new line at the end
		}

		// Split into tokens
		pos = 0;
		newpos = 0;
		while (newpos != meString::npos)
		{
			pos = newpos;								// Update
			newpos = line.find(seperator, pos);			// New search 
			dataset.push_back(line.substr(pos + 1, newpos - pos - 1));
		}
		dataset.push_back(line.substr(pos + 1, line.size() - pos - 1));

		// Append data
		if (header)
		{
			this->header = std::move(dataset);
		}
		else
		{
			this->data.push_back(std::move(dataset));
		}
		dataset.clear();
	}
	return 0;
}

meError meCSVParser::write(meString filename)
{
	/* Check if file is ok */
	meError err = this->state();
	if (err != 0)
	{
		// TODO: do we want to log the error here, or do we just pass it?
		meLogging::meLogger::getInstance().log(meErrMessage(err), 1, L"meCSVParser");
		return err;
	}
	
	/* Build the content. */
	meString content = L"";
	meUInt16 linecount = 0;

	content.reserve(BATCHSIZE * 100);	// Magic number... estimated size of one line.
	for (auto& h : header)
	{
		content += h;
		content.push_back(seperator);
	}
	content.push_back(L'\n');
	linecount++;

	for (auto& line : data)
	{
		for (auto& entry : line)
		{
			content += entry;
			content.push_back(seperator);
		}
		content.push_back(L'\n');
		linecount++;

		if (linecount >= BATCHSIZE)
		{
			int tmp = meIO::meWriteFile(this->file, content);
			if (tmp != 0)
			{
				// TODO: Cleanup file?
				return meStdioerrToMeerr(tmp);
			}
			content.clear();
			linecount = 0;
		}
	}

	if (linecount != 0)
	{
		int tmp = meIO::meWriteFile(this->file, content);
		if (tmp != 0)
		{
			// TODO: Cleanup file?
			return meStdioerrToMeerr(tmp);
		}
		content.clear();
		linecount = 0;
	}

	return 0;
}

/*
=======================
Data Handling Functions
=======================
*/			

meError meCSVParser::columns(meUInt16& num_colums)
{
	return meNotYetImplementedError;
}

meError meCSVParser::rows(meUInt16& num_rows)
{
	return meNotYetImplementedError;
}

meError meCSVParser::addHeader(meString header)
{
	return meNotYetImplementedError;
}

meError meCSVParser::addRow(meVector<meString>& data)
{
	return meNotYetImplementedError;
}

meError meCSVParser::getHeader(meUInt16 index, meString& header)
{
	return meNotYetImplementedError;
}

meError meCSVParser::getHeaders(meVector<meString>& headers)
{
	return meNotYetImplementedError;
}

meError meCSVParser::getRow(meUInt16 index, meVector<meString>& data)
{
	return meNotYetImplementedError;
}
