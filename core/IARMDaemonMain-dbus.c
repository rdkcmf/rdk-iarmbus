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

#include "libIBus.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include "string.h"

#ifdef RDK_LOGGER_ENABLED
#include "rdk_debug.h"
#include "iarmUtil.h"
#endif

extern IARM_Result_t IARM_Bus_DaemonStart(int argc, char *argv[]);
extern IARM_Result_t IARM_Bus_DaemonStop(void);

int b_rdk_logger_enabled = 0;

#ifdef RDK_LOGGER_ENABLED

#define INT_LOG(FORMAT, ...)     if(b_rdk_logger_enabled) {\
RDK_LOG(RDK_LOG_DEBUG, "LOG.RDK.IARMBUS", FORMAT , __VA_ARGS__);\
}\
else\
{\
printf(FORMAT, __VA_ARGS__);\
}

#else

#define INT_LOG(FORMAT, ...)      printf(FORMAT, __VA_ARGS__)

#endif

#define LOG(...)              INT_LOG(__VA_ARGS__, "")

#ifdef RDK_LOGGER_ENABLED
void logCallback(const char *buff)
{
    LOG("%s",buff);
}
#endif

int main(int argc,char *argv[])
{
    const char* debugConfigFile = NULL;
    int itr=0;

        while (itr < argc)
        {
                if(strcmp(argv[itr],"--debugconfig")==0)
                {
                        itr++;
                        if (itr < argc)
                        {
                                debugConfigFile = argv[itr];
                        }
                        else
                        {
                                break;
                        }
                }
                itr++;
        }

#ifdef RDK_LOGGER_ENABLED

    if(rdk_logger_init(debugConfigFile) == 0) b_rdk_logger_enabled = 1;
    IARM_Bus_RegisterForLog(logCallback);

#endif
	setvbuf(stdout, NULL, _IOLBF, 0);
    LOG("server Entering %d\r\n", getpid());
    IARM_Bus_DaemonStart(0, NULL);
    time_t curr = 0;
    while(1) {
        time(&curr);
    	LOG("I-ARM Bus Daemon : HeartBeat at %s\r\n", ctime(&curr));
    	sleep(300);
    	/*LOG("Bus Daemon HeartBeat DONE\r\n");*/
    }
    IARM_Bus_DaemonStop();
}

