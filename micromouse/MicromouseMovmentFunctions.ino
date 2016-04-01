#include <Encoder.h>
int PWMA=9;
int PWMB=10;
int AIN2=11;
int AIN1=12;
int BIN1=16;
int BIN2=17;
int BOUTA=20;
int BOUTB=21;
int AOUTB=8;
int AOUTA=7;
int button=6;
int switch1=0;
int switch2=2;
int switch3=4;
int IRFL=14;
int IRFR=15;
int IRBL=22;
int IRBR=23;


Encoder LeftEncoder(20,21);
Encoder RightEcoder(7,8);



void setup() {
  // put your setup code here, to run once:
pinMode(PWMA,OUTPUT);
pinMode(PWMB,OUTPUT);
pinMode(AIN2,OUTPUT);
pinMode(AIN1,OUTPUT);
pinMode(BIN2,OUTPUT);
pinMode(BIN1,OUTPUT);
pinMode(BOUTA,OUTPUT);
pinMode(BOUTB,OUTPUT);
pinMode(AOUTA,OUTPUT);
pinMode(AOUTB,OUTPUT);
pinMode(button,OUTPUT);
pinMode(switch1,OUTPUT);
pinMode(switch2,OUTPUT);
pinMode(switch3,OUTPUT);
pinMode(IRFR,OUTPUT);
pinMode(IRFL,OUTPUT);
pinMode(IRBR,OUTPUT);
pinMode(IRBL,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  

}
void RmotorF()
{
 digitalWrite(AIN2,HIGH);
 digitalWrite(AIN1,LOW);
   
}

void RmotorB()
{
 digitalWrite(AIN2,LOW);
 digitalWrite(AIN1,HIGH);
   
}
void LmotorB()
{
 digitalWrite(BIN2,LOW);
 digitalWrite(BIN1,HIGH);
   
}
void LmotorF()
{
 digitalWrite(BIN2,HIGH);
 digitalWrite(BIN1,LOW);
   
}

void moveForward(int magnitude)
{
 leftPosition= LeftEncoder.read();
 rightPosition = RightEncoder.read();

 RmotorF();
 LmotorF();
 int rightMotor=0;
 int leftMotor=0;
//while((leftPosition-LeftEncoder.read()*/numberofcountpercell*/)==magnitude);
 while((leftPosition-LeftEncoder.read())==magnitude);
 {
    rightMotor=255;
    leftMotor=255
  if(analogRead(IRFL)==analogRead(IRFR))
  {
    
    analogWrite(PWMA,rightMotor);
    analogWrite(PWMB,leftMotor);
  }
  else if(analogRead(IRFL)>analogRead(IRFR))
  {
    leftMotor-=pid(IRFL,IRFR);
    digitalWrite(PWMB,LOW); 
   }
   else 
   {
    rightMotor-=pid(IRFL,IRFR);
    digitalWrite(PWMA,LOW);
   }
 } 
}

int pid(int IRFL, int IRFR)
{ 
 int right= analogRead(IRFR);
 int left = analogRead(IRFL);

 return -abs(right-left/right+left)


}

