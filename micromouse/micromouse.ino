#include <Encoder.h>
#include <EEPROM.h>
#include <avr/io.h>
#include <avr/interrupt.h>


//dont ask
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

extern "C"{
	int _getpid(){ return -1;}
	int _kill(int pid, int sig){ return -1; }
	int _write(){return -1;}
}


#include "Logger.h"
const LogLevel LOG_LEVEL = DEBUG2;

#include "Controller.h"

#define BUTTON_PIN 6

volatile bool buttonFlag;



void setup() 
{
	Serial.begin(9600);



	pinMode(15,INPUT);
	randomSeed(analogRead(15));

	// for (int i = 10; i > 0; i--)
	// {
	// 	Serial.print(i);
	// 	delay(700);
	// }
	pinMode(13, OUTPUT);
	digitalWrite(13, HIGH);
	Micromouse::Controller cont;
}

void loop() {}

