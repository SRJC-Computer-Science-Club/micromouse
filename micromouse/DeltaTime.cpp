//
//  DeltaTime.cpp
//  ProjectTempwork
//
//  Created by Seaney Shell on 4/9/16.
//  Copyright (c) 2016 SRJCCSC. All rights reserved.
//
#pragma once
#ifdef __MK20DX256__
#include <Arduino.h>//random
#else
#endif
#include "DeltaTime.h"

namespace Micromouse
{

    DeltaTime::DeltaTime()
    {
        start();
    }
    
    
    
    DeltaTime::~DeltaTime()
    {
        
    }

    
    // can be used tore init time
    void DeltaTime::start()
    {
#ifdef __MK20DX256__
        initTime = micros();
#endif
    }
    
    
    
    float DeltaTime::getMagnitude()
    {
#ifdef __MK20DX256__
        return (initTime - micros());
#else
        return (initTime);
#endif
    }
    
    float DeltaTime::reset()
    {
#ifdef __MK20DX256__
        return (initTime - micros());
        initTime = micros();
#else
        return initTime;
#endif
    }
}