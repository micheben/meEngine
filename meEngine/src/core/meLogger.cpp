#include "core\meLogger.h"

#include <iostream>

using namespace meEngine;
using namespace meEngine::meLogging;

meLogger::meLogger()
{
	this->init = false;
}

void meLogger::log(meString msg, meUInt8 lvl, meUInt64 categorie)
{
	if (!this->init)
	{
		std::wcerr << L"Logger not Initialized but got Message: " << msg << " " << lvl << " " << categorie << std::endl;
	}
	if (this->init)
	{
		std::wcerr << L"Logger Initialized, Message: " << msg << " " << lvl << " " << categorie << std::endl;
	}
	return;
}


meLogger& meLogger::getInstance()
{
	static meLogger instance;
	return instance;
}