/*
* ============================================================================
* RDK MANAGEMENT, LLC CONFIDENTIAL AND PROPRIETARY
* ============================================================================
* This file (and its contents) are the intellectual property of RDK Management, LLC.
* It may not be used, copied, distributed or otherwise  disclosed in whole or in
* part without the express written permission of RDK Management, LLC.
* ============================================================================
* Copyright (c) 2014 RDK Management, LLC. All rights reserved.
* ============================================================================
*/

#ifndef _IARM_UTIL_H
#define _IARM_UTIL_H
#include <time.h>
#include <sys/time.h>
#include <stddef.h>
#include <sys/syscall.h>
#include <unistd.h>

#define __TIMESTAMP() do { /*YYMMDD-HH:MM:SS:usec*/               \
            struct tm __tm;                                             \
            struct timeval __tv;                                        \
            gettimeofday(&__tv, NULL);                                  \
            localtime_r(&__tv.tv_sec, &__tm);                           \
            printf("\r\n[tid=%ld]: %02d%02d%02d-%02d:%02d:%02d:%06d ",                 \
                                                syscall(SYS_gettid), \
                                                __tm.tm_year+1900-2000,                             \
                                                __tm.tm_mon+1,                                      \
                                                __tm.tm_mday,                                       \
                                                __tm.tm_hour,                                       \
                                                __tm.tm_min,                                        \
                                                __tm.tm_sec,                                        \
                                                (int)__tv.tv_usec);                                      \
} while(0)                              


#ifndef offsetof
#define offsetof(type, member) ((size_t) &((type *)0)->member)
#endif
#define container_of(ptr, type, member) ({          \
            const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
            (type *)( (char *)__mptr - offsetof(type,member) );})



#define _RETURN_IF_ERROR(cond, err) do {\
    if (!(cond)) { \
        printf("ERROR at [%s][%d]\r\n", __FILE__, __LINE__);\
        return (err); \
    } \
}while(0)

#define _DEBUG_ENTER() do {\
}while(0)

#define _DEBUG_EXIT(ret)  do {\
}while(0)

typedef void (*IARM_Bus_LogCb)(const char *);

#ifdef __cplusplus
extern "C" 
{
#endif

void IARM_Bus_RegisterForLog(IARM_Bus_LogCb cb); 

#ifdef __cplusplus
};
#endif

#endif
