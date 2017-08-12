#include "core/parser/meConfigParser.h"
#include "core/meLogger.h"

using namespace::meEngine;
using namespace::meEngine::meParser;


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
	while (!meIO::meEOF(file))
	{
		// Read line
		line.clear();
		err = meIO::readLine(file, line, BATCHSIZE * 100);
		if (err != 0)
		{
			meIO::close(file);
			return err;
		}
	}

	err = meIO::close(file);
	return err;
}


meError meConfigParser::write(meString filename, const meConfig& conf)
{
	return meNotYetImplementedError;
}