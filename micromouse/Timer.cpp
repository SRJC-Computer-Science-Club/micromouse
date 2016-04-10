//
//  DeltaTime.cpp
//  MicroMouse
//
//  Created by Seaney Shell ( github username RosyMapleMoth) on 4/9/16.
//  Copyright (c) 2016 SRJCCSC. All rights reserved.
//
//
#pragma once
#ifdef __MK20DX256__
#include <Arduino.h>//random
#else
#endif
#include "DeltaTime.h"

namespace Micromouse
{

    Timer::DeltaTime()
    {
        start();
    }
    
    
    
    Timer::~DeltaTime()
    {
        
    }

    
    // can be used tore init time
    void Timer::start()
    {
#ifdef __MK20DX256__
        initTime = micros();
#endif
    }
    
    
    
    float Timer::getDeltaTime()
    {
#ifdef __MK20DX256__
        return (initTime - micros());
#else
        return (initTime);
#endif
    }
    
    float Timer::reset()
    {
#ifdef __MK20DX256__
        return (initTime - micros());
        initTime = micros();
#else
        return initTime;
#endif
    }
}