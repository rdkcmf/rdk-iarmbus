# ============================================================================
# RDK MANAGEMENT, LLC CONFIDENTIAL AND PROPRIETARY
# ============================================================================
# This file (and its contents) are the intellectual property of RDK Management, LLC.
# It may not be used, copied, distributed or otherwise  disclosed in whole or in
# part without the express written permission of RDK Management, LLC.
# ============================================================================
# Copyright (c) 2014 RDK Management, LLC. All rights reserved.
# ============================================================================

SUBDIRS =
DIST_SUBDIRS =

SOLIBLDFLAGS = -ldbus-1 -lglib-2.0

INCLUDE_FILES = -I=$(includedir)/directfb \
                -I=$(includedir)/glib-2.0 \
                -I=$(libdir)/glib-2.0/include \
                -I$(abs_top_srcdir)/core/include \
                -I=$(includedir)/dbus-1.0 \
                -I=$(libdir)/dbus-1.0/include

CC = $(CXX)

AM_CPPFLAGS = $(INCLUDE_FILES)

lib_LTLIBRARIES = libIARMBus.la
libIARMBus_la_SOURCES = libIARM-dbus.c libIBus-dbus.c libIBusDaemon-dbus.c
libIARMBus_la_CFLAGS = -D_USE_DBUS $(INCLUDE_FILES)

libIARMBus_la_LDFLAGS = $(SOLIBLDFLAGS)


bin_PROGRAMS = IARMDaemonMain

IARMDaemonMain_SOURCES = IARMDaemonMain-dbus.c
IARMDaemonMain_CFLAGS = $(INCLUDE_FILES)
IARMDaemonMain_LDADD = -L. -lIARMBus -lpthread -lglib-2.0 -ldbus-1
IARMDaemonMain_DEPENDENCIES = libIARMBus.la
