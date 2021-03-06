﻿
#ifndef AVDefine_h
#define AVDefine_h

#include "stdint.h"
typedef enum {
	NO_MEDIA = 0,
	AUDIO_MEDIA,
	VIDEO_MEDIA,
	NumOfMedia = 3
}MediaType;

typedef struct MediaFrame
{
	uint8_t* data;
	int len;
	long ts;
	MediaType type;
}MediaFrame;

#ifdef IOS
#define Version_iOS_8 ((NSFoundationVersionNumber >= NSFoundationVersionNumber_iOS_8_0) ? YES : NO)
#endif // IOS

typedef enum {
  
}ErrorCode;
typedef enum {
    Warning_BindwidthSent_Bad,
}WarningCode;

class Reporter
{
public:
    virtual void onError(ErrorCode err){};
    virtual void onWarning(WarningCode warning){};
};
#endif

