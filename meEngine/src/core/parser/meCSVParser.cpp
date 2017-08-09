#include "core/parser/meCSVParser.h"

#include "core/meLogger.h"

using namespace meEngine::meParser;
using namespace meEngine;

meCSVParser::meCSVParser()
{

}

meCSVParser::meCSVParser(meString filename)
{
	this->open(filename);
	this->parse();
}

meCSVParser::meCSVParser(meIO::meFile* file)
{
	this->file = file;
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
	return meNotYetImplementedError;
}

meError meCSVParser::parse()
{
	return meNotYetImplementedError;
}

meError meCSVParser::write(meString filename)
{
	return meNotYetImplementedError;
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
