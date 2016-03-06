#pragma once
#include <iostream>
#include <sstream>
#include <fstream>

/*
This is a helper class that makes logging information easy
it will output anything that can use <<

it uses 3 different macros defined at the bottom of the file to make
logging as short and quick as possible

log( logLevel ) will output to both the console and the log file
logC( logLevel ) will output to the console only
logF( logLevel ) will output to the log file only

log level defines the importance of the log
the log type from most to least importance
ERROR , WARN , INFO , DEBUG1 , DEBUG2 , DEBUG3

LOG_LEVEL determines the highest level that will be logged
ex. LOG_LEVEL = INFO will only print INFO , WARN , ERROR


// USAGE //

#include "Logger.h"
LogLevel LOG_LEVEL = LOG_ALL; // this is required


log( DEBUG1 ) << "Mouse position: " << pos.x() << " , " << pos.y();
*/



enum LogLevel { ERROR , WARN , INFO , DEBUG1 , DEBUG2 , DEBUG3 , LOG_ALL };


class Logger
{
public:

	enum outputDest { BOTH , CONSOLE , FILE };


	//stores the log text in the buffer
	Logger( LogLevel logLevel = ERROR , outputDest dest = BOTH ) :
		dest( dest )
	{
		switch ( logLevel )
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
			Logger( WARN , CONSOLE ) << "Invalid logLevel";
			break;
		}

		buffer << " : "
			<< std::string( logLevel >= DEBUG1 ? ( logLevel - INFO ) * 2 : 0 , ' ' );
	}


	template <typename T>
	Logger & operator<<( T const & value )
	{
		buffer << value;
		return *this;
	}

	// prints the log text when the object destructs
	~Logger()
	{
		buffer << std::endl;
		std::ofstream file( ".log" , std::ios::app );
		std::string s = buffer.str();
		
		switch ( dest )
		{
		case Logger::BOTH:
			file << s;
			std::cout << s;
			break;
		case Logger::CONSOLE:
			std::cout << s;
			break;
		case Logger::FILE:
			file << s;
			break;
		}	
	}

private:
	std::ostringstream buffer;
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
