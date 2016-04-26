//
//  teensy.cpp
//  yyekalo
//
//  Created by Yekalo Berhane on 4/22/16.
//  Copyright © 2016 Yikealo Abraha. All rights reserved.
//

#include "teensy.h"
#include "Logger.h"

void digitalWrite2(int port,int state)
{

#ifdef __MK20DX256__ // Teensy Compile

    digitalWrite(port,state);

#else

    log(DEBUG4) <<"digitalWrite " << port << " state " << state;

#endif

}





void anglogWrite2(int port,int value)
{

#ifdef __MK20DX256__ // Teensy Compile

    analogWrite(port,value);

#else

    log(DEBUG4) <<"analogWrite " << port << " state " << value;

#endif

}







int analogRead2(int port)
{

#ifdef __MK20DX256__ // Teensy Compile

    return analogRead(port);

#else

    log(DEBUG4) <<"analogRead " << port;

    return 0;

#endif

}






int digitalRead2(int port)
{

#ifdef __MK20DX256__ // Teensy Compile

    return digitalRead(port);
#else

    log(DEBUG4) <<"digitalRead " << port;

    return 0;

#endif

}







void pinMode2(int port,int purpose)
{

#ifdef __MK20DX256__ // Teensy Compile

    //Iam not sure baout this
    pinMode(port,purpose);

#else

    log(DEBUG4) <<"pinMode(" << port <<"," << purpose<<")";

#endif


}







void delay2(int time)
{

#ifdef __MK20DX256__ // Teensy Compile

   delay(time);

#else

    log(DEBUG4) <<"delay for " << time;

#endif

}





//cli
//sei

void delayMicroseconds2(int microseconds)
{
#ifdef __MK20DX256__ // Teensy Compile

    delayMicroseconds(microseconds);

#else

log(DEBUG4) <<"delayMicroseconds for " << microseconds;

#endif
}






int random2(int value)
{
    #ifdef __MK20DX256__ // Teensy Compile

       return random(value);

    #else

    return rand() % value;

    #endif
}
