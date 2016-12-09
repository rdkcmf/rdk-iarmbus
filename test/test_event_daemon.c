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


/**
* @defgroup iarmbus
* @{
* @defgroup test
* @{
**/


#include "libIBus.h"
#include "libIBusDaemon.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern IARM_Result_t IARM_Bus_DaemonStart(int argc, char *argv[]);
extern IARM_Result_t IARM_Bus_DaemonStop(void);

int main()
{
	printf("server Entering %d\r\n", getpid());
    //IARM_Bus_DaemonStart(0, NULL);
    int i = 0;
    int timedur = 10;;
    int sleepus = 5 * 1000 * 1000;
    while(i++ < timedur) {
    	printf("Send HeartBeat %d\r\n", i);
    	IARM_Bus_EventData_t eventData;
    	eventData.resrcType = (IARM_Bus_ResrcType_t)i;
    	if (i % 3 == 0) {
    		IARM_Bus_BroadcastEvent(IARM_BUS_DAEMON_NAME, IARM_BUS_EVENT_RESOURCEAVAILABLE, (void*) &eventData, sizeof(eventData));
    	}
    	else if (i % 3 == 1) {

    	}
    	else {

    	}
    	usleep(sleepus);

    	printf("Send HeartBeat DONE\r\n");
    }
    //IARM_Bus_DaemonStop();
}



/** @} */
/** @} */
