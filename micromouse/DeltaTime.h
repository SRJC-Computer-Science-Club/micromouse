//
//  DeltaTime.h
//  ProjectTempwork
//
//  Created by Seaney Shell on 4/9/16.
//  Copyright (c) 2016 SRJCCSC. All rights reserved.
//

#ifndef __ProjectTempwork__DeltaTime__
#define __ProjectTempwork__DeltaTime__

#include <stdio.h>

#endif /* defined(__ProjectTempwork__DeltaTime__) */
namespace Micromouse
{
    class DeltaTime
    {
    public:
        DeltaTime();
        ~DeltaTime();
    
        // start counting from current time.
        void start();
        
        // returns current time from last start or reset.
        float getMagnitude();
        
        // returns the current time from last start or restart, sets that time to zero.
        float reset();
    
    
    private:
        float initTime;
    
    
    
    
    
    
    
    
    };
}