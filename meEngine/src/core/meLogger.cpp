#include "core\meLogger.h"

#include <ctime>
#include <iostream>
#include <iomanip>

using namespace meEngine;
using namespace meEngine::meLogging;

meLogger::meLogger() : currLevel(3)
{
	this->logger.addHeader(L"message");
	this->logger.addHeader(L"lvl");
	this->logger.addHeader(L"categorie");
}

meLogger& meLogger::getInstance()
{
	static meLogger instance;
	return instance;
}

/*
=============
Class Methods
=============
*/
meError meLogger::log(meString msg, meUInt8 lvl, meString categorie)
{
	return this->logger.addRow(meVector<meString>{msg, meToString(lvl), categorie});
}

meError meLogger::logInfo(meString msg, meString categorie)
{
	return this->logger.addRow(meVector<meString>{msg, L"3", categorie});
}

meError meLogger::logWarn(meString msg, meString categorie)
{
	return this->logger.addRow(meVector<meString>{msg, L"2", categorie});
}

meError meLogger::logError(meString msg, meString categorie)
{
	return this->logger.addRow(meVector<meString>{msg, L"1", categorie});
}

meError meLogger::setLoggerLevel(meUInt8 lvl)
{
	this->currLevel = lvl;
	return 0;
}

meUInt8 meLogger::getLoggerLevel()
{
	return this->currLevel;
}

/*
==============
Static Methods
==============
*/
meError meLogger::meLog(meString msg, meUInt8 lvl, meString categorie)
{
	return getInstance().log(msg, lvl, categorie);
}

meError meLogger::meLogInfo(meString msg, meString categorie)
{
	return getInstance().logInfo(msg, categorie);
}

meError meLogger::meLogWarn(meString msg, meString categorie)
{
	return getInstance().logWarn(msg, categorie);
}

meError meLogger::meLogError(meString msg, meString categorie)
{
	return getInstance().logError(msg, categorie);
}

meError meLogger::meSetLoggerLevel(meUInt8 lvl)
{
	return getInstance().setLoggerLevel(lvl);
}

meUInt8 meLogger::meGetLoggerLevel()
{
	return getInstance().getLoggerLevel();
}