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
    while(i++ < 10000) {
    	printf("Bus Daemon HeartBeat %d\r\n", i);
    	sleep(5);
    	printf("Bus Daemon HeartBeat DONE\r\n");
    }
    //IARM_Bus_DaemonStop();
}



/** @} */
/** @} */
