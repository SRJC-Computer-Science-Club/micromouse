


int IR_PIN = 1;
int BUTTON_PIN = 7;
int sample = 50;
int calibration[14];
int SEP = 2;
int START = 4;

void calibrate();
void distance();
float interpolate(int x1, int x2, int y1, int y2, int x);

void setup() {
	// put your setup code here, to run once:
	Serial.begin(9600);
	calibrate();
}

void loop() {


	distance();
	delay(50);
	// put your main code here, to run repeatedly:

}

void calibrate()
{

	for (int i = 0; i < 14; i++)
	{
		Serial.print("distance: ");
		Serial.println(i * 2 + 4);

		//TODO interrupts
		while (!digitalRead(BUTTON_PIN))
		{
			delay(1);
		}
		while (digitalRead(BUTTON_PIN))
		{
			delay(1);
		}

		for (int x = 0; x < sample; x++)
		{
			calibration[i] += analogRead(IR_PIN);
			delay(1);
		}

		calibration[i] /= sample;
		//calibration[i] = 700 - i *40;

		Serial.println(calibration[i]);


	}
}

void distance()
{
	int val = analogRead(IR_PIN);
	for (int i = 13; i >= 0; i--)
	{
		//	Serial.print( calibration[i] );
		//	Serial.print( " : " );
		//	Serial.print( val );
		//	Serial.print( " : ");
		if (val < calibration[i])
		{
			float dist = interpolate(calibration[i], calibration[i + 1], i * SEP + START, (i + 1) * SEP + START, val);
			Serial.print(dist);

			for (int j = 0; j <= dist; j++)
			{
				Serial.print("|");
			}
			Serial.println("");
			break;
		}
	}


}

float interpolate(int x1, int x2, int y1, int y2, int x)
{
	return(float(x - x1) / (x2 - x1)*(y2 - y1) + y1);
}