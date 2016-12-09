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
* @defgroup template
* @{
**/


#include <stdio.h>
#include <unistd.h>
#include "iarmUtil.h"
#include "libIARM.h"
#include "libIBus.h"
#include "barMgr.h"
#include "barMgrInternal.h"

static IARM_Result_t _dummyAPI0	(void *arg);
static IARM_Result_t _dummyAPI1	(void *arg);

IARM_Result_t IARM_BarMgr_Start(int argc, char *argv[])
{

    IARM_Result_t retCode = IARM_RESULT_SUCCESS;
    /* If any, Process argc, argv */

    /*
     * Register and Connect to the IARM Bus
     */
    IARM_Bus_Init(IARM_BUS_BARMGR_NAME);
    IARM_Bus_Connect();

    /*
     * Register Events that this module publishes
     */
    IARM_Bus_RegisterEvent(IARM_BUS_BARMGR_EVENT_MAX);

    /*
     * Register APIs that can be RPCs by other entities on the bus.
     */
     IARM_Bus_RegisterCall(IARM_BUS_BARMGR_API_DummyAPI0,  	_dummyAPI0);
     IARM_Bus_RegisterCall(IARM_BUS_BARMGR_API_DummyAPI1,  	_dummyAPI1);

    return retCode;
}

void IARM_BarMgr_Loop()
{
	int i = 0;
	while (++i) {
		/* Infinite Loop listening for component specific events from drivers */
		printf("[%s]: Heartbeat\r\n", __FUNCTION__);
		IARM_Bus_BarMgr_EventData_t eventData;
		/* Populate Event Data Here */
		eventData.data.dummy0.dummyData = i;
		IARM_Bus_BroadcastEvent(IARM_BUS_BARMGR_NAME, IARM_BUS_BARMGR_EVENT_DUMMY0, &eventData, sizeof(eventData));
		sleep(10);
	}
}

IARM_Result_t IARM_BarMgr_Stop(void)
{
    IARM_Result_t retCode = IARM_RESULT_SUCCESS;
	IARM_Bus_Disconnect();
    IARM_Bus_Term();
    return retCode;
}

/**
 *
 * @param [in] arg reference of IARM_Bus_Member_t of the caller trying to register with UIMgr. This is allocated from shared memory
 */
static IARM_Result_t _dummyAPI0(void *arg)
{
    IARM_Result_t retCode = IARM_RESULT_SUCCESS;
    IARM_Bus_BarMgr_DummyAPI0_Param_t *param = (IARM_Bus_BarMgr_DummyAPI0_Param_t *)arg;
    param = param;
    /*
     * Implementation;
     */
    return retCode;

}

static IARM_Result_t _dummyAPI1(void *arg)
{
    IARM_Result_t retCode = IARM_RESULT_SUCCESS;
    IARM_Bus_BarMgr_DummyAPI1_Param_t *param = (IARM_Bus_BarMgr_DummyAPI1_Param_t *)arg;
    param = param;
    /*
     * Implementation;
     */
    return retCode;
}





/** @} */
/** @} */
