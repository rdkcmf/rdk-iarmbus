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


#ifndef _IARM_BARMGR_INTERNAL_H
#define _IARM_BARMGR_INTERNAL_H
#include "libIARM.h"
#include "barMgr.h"
/*
 * Data structures used for BarMgr's internal implementation.
 */
IARM_Result_t IARM_BarMgr_Start(int argc, char *argv[]);
void IARM_BarMgr_Loop(void);
IARM_Result_t IARM_BarMgr_Stop(void);

#endif


/** @} */
/** @} */
