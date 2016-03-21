
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

