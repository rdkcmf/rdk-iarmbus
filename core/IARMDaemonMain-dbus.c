/*
 * If not stated otherwise in this file or this component's Licenses.txt file the
 * following copyright and licenses apply:
 *
 * Copyright 2016 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

#include "libIBus.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include "string.h"

#ifdef ENABLE_SD_NOTIFY
#include <systemd/sd-daemon.h>
#endif

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
    #ifdef ENABLE_SD_NOTIFY
    LOG("servers Entering and notifying pid=%d\r\n", getpid());
        sd_notifyf(0, "READY=1\n"
          "STATUS=IARM Daemon is Successfully Initialized\n"
          "MAINPID=%lu",
          (unsigned long) getpid());
    #else
    LOG("servers Entering without notifying pid=%d\r\n", getpid());
    #endif
    time_t curr = 0;
    while(1) {
        time(&curr);
    	LOG("I-ARM Bus Daemon : HeartBeat at %s\r\n", ctime(&curr));
    	sleep(300);
    	/*LOG("Bus Daemon HeartBeat DONE\r\n");*/
    }
    IARM_Bus_DaemonStop();
}

