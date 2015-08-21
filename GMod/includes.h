/*
 *  GMod.h
 *  GMod
 *
 *  Created by Uriel Griffin on 22/08/2015.
 *  Copyright (c) 2015 Vetra Games. All rights reserved.
 *
 */

#ifndef GMod_
#define GMod_


//Define the available platforms...
#define DYLIB_UNKNOWN 0
#define DYLIB_MACOS 1
#define DYLIB_IOS 2
#define DYLIB_LINUX 3
#define DYLIB_WINDOWS 4

//Default definition, this gets redefined.
#define DYLIB_PLATFORM DYLIB_UNKNOWN

//At some point we want to remove duplicates and merge a significant amount of includes (like <vector>) in this file.
#include "bassmod.h"

#ifdef __APPLE__
#include "IncludeDarwin.h" //Darwin is the kernel upon which Mac OS X and iOS depend. No need for separate ports as 39dylib doesn't really touch Cocoa.
#endif

#ifdef __linux__
#include "IncludeLinux.h" //I presume it can be the same as 39dylib_Darwin?
#endif

#if defined _WIN32 || defined __CYGWIN__
#include "IncludeWindows.h"
#endif

//Now,the new definition mechanism for 39dylib!

#if defined _WIN32 || defined __CYGWIN__

//Windows platforms use this attribute marker...
#define DYLIBEXPORT extern "C" __declspec(dllexport)

#else
//Unix (Darwin, Linux, BSD, whatever) can have fun with this one.

#define DYLIBEXPORT extern "C" __attribute__((visibility("default")))

#endif

#endif


