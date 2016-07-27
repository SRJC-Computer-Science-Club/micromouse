#ifdef  #ifdef __MK20DX256__ // Teensy Compile
#else //on windows
void delay(int milliseconds){};
#endif

#ifdef  #ifdef __MK20DX256__ // Teensy Compile
#else //on windows
void digitalWrite(int pin, bool high){};
#endif
