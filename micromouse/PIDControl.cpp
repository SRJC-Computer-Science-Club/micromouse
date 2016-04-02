//
//  PIDControl.cpp
//  aa
//
//  Created by Yekalo Abraha on 4/1/16.
//  Copyright © 2016 Yikealo Abraha. All rights reserved.
//

#include "PIDControl.hpp"
#include "stdlib.h"


PIDControl::PIDControl(float kp,float ki, float kd)
{
    ErroSum=0;
    ErrorDifference=0;
    Kd=kd;
    Kp=kp;
    Ki=ki;
}



float PIDControl::getCorrection(float error)
{
    ErroSum+=error;
    ErrorDifference=lastError-error;
    return Ki * error + Ki * ErroSum + Kd * ErrorDifference;
}





void PIDControl::setKp(float kp)
{
    Kp=kp;
}




void PIDControl::setKi(float ki)
{
    Ki=ki;
}




void PIDControl::setKd(float kd)
{
    Kd=kd;
}





void PIDControl::reset()
{
    ErroSum=0;
    ErrorDifference=0;
}