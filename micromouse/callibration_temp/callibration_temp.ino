	

int IR_PIN = 5;
int sample = 50;

void setup() {
  // put your setup code here, to run once:
	Serial.begin(9600);
}

void loop() {
	int val = 0;
	for (int x = 0; x < sample; x++)
	{
		val += analogRead(IR_PIN);
		delay(1);
	}
	val /= sample;
	float dist = pow(2.7183f, 0.00431 * ( 810 - val ) );
	//Serial.println(val);
	Serial.println(dist);
	delay(20);
  // put your main code here, to run repeatedly:

}

