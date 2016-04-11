//
//  DeltaTime.h
//  MicroMouse
//
//  Created by Seaney Shell ( github username RosyMapleMoth) on 4/9/16.
//  Copyright (c) 2016 SRJCCSC. All rights reserved.
//

#ifndef __ProjectTempwork__DeltaTime__
#define __ProjectTempwork__DeltaTime__
#ifndef __MK20DX256__
#include <chrono>
#else 
#include "arduino.h"
#endif
#include <stdio.h>

#endif /* defined(__ProjectTempwork__DeltaTime__) */
namespace Micromouse
{
    class Timer
    {
    public:
        Timer();
    
        // start counting from current time.
        void start();
        
        // returns current time from last start() or getDeltaTime().
        float getDeltaTime();
    
    
    private:
        
#ifndef __MK20DX256__
        // If on PC
        long micros();
        
        typedef std::chrono::steady_clock::time_point time_point;
        time_point initialTime = std::chrono::high_resolution_clock::now();
#endif
        float lastTime;
    
    
    
    
    
    
    
    
    };
}