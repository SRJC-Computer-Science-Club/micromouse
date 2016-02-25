//by oran collins this code gets sensor values from the 
//motor and the Infa red sensors, an simply displays them
int sensorPin   = 0; //analog pin 0
int sensorPin1  = 1;//second sensor pin at analog 1
int sensorPin2  = 2;
int encoderPin3 = 3;//use pin three for encoder

void setup(){
  Serial.begin(9600);
}

void loop(){
  int rightIRsensor = analogRead(sensorPin);
  int leftIRsensor  = analogRead(sensorPin1);
  int frontIRsensor = analogRead(sensorPin2);
  int moterSensor   = analogRead(encoderPin3);
  // EX
  //Right Sensor : 166, Left Sensor : 131, Front Sensor : 144, Encoder Value : 144
  Serial.print("Right Sensor : ");
  Serial.print(rightIRsensor);
  Serial.print(", Left Sensor : ");
  Serial.print(leftIRsensor);
  Serial.print(", Front Sensor : ");
  Serial.print(frontIRsensor);
  Serial.print(", Encoder Value : ");
  Serial.println(moterSensor); 

  //just to slow down the output - remove if trying to catch an object passing by
  delay(100);

}
