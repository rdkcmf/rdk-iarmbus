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


#ifndef _IARM_BUS_BARMGR_H
#define _IARM_BUS_BARMGR_H

#ifdef __cplusplus
extern "C" 
{
#endif
#define IARM_BUS_BARMGR_NAME 						"BarMgr"
/*
 * Declare Published Events
 */
typedef enum _BarMgr_EventId_t {
	IARM_BUS_BARMGR_EVENT_DUMMY0,
    IARM_BUS_BARMGR_EVENT_DUMMY1,
    IARM_BUS_BARMGR_EVENT_DUMMY2,

    IARM_BUS_BARMGR_EVENT_MAX,
} IARM_Bus_BarMgr_EventId_t;

/*
 * Declare Event Data
 */
typedef struct _BarMgr_EventData_t {
    union {
        struct _EventData_DUMMY_0{
        	/* Declare Event Data structure for BARMGR_EVENT_DUMMY0 */
        	int dummyData;
        } dummy0;
        struct _EventData_DUMMY_1{
        	/* Declare Event Data structure for BARMGR_EVENT_DUMMY1 */
        	int dummyData;
        } dummy1;
        struct _EventData_DUMMY_2{
        	/* Declare Event Data structure for BARMGR_EVENT_DUMMY2 */
        	int dummyData;
        } dummy2;
    } data;
}IARM_Bus_BarMgr_EventData_t;

/*
 * Declare RPC API names and their arguments
 */
#define IARM_BUS_BARMGR_API_DummyAPI0 		"DummyAPI0"
typedef struct _IARM_Bus_BarMgr_DummyAPI0_Param_t {
	/* Declare Argument Data structure for DummyAPI0 */
} IARM_Bus_BarMgr_DummyAPI0_Param_t;

#define IARM_BUS_BARMGR_API_DummyAPI1 		"DummyAPI1"
typedef struct _IARM_Bus_BarMgr_DummyAPI1_Param_t {
	/* Declare Argument Data structure for DummyAPI1 */
} IARM_Bus_BarMgr_DummyAPI1_Param_t;

#ifdef __cplusplus
}
#endif
#endif


/** @} */
/** @} */
