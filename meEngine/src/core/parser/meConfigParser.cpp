#include "core/parser/meConfigParser.h"
#include "core/meLogger.h"

using namespace::meEngine;
using namespace::meEngine::meParser;

bool _splitLine(meString& line, meString& token, meString& value)
{
	auto pos = line.find(L"=");

	if (pos == meString::npos)
	{
		return false;
	}

	token = line.substr(0, pos);

	value.clear();
	value = line.substr(pos + 1);

	return true;
}


meConfigParser::meConfigParser()
{

}

meConfigParser::~meConfigParser()
{

}



meError meConfigParser::read(meString filename, meConfig& conf)
{
	meIO::meFile* file;
	meError err = meIO::open(&file, filename, L"r");
	if (err != 0)
	{
		// TODO: do we want to log the error here, or do we just pass it?
		meLogging::meLogger::meLogError(meErrMessage(err), L"meConfigParser");
		return err;
	}

	meString line;
	meString token;
	meString value;
	while (!meIO::meEOF(file))
	{
		// Read line
		line.clear();
		err = meIO::readLine(file, line);
		if (err != 0)
		{
			meIO::close(file);
			return err;
		}

		if (!_splitLine(line, token, value))
		{
			meLogging::meLogger::meLogWarn(L"Invalid token found: %s. Ignore Parameter", L"meConfigParser");
			continue;
		}

	}

	err = meIO::close(file);
	return err;
}


meError meConfigParser::write(meString filename, const meConfig& conf)
{
	return meNotYetImplementedError;
}