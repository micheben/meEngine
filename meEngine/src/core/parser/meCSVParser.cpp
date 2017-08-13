#include "core/parser/meCSVParser.h"

#include "core/meLogger.h"
#include "core/meIO.h"

using namespace meEngine::meParser;
using namespace meEngine;

meCSVParser::~meCSVParser()
{

}

meCSVParser::meCSVParser(meChar sep) :
	seperator(sep)
{

}

meCSVParser::meCSVParser(const meString& filename, meChar sep) :
	seperator(sep)
{
	this->read(filename);
}


meError meCSVParser::read(const meString& filename)
{
	meIO::meFile* file;
	meError err = meIO::open(&file, filename, L"r");
	if (err != 0)
	{
		// TODO: do we want to log the error here, or do we just pass it?
		meLogging::meLogger::getInstance().log(1, L"meCSVParser", meErrMessage(err));
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
		meError tmp = meIO::readLine(file, line, BATCHSIZE * 100);
		if (err != 0)
		{
			meIO::close(file);
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

	err = meIO::close(file);
	return err;
}

meError meCSVParser::write(const meString& filename)
{
	meIO::meFile* file;
	meError err = meIO::open(&file, filename, L"w");
	if (err != 0)
	{
		// TODO: do we want to log the error here, or do we just pass it?
		meLogging::meLogger::getInstance().log(1, L"meCSVParser", meErrMessage(err));
		return err;
	}

	if (this->header.size() == 0)	// No content
	{
		err = meIO::close(file);
		return meNoDataGiven;
	}

	/* Build the content. */
	meString content = L"";
	meUInt16 linecount = 0;

	content.reserve(BATCHSIZE * 100);	// Magic number... estimated size of one line.
	for (auto& h : this->header)
	{
		content += h;
		content.push_back(seperator);
	}
	content[content.size() - 1] = L'\n';

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
			err = meIO::writeString(file, content);
			if (err != 0)
			{
				meIO::close(file);
				return err;
			}
			content.clear();
			linecount = 0;
		}
	}

	if (linecount != 0)
	{
		err = meIO::writeString(file, content);
		if (err != 0)
		{
			meIO::close(file);
			return err;
		}
		content.clear();
		linecount = 0;
	}

	err = meIO::close(file);
	return err;
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

meError meCSVParser::addHeader(const meString& header)
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
