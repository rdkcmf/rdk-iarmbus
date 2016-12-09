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

#######################################
#
# Build Framework standard script for
#
# IARMBus component

# use -e to fail on any shell issue
# -e is the requirement from Build Framework
set -ex


# default PATHs - use `man readlink` for more info
# the path to combined build
export RDK_PROJECT_ROOT_PATH=${RDK_PROJECT_ROOT_PATH-`readlink -m ..`}
export COMBINED_ROOT=$RDK_PROJECT_ROOT_PATH

# path to build script (this script)
export RDK_SCRIPTS_PATH=${RDK_SCRIPTS_PATH-`readlink -m $0 | xargs dirname`}

# path to components sources and target
export RDK_SOURCE_PATH=${RDK_SOURCE_PATH-`readlink -m .`}
export RDK_TARGET_PATH=${RDK_TARGET_PATH-$RDK_SOURCE_PATH}

# fsroot and toolchain (valid for all devices)
export RDK_FSROOT_PATH=${RDK_FSROOT_PATH-`readlink -m $RDK_PROJECT_ROOT_PATH/sdk/fsroot/ramdisk`}
export RDK_TOOLCHAIN_PATH=${RDK_TOOLCHAIN_PATH-`readlink -m $RDK_PROJECT_ROOT_PATH/sdk/toolchain/staging_dir`}


# default component name
export RDK_COMPONENT_NAME=${RDK_COMPONENT_NAME-`basename $RDK_SOURCE_PATH`}


# parse arguments
INITIAL_ARGS=$@

function usage()
{
    set +x
    echo "Usage: `basename $0` [-h|--help] [-v|--verbose] [action]"
    echo "    -h    --help                  : this help"
    echo "    -v    --verbose               : verbose output"
    echo "    -p    --platform  =PLATFORM   : specify platform for IARMBus"
    echo
    echo "Supported actions:"
    echo "      configure, clean, build (DEFAULT), rebuild, install"
}

# options may be followed by one colon to indicate they have a required argument
if ! GETOPT=$(getopt -n "build.sh" -o hvp: -l help,verbose,platform: -- "$@")
then
    usage
    exit 1
fi

eval set -- "$GETOPT"

while true; do
  case "$1" in
    -h | --help ) usage; exit 0 ;;
    -v | --verbose ) set -x ;;
    -p | --platform ) CC_PLATFORM="$2" ; shift ;;
    -- ) shift; break;;
    * ) break;;
  esac
  shift
done

ARGS=$@


# component-specific vars
export RDK_PLATFORM_SOC=${RDK_PLATFORM_SOC-broadcom}
export PLATFORM_SOC=$RDK_PLATFORM_SOC
export CC_PLATFORM=${CC_PLATFORM-$RDK_PLATFORM_SOC}
CC_PATH=$RDK_SOURCE_PATH
export FSROOT=${RDK_FSROOT_PATH}
export TOOLCHAIN_DIR=${RDK_TOOLCHAIN_PATH}
export BUILDS_DIR=$RDK_PROJECT_ROOT_PATH



# functional modules

function configure()
{
    true #use this function to perform any pre-build configuration
}

function clean()
{
    true #use this function to provide instructions to clean workspace
}

