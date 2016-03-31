#include "micromouse/Logger.h"
const LogLevel LOG_LEVEL = DEBUG3;

#include <iostream>
#include <cstdlib>
#include <ctime> //time
#include <iomanip> //put_time
#include "micromouse/Controller.h"

using namespace std;


int main( int argc , char** argv )
{
	//gets current time and date
	//thx stackoverflow
	auto t = std::time( nullptr );
	auto tm = *std::localtime( &t );

	//log everytime the program runs
	log( INFO ) << "Program Start: " << std::put_time( &tm , "%c" );


	//seed the random function
	srand( (unsigned int)time( NULL ) );


	Micromouse::Controller routine;//begins the maze solving log





	log( INFO ) << "Program End \n\n\n";

	system( "pause" );

	return 0;
}