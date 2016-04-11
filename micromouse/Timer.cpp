//
//  DeltaTime.cpp
//  MicroMouse
//
//  Created by Seaney Shell ( github username RosyMapleMoth) on 4/9/16.
//  Copyright (c) 2016 SRJCCSC. All rights reserved.
//
//
#include "Timer.h"


namespace Micromouse
{

    Timer::Timer()
    {
        start();
    }

    
    // can be used tore init time
    void Timer::start()
    {
        lastTime = micros();
    }
    
    
    
    float Timer::getDeltaTime()
    {
        long currentTime = micros();
        float deltaTime = (currentTime - lastTime) / 1000000.0f;
        lastTime = currentTime;
        return deltaTime;
    }
    
#ifndef __MK20DX256__
    long Timer::micros()
    {
        using namespace std::chrono;
        
        return duration_cast<microseconds>(high_resolution_clock::now() - initialTime).count();
    }
#endif
}