function build()
{
    CURR_DIR=`pwd`
    cd ${CC_PATH}
    export DS_PATH=$BUILDS_DIR/devicesettings
    export IARM_MGRS=$BUILDS_DIR/iarmmgrs
    if [ $RDK_PLATFORM_SOC = "intel" ]; then
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
    if [ "x$BUILD_CONFIG" = "xhybrid" ];then
        export GLIB_INCLUDE_PATH=$FSROOT/usr/local/include/glib-2.0/
        export GLIB_LIBRARY_PATH=$FSROOT/usr/local/lib/
    else
        export GLIB_INCLUDE_PATH=$CROSS_TOOLCHAIN/include/glib-2.0/
        export GLIB_LIBRARY_PATH=$CROSS_TOOLCHAIN/lib/
    fi
    export GLIB_CONFIG_INCLUDE_PATH=$GLIB_LIBRARY_PATH/glib-2.0/
	export GLIBS='-lglib-2.0 -lz'
    elif [ $RDK_PLATFORM_SOC = "broadcom" ]; then
        echo "building for ${RDK_PLATFORM_DEVICE}..."
        export WORK_DIR=$BUILDS_DIR/work${RDK_PLATFORM_DEVICE^^}
		
		if [ ${RDK_PLATFORM_DEVICE} = "rng150" ];then
			if [ -f $BUILDS_DIR/sdk/scripts/setBcmEnv.sh ]; then
				. $BUILDS_DIR/sdk/scripts/setBcmEnv.sh		
			fi
			if [ -f $BUILDS_DIR/sdk/scripts/setBCMenv.sh ]; then
				. $BUILDS_DIR/sdk/scripts/setBCMenv.sh		
			fi
		else
		        . $BUILDS_DIR/build_scripts/setBCMenv.sh
		fi

        export MFR_PATH=$WORK_DIR/svn/sdk/mfrlib
    	export OPENSOURCE_BASE=$BUILDS_DIR/opensource
        export IARM_PATH=$BUILDS_DIR/iarmbus
    	export FUSION_PATH=$OPENSOURCE_BASE/FusionDale
        export FSROOT=$COMBINED_ROOT/sdk/fsroot/ramdisk
    	CROSS_COMPILE=mipsel-linux
        export CC=$CROSS_COMPILE-gcc
    	export CXX=$CROSS_COMPILE-g++

        export GLIB_INCLUDE_PATH=$FSROOT/usr/local/include/glib-2.0/
        export GLIB_LIBRARY_PATH=$FSROOT/usr/local/lib/
        export GLIB_CONFIG_INCLUDE_PATH=$GLIB_LIBRARY_PATH/glib-2.0/
        export GLIBS='-lglib-2.0 -lintl -lz'
    elif [ $RDK_PLATFORM_SOC = "entropic" ]; then
      export SDK_CONFIG=stb597_V3_xi3
      export BUILD_DIR=$BUILDS_DIR
      source ${BUILD_DIR}/build_scripts/setupSDK.sh

      export FSROOT="${BUILD_DIR}/fsroot"

      export LDFLAGS="-L${GCC_BASE}/lib \
         -L${_TMTGTBUILDROOT}/comps/generated/lib/armgnu_linux_el_cortex-a9 \
         -L${_TMTGTBUILDROOT}/comps/generic_apps/usr/lib \
         -L${FSROOT}/usr/lib -L${FSROOT}/usr/local/lib"


      export OPENSOURCE_BASE="${BUILD_DIR}/opensource"
      export IARM_PATH="${BUILD_DIR}/iarmbus"
      export DFB_LIB="${_TMTGTBUILDROOT}/comps/generic_apps/usr/lib"
      export DFB_ROOT="${_TMTGTBUILDROOT}/comps/generic_apps/usr/include/directfb"
      export FUSION_PATH="${_TMTGTBUILDROOT}/comps/generic_apps/usr/include/fusiondale"
      export GLIB_INCLUDE_PATH="${_TMTGTBUILDROOT}/comps/generic_apps/usr/include/glib-2.0"
      export GLIB_CONFIG_INCLUDE_PATH="${_TMTGTBUILDROOT}/comps/generic_apps/usr/lib/glib-2.0"
      export GLIB_LIBRARY_PATH="${FSROOT}/appfs/lib"
      export GLIBS="-lglib-2.0 -lz"
      export DS_PATH="${BUILD_DIR}/devicesettings"
      export IARM_MGRS="${BUILD_DIR}/iarmmgrs"

      export CFLAGS="-O2 -Wall -fPIC \
         -I${_TMTGTBUILDROOT}/comps/generic_apps/usr/include \
         -I${NXP_BASE_ROOT}/open_source_archive/linux/tools_glibc_${GCC_VERSION}/usr/include \
         -I${_TMTGTBUILDROOT}/comps/generic_apps/usr/include/glib-2.0 \
         -I${_TMTGTBUILDROOT}/comps/generic_apps/usr/lib/glib-2.0/include \
         -I${FSROOT}/usr/local/include/libxml2 \
         -I${FSROOT}/usr/local/include/libsoup-2.4 \
         -I ${DFB_ROOT} -I$FUSION_PATH \
         -I${FSROOT}/usr/local/include/gssdp-1.0"

      export CC="${GCC_PREFIX}-gcc --sysroot ${_TMSYSROOT} $CFLAGS" 
      export CXX="${GCC_PREFIX}-g++ --sysroot ${_TMSYSROOT} $CFLAGS" 
      export LD="${GCC_PREFIX}-ld --sysroot ${_TMSYSROOT}"
   elif [ $RDK_PLATFORM_SOC = "mstar" ]; then
	  CROSS_COMPILE=arm-none-linux-gnueabi
	  export GLIBS='-lglib-2.0 -lz'	  
	  FSROOT=$COMBINED_ROOT/sdk/fsroot
	  export IARM_PATH="`readlink -m .`"
	  export DFB_ROOT=${FSROOT}
	  export GLIB_INCLUDE_PATH="${FSROOT}/usr/include/glib-2.0"
	  export GLIB_CONFIG_INCLUDE_PATH="${FSROOT}/usr/lib/glib-2.0/include"
	  export FUSION_PATH="${FSROOT}/usr/include/fusiondale"
	  export CFLAGS+="-O2 -Wall -fPIC -I./include -I${GLIB_INCLUDE_PATH} -I${GLIB_CONFIG_INCLUDE_PATH} -I${FUSION_PATH} \
         -I${FSROOT}/usr/include \
         -I${FSROOT}/usr/include/directfb \
         -I${FSROOT}/usr/include/libsoup-2.4\
         -I${FSROOT}/usr/include/gssdp-1.0"
	  export LDFLAGS+="-Wl,-rpath,${FSROOT}/vendor/lib/utopia -L${FSROOT}/usr/lib"		
	  export DFB_LIB=${FSROOT}/vendor/lib
	  export OPENSOURCE_BASE=${FSROOT}/usr
	  export CC="$CROSS_COMPILE-gcc $CFLAGS"
	  export CXX="$CROSS_COMPILE-g++ $CFLAGS $LDFLAGS"     
    elif [ $RDK_PLATFORM_SOC = "stm" ]; then
        source $RDK_SCRIPTS_PATH/soc/build/soc_env.sh 
    fi
    if [ -f $COMBINED_ROOT/rdklogger/build/lib/librdkloggers.so ]; then
	  export RDK_LOGGER_ENABLED='y'
    fi

    make

    cd $CURR_DIR

}

