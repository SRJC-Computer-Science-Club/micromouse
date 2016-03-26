
namespace std {
  void __throw_bad_alloc()
  {
    Serial.println("Unable to allocate memory");
  }

  void __throw_length_error( char const*e )
  {
    Serial.print("Length Error :");
    Serial.println(e);
  }
}

#include "Logger.h"
const LogLevel LOG_LEVEL = DEBUG3;

#include "Controller.h"
#include <ostream>

void setup() {

	Serial.begin(9600);


    for (int i = 10; i > 0; i--)
    {
	    Serial.print(i);
	    delay(800);
    }

	Serial.println();

	Micromouse::Controller cont;
	}

void loop()
{
}


// int main( int argc , char** argv )
// {

// 	int i = 10;
// 	pinMode(13, OUTPUT);
// 	while( true )
// 	{
// Serial.print("sfg");
// 		digitalWrite( 13 , HIGH );
// 	delay(i);
// 	digitalWrite( 13 , LOW );	
// 	delay(2*i);
// 	i++;
// 	}
// }

