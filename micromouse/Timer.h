//
//  DeltaTime.h
//  MicroMouse
//
//  Created by Seaney Shell ( github username RosyMapleMoth) on 4/9/16.
//  Copyright (c) 2016 SRJCCSC. All rights reserved.
//

#ifndef __ProjectTempwork__DeltaTime__
#define __ProjectTempwork__DeltaTime__

#include <stdio.h>

#endif /* defined(__ProjectTempwork__DeltaTime__) */
namespace Micromouse
{
    class Timer
    {
    public:
        DeltaTime();
        ~DeltaTime();
    
        // start counting from current time.
        void start();
        
        // returns current time from last start or reset.
        float getDeltaTime();
        
        // returns the current time from last start or restart, sets that time to zero.
        float reset();
    
    
    private:
        float initTime;
    
    
    
    
    
    
    
    
    };
}