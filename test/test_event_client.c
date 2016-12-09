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


static void _handler_ResourceAvailable(const char *owner, IARM_EventId_t eventId, void *data, size_t len)
{
	IARM_Bus_EventData_t *busEventData = (IARM_Bus_EventData_t *)data;
	printf("=======================_handler_ResourceAvailable Received Event [%d] from [%s] for [%d]", eventId, owner, busEventData->resrcType);
}

static void _handler_PostChange(const char *owner, IARM_EventId_t eventId, void *data, size_t len)
{
	IARM_Bus_EventData_t *busEventData = (IARM_Bus_EventData_t *)data;
	printf("=============================_=handler_PostChange Received Event [%d] from [%s] for [%d]", eventId, owner, busEventData->resrcType);
}

static void _handler_PreChange(const char *owner, IARM_EventId_t eventId, void *data, size_t len)
{
	IARM_Bus_EventData_t *busEventData = (IARM_Bus_EventData_t *)data;
	printf("================================_handler_PreChange Received Event [%d] from [%s] for [%d]", eventId, owner, busEventData->resrcType);
}

int main()
{
	printf("EventClient Entering %d\r\n", getpid());
	IARM_Bus_Init("Client");
	int i = 0;
	IARM_Bus_Connect();
	IARM_Bus_RegisterEventHandler(IARM_BUS_DAEMON_NAME, IARM_BUS_EVENT_RESOURCEAVAILABLE, 	_handler_ResourceAvailable);

	while(++i < 5) {
		printf("Client Hearbeat\r\n");
		sleep(5);
	}
	IARM_Bus_Disconnect();
	IARM_Bus_Term();
	printf("Client Exiting\r\n");
}


/** @} */
/** @} */
