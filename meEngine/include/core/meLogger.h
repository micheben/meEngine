#pragma once
#pragma warning(disable : 4996)

#include "PIL\meTypes.h"
#include "PIL\meCollections.h"
#include "parser\meCSVParser.h"

#include <ctime>
#include <iostream>
#include <iomanip>
#include <memory>

namespace meEngine
{
	namespace meLogging
	{
		typedef meParser::meCSVParser logclass;
		const meUInt8 meErrorLevel = 1; // The lower the Level, the more important
		const meUInt8 meWarningLevel = 2;
		const meUInt8 meInfoLevel = 3;
		
		class meLogger
		{
		public:

			/*
			==============
			Static Methods
			==============
			*/
			/// <summary>Log the given message at a given level for a given categorie</summary>
			/// <param name="msg">The message to be logged</param>
			/// <param name="lvl">The level of the message. 1 => Error, 2 => Warning, 3 => Info</param>
			/// <param name="categorie">(Optional) You can add filters to only show a subset of messages</param>
			/// <returns> 0 on success, error number else. </returns>
			template<typename ... Args>
			static meError meLog(meUInt8 lvl, meString categorie, meString msg, Args ... args)
			{
				return getInstance().log(lvl, categorie, msg, args ...);
			}


			/// <summary>Log the given message as info (lvl 3)</summary>
			/// <param name="msg">The message to be logged</param>
			/// <param name="categorie">(Optional) You can add filters to only show a subset of messages</param>
			/// <returns> 0 on success, error number else. </returns>
			template<typename ... Args>
			static meError meLogInfo(meString categorie, meString msg, Args ... args)
			{
				return getInstance().logInfo(categorie, msg, args ...);
			}

			/// <summary>Log the given message as warning (lvl 2)</summary>
			/// <param name="msg">The message to be logged</param>
			/// <param name="categorie">(Optional) You can add filters to only show a subset of messages</param>
			/// <returns> 0 on success, error number else. </returns>
			template<typename ... Args>
			static meError meLogWarn(meString categorie, meString msg, Args ... args)
			{
				return getInstance().logWarn(categorie, msg, args ...);
			}

			/// <summary>Log the given message as error (lvl 1)</summary>
			/// <param name="msg">The message to be logged</param>
			/// <param name="categorie">(Optional) You can add filters to only show a subset of messages</param>
			/// <returns> 0 on success, error number else. </returns>
			template<typename ... Args>
			static meError meLogError(meString categorie, meString msg, Args ... args)
			{
				return getInstance().logError(categorie, msg, args ...);
			}

			/// <summary>Set the logger Level (only log messages at or below the level)</summary>
			/// <param name="lvl">The new logger level</param>
			/// <returns> 0 on success, error number else. </returns>
			static meError meSetLoggerLevel(meUInt8 lvl)
			{
				return getInstance().setLoggerLevel(lvl);
			}


			/// <summary>Get the logger Level (only log messages at or below the level)</summary>
			/// <returns> The logger level </returns>
			static meUInt8 meGetLoggerLevel()
			{
				return getInstance().getLoggerLevel();
			}
			
			/* 
			   =============
			   Class Methods 
			   =============
			*/
			/// <summary>Log the given message at a given level for a given categorie</summary>
			/// <param name="msg">The message to be logged</param>
			/// <param name="lvl">The level of the message. 1 => Error, 2 => Warning, 3 => Info</param>
			/// <param name="categorie">(Optional) You can add filters to only show a subset of messages</param>
			/// <returns> 0 on success, error number else. </returns>
			template<typename ... Args>
			meError log(meUInt8 lvl, meString categorie, meString msg, Args ... args)
			{
				return this->logger.addRow(meVector<meString>{string_format(msg, args ...), meToString(lvl), categorie});
			}

			/// <summary>Log the given message as info (lvl 3)</summary>
			/// <param name="msg">The message to be logged</param>
			/// <param name="categorie">(Optional) You can add filters to only show a subset of messages</param>
			/// <returns> 0 on success, error number else. </returns>
			template<typename ... Args>
			meError logInfo(meString categorie, meString msg, Args ... args)
			{
				return this->logger.addRow(meVector<meString>{string_format(msg, args ...), L"3", categorie});
			}

			/// <summary>Log the given message as warning (lvl 2)</summary>
			/// <param name="msg">The message to be logged</param>
			/// <param name="categorie">(Optional) You can add filters to only show a subset of messages</param>
			/// <returns> 0 on success, error number else. </returns>
			template<typename ... Args>
			meError logWarn(meString categorie, meString msg, Args ... args)
			{
				return this->logger.addRow(meVector<meString>{string_format(msg, args ...), L"2", categorie});
			}

			/// <summary>Log the given message as error (lvl 1)</summary>
			/// <param name="msg">The message to be logged</param>
			/// <param name="categorie">(Optional) You can add filters to only show a subset of messages</param>
			/// <returns> 0 on success, error number else. </returns>
			template<typename ... Args>
			meError logError(meString categorie, meString msg, Args ... args)
			{
				return this->logger.addRow(meVector<meString>{string_format(msg, args ...), L"1", categorie});
			}
			
			/// <summary>Set the logger Level (only log messages at or below the level)</summary>
			/// <param name="lvl">The new logger level</param>
			/// <returns> 0 on success, error number else. </returns>
			meError setLoggerLevel(meUInt8 lvl)
			{
				this->currLevel = lvl;
				return 0;
			}

			/// <summary>Get the logger Level (only log messages at or below the level)</summary>
			/// <returns> The logger level </returns>
			meUInt8 getLoggerLevel()
			{
				return this->currLevel;
			}

			meLogger(meLogger const&) = delete;
			void operator=(meLogger const&) = delete;

			static meLogger& getInstance()
			{
				static meLogger instance;
				return instance;
			}
		private:
			meLogger()
			{
				this->logger.addHeader(L"message");
				this->logger.addHeader(L"lvl");
				this->logger.addHeader(L"categorie");
			}

			meString filename = L"meLog.csv";
			logclass logger;

			meUInt8 currLevel;

			template<typename ... Args>
			meString string_format(meString& format, Args ... args)
			{
				size_t size = _snwprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
				std::unique_ptr<meChar[]> buf(new meChar[size]);
				_snwprintf(buf.get(), size, format.c_str(), args ...);
				return meString(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
			}
		};

		
	}
}