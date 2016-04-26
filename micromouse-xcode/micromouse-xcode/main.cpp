#include "Logger.h"
const LogLevel LOG_LEVEL = DEBUG2;


#include <iostream>
#include <cstdlib>
#include <ctime> //time
#include "Controller.h"



using namespace std;

volatile bool buttonFlag;

int main( int argc , char** argv )
{
    //seed the random function
    srand( (unsigned int)time( NULL ) );
    
    Micromouse::Controller routine;
    
    system( "pause" );
    
    return 0;
}