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


#include "barMgr.h"
#include "barMgrInternal.h"


int main(int argc, char *argv[])
{
	IARM_BarMgr_Start(argc, argv);
	IARM_BarMgr_Loop();
	IARM_BarMgr_Stop();
}


/** @} */
/** @} */
