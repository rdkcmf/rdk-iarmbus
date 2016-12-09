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


#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "libIBus.h"
#include "barMgr.h"

static void _dummyEventHandler(const char *owner, IARM_EventId_t eventId, void *data, size_t len);

int main(int argc, char *argv[])
{
	int i = 0;
    /*
     * Register and Connect to the IARM Bus.
     *
     */
    IARM_Bus_Init("Sample App");
    IARM_Bus_Connect();

    /*
     * After connection, SampleApp can communicate with entities on the IARM Bus.
     * 1. Register Handlers for BarMgr's published events.
     * 2. Invoke RPC calls to BarMgr's published methods.
     */
    IARM_Bus_RegisterEventHandler(IARM_BUS_BARMGR_NAME, IARM_BUS_BARMGR_EVENT_DUMMY1, _dummyEventHandler);
    IARM_Bus_RegisterEventHandler(IARM_BUS_BARMGR_NAME, IARM_BUS_BARMGR_EVENT_DUMMY2, _dummyEventHandler);

    while (i < 20) {
    	i++;
    	printf("SampleApp heartbeat\r\n");
    	IARM_Bus_BarMgr_DummyAPI0_Param_t param0;
    	IARM_Bus_BarMgr_DummyAPI1_Param_t param1;

    	/* populate param0, param1 here */
    	IARM_Bus_Call(IARM_BUS_BARMGR_NAME, IARM_BUS_BARMGR_API_DummyAPI0, (void *)&param0, sizeof(param0));
    	IARM_Bus_Call(IARM_BUS_BARMGR_NAME, IARM_BUS_BARMGR_API_DummyAPI1, (void *)&param1, sizeof(param1));
    	sleep(10);
    }

    IARM_Bus_Disconnect();
    IARM_Bus_Term();
}


static void _dummyEventHandler(const char *owner, IARM_EventId_t eventId, void *data, size_t len)
{

	if (strcmp(owner, IARM_BUS_BARMGR_NAME) == 0) {
		/* Handle BarMgr's events here */
		IARM_Bus_BarMgr_EventData_t *eventData = (IARM_Bus_BarMgr_EventData_t *)data;

		switch(eventId) {
		case IARM_BUS_BARMGR_EVENT_DUMMY0:
			break;
		case IARM_BUS_BARMGR_EVENT_DUMMY1:
			break;
		case IARM_BUS_BARMGR_EVENT_DUMMY2:
			break;
		}
	}
	else if (/* compare owner compare other names */1) {
		/* Handle Another owner's events here */
	}
	else {
	}
}


/** @} */
/** @} */
