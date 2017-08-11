#include "core/parser/meCSVParser.h"

#include "core/meLogger.h"

using namespace meEngine::meParser;
using namespace meEngine;

meCSVParser::~meCSVParser()
{

}

meCSVParser::meCSVParser(meChar sep) :
	seperator(sep)
{

}

meCSVParser::meCSVParser(meString filename, meChar sep) : 
	seperator(sep)
{
	this->read(filename);
}

meError meCSVParser::_open(meIO::meFile** file, meString filename, meString mode)
{
	int tmp = meIO::meOpenFile(file, filename, mode);
	return meStdioerrToMeerr(tmp);
}

meError meCSVParser::_close(meIO::meFile** file)
{
	if ((*file) == NULL)
	{
		return meFileClosedError;	// TODO: Maybe return error code?
	}
	int tmp = meIO::meCloseFile(*file);
	return meStdioerrToMeerr(tmp);
}

meError meCSVParser::read(meString filename)
{
	meIO::meFile* file;
	meError err = this->_open(&file, filename, L"r");
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

	while (!meIO::meEOF(file))
	{
		// Read line
		line.clear();
		int tmp = meIO::meReadFile(file, line, BATCHSIZE * 100);
		meError err = meStdioerrToMeerr(tmp);
		if (err != 0)
		{
			this->_close(&file);
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
			newpos = line.find(seperator, pos);			// New search 
			dataset.push_back(line.substr(pos, newpos - pos));
			pos = newpos + 1;							// Update
		}
		// Append data
		if (header)
		{
			this->header = std::move(dataset);
			header = false;
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
	meIO::meFile* file;
	meError err = this->_open(&file, filename, L"w");
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
	content[content.size()-1] = L'\n';
	linecount++;

	for (auto& line : data)
	{
		for (auto& entry : line)
		{
			content += entry;
			content.push_back(seperator);
		}
		content[content.size() - 1] = L'\n';	// Replace last ; with newline
		linecount++;

		if (linecount >= BATCHSIZE)
		{
			int tmp = meIO::meWriteFile(file, content);
			if (tmp != 0)
			{
				this->_close(&file);
				return meStdioerrToMeerr(tmp);
			}
			content.clear();
			linecount = 0;
		}
	}

	if (linecount != 0)
	{
		int tmp = meIO::meWriteFile(file, content);
		if (tmp != 0)
		{
			this->_close(&file);
			return meStdioerrToMeerr(tmp);
		}
		content.clear();
		linecount = 0;
	}

	int tmp = meIO::meCloseFile(file);
	err = meStdioerrToMeerr(tmp);
	if (err != 0)
	{
		this->currState = err;
		// TODO: do we want to log the error here, or do we just pass it?
		meLogging::meLogger::getInstance().log(meErrMessage(err), 1, L"meCSVParser");
	}
	return 0;
}

/*
=======================
Data Handling Functions
=======================
*/

meError meCSVParser::columns(meUInt64& num_colums)
{
	num_colums = this->header.size();
	return 0;
}

meError meCSVParser::rows(meUInt64& num_rows)
{
	num_rows = this->data.size();
	return 0;
}

meError meCSVParser::addHeader(const meString header)
{
	this->header.push_back(header);
	return 0;
}

meError meCSVParser::addRow(const meVector<meString>& data)
{
	auto tmp = data;
	while (tmp.size() < this->header.size())
	{
		tmp.push_back(L"");
	}
	if (tmp.size() > this->header.size())
	{
		return meToManyRowsError;
	}
	this->data.push_back(move(tmp));
	return 0;
}

meError meCSVParser::getHeader(meUInt16 index, meString& header)
{
	if (this->header.size() <= index)
	{
		return meIndexOutOfRangeError;
	}
	header = this->header[index];
	return 0;
}

meError meCSVParser::getHeaders(meVector<meString>& headers)
{
	headers = this->header;
	return 0;
}

meError meCSVParser::getRow(meUInt16 index, meVector<meString>& data)
{
	if (this->data.size() <= index)
	{
		return meIndexOutOfRangeError;
	}
	data = this->data[index];
	return 0;
}
