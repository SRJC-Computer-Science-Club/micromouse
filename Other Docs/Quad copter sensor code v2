const int anPin =A0;//pins for sonar sensor analog, power, ground, A0, 5v, GND.
//steper motor pins DIGITAL, DITIGAL, 9, 8.
long anVolt, mm, inches;
void setup() {  
  Serial.begin(9600);
                
  pinMode(8, OUTPUT);      
  pinMode(9, OUTPUT);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
}

void loop() {

for(int count=0; count < 1650; count++)//left turn
{
  if(count %20 == 0)
  {SensorRead(count);
  //delay(200);
  }
  digitalWrite(8,LOW);
  digitalWrite(9, HIGH);
  delay(1);          
  digitalWrite(9, LOW); 
  delay(1);
}
  for(int count=0; count < 1650; count++)//left turn
{
  if(count %20 == 0)
  {SensorRead(count);
  //delay(200);
  }
  digitalWrite(8,HIGH);
  digitalWrite(9, HIGH);
  delay(1);          
  digitalWrite(9, LOW); 
  delay(1);
}     
  
}

void SensorRead(int x)//move the server 50 steps 
{
  anVolt= analogRead(anPin);
  mm = anVolt * 5;
  inches = mm/25.4;
 // Serial.println("DEGREES");
  //Serial.print("=");
  Serial.print(x);
  Serial.print(",");
  Serial.println(inches);
  //out put looks line NUMBER,NUMBER IE 123,432
}

