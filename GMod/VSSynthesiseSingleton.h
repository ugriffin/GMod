//
//  VSSynthesiseSingleton.h
//  Vetra Games / VetraSoft
//
//  Credit to Uriel Griffin in your app/software/whatever is not required but appreciated.
//
//  Created by Uriel Griffin on the 17th of March, 2015, in Melbourne, Australia.
//  Copyright (c) 2015 Uriel Griffin. All rights reserved.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//  SOFTWARE.
//
//  Inspired by CocoaWithLove's CWLSynthesizeSingleton.h, created by Matt Gallagher. Infinitely useful macro. Many thanks. :)

#ifndef VSSynthesiseSingleton_h
#define VSSynthesiseSingleton_h

#define VS_DECLARESINGLETON(__CLASSNAME__,__ACCESSORNAME__)\
\
private:\
\
static bool instanceFlag;\
static __CLASSNAME__ *single;\
\
__CLASSNAME__();\
\
void init();\
void destroy();\
\
public:\
\
static __CLASSNAME__* __ACCESSORNAME__();\
~__CLASSNAME__();\


#define VS_SYNTHESISESINGLETON(__CLASSNAME__,__ACCESSORNAME__)\
\
bool __CLASSNAME__::instanceFlag = false;\
__CLASSNAME__* __CLASSNAME__::single = NULL;\
\
\
__CLASSNAME__::__CLASSNAME__()\
{\
    this->init();\
}\
\
\
__CLASSNAME__::~__CLASSNAME__()\
{\
    instanceFlag = false;\
    this->destroy();\
}\
\
\
__CLASSNAME__* __CLASSNAME__::__ACCESSORNAME__()\
{\
    if(! instanceFlag)\
    {\
        single = new __CLASSNAME__();\
        instanceFlag = true;\
        return single;\
    }\
    else\
    {\
        return single;\
    }\
}\


#endif
