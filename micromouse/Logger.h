#pragma once

#ifdef __MK20DX256__ //this is the Teensy signature
#include <Arduino.h>

#else
#include <iostream>
#include <fstream>
#include <sstream>
#endif


/*
This is a helper class that makes logging information easy
it will output anything that can use <<

it uses 3 different macros defined at the bottom of the file to make
logging as short and quick as possible

log( logLevel ) will output to both the console and the log file
logC( logLevel ) will output to the console only
logF( logLevel ) will output to the log file only

logLevel defines the importance of the log
the log type from most to least importance
ERROR , WARN , INFO , DEBUG1 , DEBUG2 , DEBUG3

LOG_LEVEL determines the highest level that will be logged
ex. LOG_LEVEL = INFO will only print INFO , WARN , ERROR


// USAGE //

#include "Logger.h" //required for every file using logging
const LogLevel LOG_LEVEL = LOG_ALL; // this is required only once in Main


log( DEBUG1 ) << "Mouse position: " << pos.x() << " , " << pos.y();
*/



enum LogLevel { ERROR , WARN , INFO , DEBUG1 , DEBUG2 , DEBUG3 , LOG_ALL };


class Logger
{
public:

	enum outputDest { BOTH, CONSOLE, FILE };


	//stores the log text in the buffer
	Logger(LogLevel logLevel = ERROR, outputDest dest = BOTH) :
		dest(dest)
	{

#ifdef __MK20DX256__ //this is the Teensy signature
		switch (logLevel)
		{
		case DEBUG1:
		case DEBUG2:
		case DEBUG3:
			buffer += String("DBUG" ) + String( logLevel - INFO );
			break;
		case ERROR:
			buffer += String("ERROR");
			break;
		case WARN:
			buffer += String("WARN ");
			break;
		case INFO:
			buffer += String("INFO ");
			break;
		default:
			Logger(WARN, CONSOLE) << "Invalid logLevel";
			break;
		}

		buffer += String(" : ");
#else
		switch (logLevel)
		{
		case DEBUG1:
		case DEBUG2:
		case DEBUG3:
			buffer << "DBUG" << logLevel - INFO;
			break;
		case ERROR:
			buffer << "ERROR";
			break;
		case WARN:
			buffer << "WARN ";
			break;
		case INFO:
			buffer << "INFO ";
			break;
		default:
			Logger(WARN, CONSOLE) << "Invalid logLevel";
			break;
		}

		buffer << " : "
			<< std::string(logLevel >= DEBUG1 ? (logLevel - INFO) * 2 : 0, ' ');
#endif
	}


	template <typename T>
	Logger & operator<<(T const & value)
	{
#ifdef __MK20DX256__ //this is the Teensy signature
		buffer += String( value );
#else
		buffer << value;
#endif
		return *this;
	}



#ifdef __MK20DX256__ //this is the Teensy signature
	void consoleOut()
	{
		Serial.println(buffer);
		delay(20);
	}
#else
	void consoleOut(const std::string & s)
	{
		std::cout << s;
	}
#endif



#ifdef __MK20DX256__ //this is the Teensy signature
#else
	void fileOut(const std::string & s)
	{
		//std::ofstream file(".log", std::ios::app);
	}
#endif

	// prints the log text when the object destructs
	~Logger()
	{
#ifdef __MK20DX256__ //this is the Teensy signature
		if (dest != FILE )
		{
			consoleOut();
		}
#else
		buffer << std::endl;
		std::string s = buffer.str();

		switch ( dest )
		{
		case Logger::BOTH:
			fileOut(s);
			consoleOut(s);
			break;
		case Logger::CONSOLE:
			consoleOut(s);
			break;
		case Logger::FILE:
			fileOut(s);
			break;
		}	
#endif
		
	}

private:
#ifdef __MK20DX256__ //this is the Teensy signature
	String buffer;
#else
	std::ostringstream buffer;
#endif
	outputDest dest;
};

extern const LogLevel LOG_LEVEL; //must be defined in main

//file and console
#define log(level)\
if (level <= LOG_LEVEL)\
Logger(level)

// file only
#define logF(level)\
if (level <= LOG_LEVEL)\
Logger(level , Logger::FILE )

// console only
#define logC(level)\
if (level <= LOG_LEVEL)\
Logger(level , Logger::CONSOLE )
