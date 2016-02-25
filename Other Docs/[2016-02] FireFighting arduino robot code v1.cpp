#include <AFMotor.h>

char keyboard; // variable to receive data from the serial port
int tingy;
AF_DCMotor motor1(2, MOTOR12_64KHZ); // create motor #2, 64KHz pwm 
AF_DCMotor motor2(4, MOTOR12_64KHZ); // create motor #2, 64KHz pwm
void setup() {

 // pinMode(ledpin, OUTPUT);  // pin 48 (on-board LED) as OUTPUT
  Serial.begin(9600);       // start serial communication at 9600bps
  motor.setSpeed(200);
}

void loop() {
	
  Serial.print("Hello world");
  
  if( Serial.available() )       // if data is available to read
  {
    keyboard = Serial.read();         // read it and store it in 'val'
  }
  if( keyboard == 'w' ){    
//motor2 left is 4 and motor1 right is 2 with the gear box positioned at back
  motor1.run(FORWARD);
  delay(1000);  
  motor2.run(FORWARD);
  delay(1000);  
  
  } else if(keyboard == 's'){ 
  
  motor1.run(BACKWARD);
  delay(1000);
  motor2.run(BACKWARD);
  delay(1000);
  
  }else if(keyboard == 'a' ){ 
  
  motor2.run(BACKWARD);
  delay(1000);
  motor1.run(FORWARD);
  delay(1000);
  
  }else if(keyboard == 'd' ){
  motor1.run(BACKWARD);
  delay(1000);
  motor2.run(FORWARD);
  delay(1000);
  }else if(keyboard == 'e'){
  Serial.print("E for error. this is an error kinda well its not sorry");
  Serial.print("tack");
  motor.run(RELEASE);      // stopped
  delay(1000); 
 }
  //delay(100);                    // wait 100ms for next reading

} 
