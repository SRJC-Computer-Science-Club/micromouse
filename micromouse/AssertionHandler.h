//
//  AssertionHandler.h
//  micromouse-xcode
//
//  Created by Erick Sanchez on 4/20/16.
//  Copyright © 2016 Erick Sanchez. All rights reserved.
//

#ifndef AssertionHandler_h
#define AssertionHandler_h

#include "Logger.h"

#ifdef __MK20DX256__ // Teensy Compile

//Prints to concole using Logger(..) << code and metadata of the assertion
#define assertion(condition,code) \
( \
(__builtin_expect(!(condition), 0) ? (void)(Logger(ERROR)<<"("<<#condition<<")"<<" code: "<<code<<" @ "<<__FILE__<<" function -"<<__func__<<", line:"<<__LINE__) : (void)0) \
)

#else

//Prints to concole using the definition of assert(e) declared in assert.h
#define assertion(condition,code) \
( \
(__builtin_expect(!(condition), 0) ? __assert_rtn(__func__, __FILE__, __LINE__, #condition) : (void)0) \
)

#endif

#endif /* AssertionHandler_h */