function rebuild()
{
    clean
    build
}

function install()
{
    if [ $RDK_PLATFORM_SOC = "entropic" ]; then
       RAMDISK_PATH=$BUILDS_DIR/fsroot
       IARMBUS_PATH=$BUILDS_DIR/iarmbus
    else
       RAMDISK_PATH=${RDK_FSROOT_PATH}
       IARMBUS_PATH=${CC_PATH}
    fi
    IARMBUSUSRLIB_DIR=${RAMDISK_PATH}/usr/local/lib
    CURR_DIR=`pwd`

	RAMDISK_TARGET=${RDK_FSROOT_PATH}/mnt/nfs/env/

    if [ ! -d  $RAMDISK_TARGET ] ; then
       mkdir --parents $RAMDISK_TARGET
    fi

	cd $IARMBUS_PATH

    cp ${IARMBUS_PATH}/core/libIARMBus.so $IARMBUSUSRLIB_DIR
    cp ${IARMBUS_PATH}/core/include/libIBus.h ${RDK_FSROOT_PATH}/usr/include
    cp ${IARMBUS_PATH}/core/include/libIARM.h ${RDK_FSROOT_PATH}/usr/include
    cp $cp -v ${IARMBUS_PATH}/install/bin/IARMDaemonMain ${RDK_FSROOT_PATH}/mnt/nfs/env 

    cd $CURR_DIR
}


# run the logic

#these args are what left untouched after parse_args
HIT=false

for i in "$ARGS"; do
    case $i in
        configure)  HIT=true; configure ;;
        clean)      HIT=true; clean ;;
        build)      HIT=true; build ;;
        rebuild)    HIT=true; rebuild ;;
        install)    HIT=true; install ;;
        *)
            #skip unknown
        ;;
    esac
done

# if not HIT do build by default
if ! $HIT; then
  build
fi
