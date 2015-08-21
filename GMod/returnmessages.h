//
//  returnmessages.h
//  GMod
//
//  Created by Uriel Griffin on 22/08/2015.
//  Copyright (c) 2015 Vetra Games. All rights reserved.
//

#ifndef GMod_returnmessages_h
#define GMod_returnmessages_h


#define GMOD_NOERROR 1
#define GMOD_ERROR 0
#define GMOD_NOT_INITIALISED -1
#define GMOD_INIT_FAIL 3
#define GMOD_FILE_LOADERROR 4


#define gmod_checkinit() if(!gmod_isinitialised()){return GMOD_NOT_INITIALISED;}


#endif
