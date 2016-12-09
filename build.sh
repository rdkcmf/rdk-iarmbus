#!/bin/bash
#
# ============================================================================
# RDK MANAGEMENT, LLC CONFIDENTIAL AND PROPRIETARY
# ============================================================================
# This file (and its contents) are the intellectual property of RDK Management, LLC.
# It may not be used, copied, distributed or otherwise  disclosed in whole or in
# part without the express written permission of RDK Management, LLC.
# ============================================================================
# Copyright (c) 2014 RDK Management, LLC. All rights reserved.
# ============================================================================
#
set -x

if [ -z $PLATFORM_SOC ]; then
    export PLATFORM_SOC=intel
fi

SCRIPT=$(readlink -f "$0")
SCRIPTS_DIR=`dirname "$SCRIPT"`
export BUILDS_DIR=$SCRIPTS_DIR/..
export COMBINED_ROOT=$BUILDS_DIR
export DS_PATH=$BUILDS_DIR/devicesettings
export IARM_MGRS=$BUILDS_DIR/iarmmgrs
if [ $PLATFORM_SOC = "intel" ]; then
	export TOOLCHAIN_DIR=$COMBINED_ROOT/sdk/toolchain/staging_dir
	export CROSS_TOOLCHAIN=$TOOLCHAIN_DIR
	export CROSS_COMPILE=$CROSS_TOOLCHAIN/bin/i686-cm-linux
	export CC=$CROSS_COMPILE-gcc
	export CXX=$CROSS_COMPILE-g++
	export OPENSOURCE_BASE=$COMBINED_ROOT/opensource
	export DFB_ROOT=$TOOLCHAIN_DIR 
	export DFB_LIB=$TOOLCHAIN_DIR/lib
	export IARM_PATH=$BUILDS_DIR/iarmbus 
	export FUSION_PATH=$OPENSOURCE_BASE/src/FusionDale
	export SDK_FSROOT=$COMBINED_ROOT/sdk/fsroot/ramdisk
	export FSROOT=$COMBINED_ROOT/sdk/fsroot/ramdisk
	export GLIB_INCLUDE_PATH=$CROSS_TOOLCHAIN/include/glib-2.0/
        export GLIB_LIBRARY_PATH=$CROSS_TOOLCHAIN/lib/
        export GLIB_CONFIG_INCLUDE_PATH=$GLIB_LIBRARY_PATH/glib-2.0/
	export GLIBS='-lglib-2.0 -lz'
 elif [ $PLATFORM_SOC = "broadcom" ]; then 
	export WORK_DIR=$BUILDS_DIR/workXI3
	. $BUILDS_DIR/build_scripts/setBCMenv.sh
	export MFR_PATH=$WORK_DIR/svn/sdk/mfrlib
	export OPENSOURCE_BASE=$BUILDS_DIR/opensource
	export IARM_PATH=$BUILDS_DIR/iarmbus
	export FUSION_PATH=$OPENSOURCE_BASE/FusionDale
	export FSROOT=$COMBINED_ROOT/sdk/fsroot/ramdisk
	CROSS_COMPILE=mipsel-linux
	export CC=$CROSS_COMPILE-gcc
	export CXX=$CROSS_COMPILE-g++
	export GLIB_INCLUDE_PATH=$APPLIBS_TARGET_DIR/usr/local/include/glib-2.0/
	export GLIB_LIBRARY_PATH=$APPLIBS_TARGET_DIR/usr/local/lib/
	export GLIBS='-lglib-2.0 -lintl -lz'
 elif [ $PLATFORM_SOC = "mstar" ]; then 
	export IARM_PATH=$BUILDS_DIR/iarmbus
	CROSS_COMPILE=arm-none-linux-gnueabi
	export CC=$CROSS_COMPILE-gcc
	export CXX=$CROSS_COMPILE-g++
	export GLIBS='-lglib-2.0 -lz'

fi

if [ -f $COMBINED_ROOT/rdklogger/build/lib/librdkloggers.so ]; then
	export RDK_LOGGER_ENABLED='y'
	exit 0;
fi

buildReport=$BUILDS_DIR/../Logs/buildIARMBusreport.txt
make > $buildReport 2>> $buildReport 
if [ $? -ne 0 ] ; then
  echo IarmBus Build Failed
  exit 1
else
  echo IarmBus Build Success
  exit 0
fi
