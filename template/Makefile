# ============================================================================
# RDK MANAGEMENT, LLC CONFIDENTIAL AND PROPRIETARY
# ============================================================================
# This file (and its contents) are the intellectual property of RDK Management, LLC.
# It may not be used, copied, distributed or otherwise  disclosed in whole or in
# part without the express written permission of RDK Management, LLC.
# ============================================================================
# Copyright (c) 2014 RDK Management, LLC. All rights reserved.
# ============================================================================
RM          := rm -rf 
CFLAGS      := -g -fPIC -D_REENTRANT -Wall
ifeq ($(USE_DBUS),y)
EXECUTABLE  := $(patsubst %.c,%,$(wildcard *Main*.c))
else
EXECUTABLE  := $(patsubst %.c,%,$(wildcard *Main.c))
endif
OBJS        := $(patsubst %.c,%.o,$(wildcard *.c))

INCLUDE     :=	-I.\
		-I./include	\
		-I$(IARM_PATH)/core/                      \
		-I$(IARM_PATH)/core/include                        \
		-I$(DFB_ROOT)/usr/local/include/directfb 

		

CFLAGS      += $(INCLUDE)

LDFLAGS=-L$(IARM_PATH)/core/
LDFLAGS+=-L$(DFB_LIB) -L$(OPENSOURCE_BASE)/lib
ifeq ($(USE_DBUS),y)
FUSION_LIBS=-ldirect -lfusion  -lpthread
LDFLAGS += -ldbus-1 
else
CFLAGS      += -I$(FUSION_PATH)/src -I$(FUSION_PATH)/include
FUSION_LIBS=-ldirect -lfusiondale -lfusion  -lpthread
endif
LDFLAGS += $(FUSION_LIBS) 
LDFLAGS+=-L$(GLIB_LIBRARY_PATH)/
LDFLAGS+=$(GLIBS)
LDFLAGS += -lIARMBus 

all: clean executable
	@echo "Build Finished...."

executable: $(OBJS)
	@echo "Creating Final Executable ..$(EXECUTABLE) "
	$(CXX) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(EXECUTABLE)

%.o: %.c
	@echo "Building $@ ...."
	$(CXX) -c $<  $(CFLAGS) -o $@

clean:
	@echo "Cleaning the directory..."
	@$(RM) $(OBJS) $(LIBNAMEFULL)
