void setup() {
}

int main( int argc , char** argv )
{
	int i = 10;
	pinMode(13, OUTPUT);
	while( true )
	{
		digitalWrite( 13 , HIGH );
	delay(i);
	digitalWrite( 13 , LOW );	
	delay(2*i);
	i++;
	}
}

// void loop() {
//   // put your main code here, to run repeatedly:
//    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
//   delay(1000);               // wait for a second
//   digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
//   delay(1000);               // wait for a second
//   Serial.print(pos.x());
// }

