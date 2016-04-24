#pragma once
extern volatile bool buttonFlag;

// Detects when button has been pressed and exits the current function
// MUST be used with the BUTTONEXIT
#define BUTTONFLAG \
if (buttonFlag) goto BUTTON_EXIT;

// When a BUTTONFLAG is triggered the program control will jump to the BUTTONEXIT line
// Must be placed at the end of the function, just before the return to allow exit
#define BUTTONEXIT \
BUTTON_EXIT:


// EXAMPLE USAGE //
#ifdef this_is_a_comment //syntax highlighting is enabled this way

void someFunction()
{
	for (int i = 0; i < 2000; i++)
	{
		BUTTONFLAG //control jumps to BUTTONEXIT when triggered by button press

		doSomething();
		doSomething();
		delay(200);


		for (int i = 0; i < 2000; i++)
		{
		BUTTONFLAG // multiple BUTTONFLAGs can exist

		doSomething();
		doSomething();
		delay(200);
		}
	}

	// Must be placed at the end of the function, just before the return to allow exit
	// only 1 BUTTONEXIT should exist per function
	BUTTONEXIT

	// Teensy requires there be something after the BUTTONEXIT
	// so for void functions, add return; to the end
	return; 
}

#endif
