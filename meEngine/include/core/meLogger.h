#pragma once

#include "PIL\meTypes.h"
#include "PIL\meCollections.h"
#include "parser\meCSVParser.h"

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
			static meError meLog(meString msg, meUInt8 lvl, meString categorie = L"general");


			/// <summary>Log the given message as info (lvl 3)</summary>
			/// <param name="msg">The message to be logged</param>
			/// <param name="categorie">(Optional) You can add filters to only show a subset of messages</param>
			/// <returns> 0 on success, error number else. </returns>
			static meError meLogInfo(meString msg, meString categorie = L"general");

			/// <summary>Log the given message as warning (lvl 2)</summary>
			/// <param name="msg">The message to be logged</param>
			/// <param name="categorie">(Optional) You can add filters to only show a subset of messages</param>
			/// <returns> 0 on success, error number else. </returns>
			static meError meLogWarn(meString msg, meString categorie = L"general");

			/// <summary>Log the given message as error (lvl 1)</summary>
			/// <param name="msg">The message to be logged</param>
			/// <param name="categorie">(Optional) You can add filters to only show a subset of messages</param>
			/// <returns> 0 on success, error number else. </returns>
			static meError meLogError(meString msg, meString categorie = L"general");

			/// <summary>Set the logger Level (only log messages at or below the level)</summary>
			/// <param name="lvl">The new logger level</param>
			/// <returns> 0 on success, error number else. </returns>
			static meError meSetLoggerLevel(meUInt8 lvl);

			/// <summary>Get the logger Level (only log messages at or below the level)</summary>
			/// <returns> The logger level </returns>
			static meUInt8 meGetLoggerLevel();
			
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
			meError log(meString msg, meUInt8 lvl, meString categorie = L"general");

			/// <summary>Log the given message as info (lvl 3)</summary>
			/// <param name="msg">The message to be logged</param>
			/// <param name="categorie">(Optional) You can add filters to only show a subset of messages</param>
			/// <returns> 0 on success, error number else. </returns>
			meError logInfo(meString msg, meString categorie = L"general");

			/// <summary>Log the given message as warning (lvl 2)</summary>
			/// <param name="msg">The message to be logged</param>
			/// <param name="categorie">(Optional) You can add filters to only show a subset of messages</param>
			/// <returns> 0 on success, error number else. </returns>
			meError logWarn(meString msg, meString categorie = L"general");

			/// <summary>Log the given message as error (lvl 1)</summary>
			/// <param name="msg">The message to be logged</param>
			/// <param name="categorie">(Optional) You can add filters to only show a subset of messages</param>
			/// <returns> 0 on success, error number else. </returns>
			meError logError(meString msg, meString categorie = L"general");
			
			/// <summary>Set the logger Level (only log messages at or below the level)</summary>
			/// <param name="lvl">The new logger level</param>
			/// <returns> 0 on success, error number else. </returns>
			meError setLoggerLevel(meUInt8 lvl);

			/// <summary>Get the logger Level (only log messages at or below the level)</summary>
			/// <returns> The logger level </returns>
			meUInt8 getLoggerLevel();

			meLogger(meLogger const&) = delete;
			void operator=(meLogger const&) = delete;

			static meLogger& getInstance();
		private:
			meLogger(); // We use a singelton

			meString filename = L"meLog.csv";
			logclass logger;

			meUInt8 currLevel;
		};

		
	}
}