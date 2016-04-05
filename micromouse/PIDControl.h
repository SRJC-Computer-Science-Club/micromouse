//
//  PIDControl.hpp
//  aa
//
//  Created by Yekalo Abraha on 4/1/16.
//  Copyright © 2016 Yikealo Abraha. All rights reserved.
//

#ifndef PIDControl_hpp
#define PIDControl_hpp

#include <stdio.h>

class PIDControl
{
public:
    PIDControl(float kp,float ki, float kd=0);
    float getCorrection(float Error);
    void setKp(float kp);
    void setKi(float ki);
    void setKd(float kd);
    void reset();
    
private:
    float ErroSum;
    float ErrorDifference;
    float lastError;
    float Kp;
    float Ki;
    float Kd;
    
};



























#endif /* PIDControl_hpp */
