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

INCLUDE     :=	-I.\
		-I./include	\
		-I$(IARM_PATH)/core/                            \
		-I$(IARM_PATH)/core/include                      \
		-I$(IARM_PATH)/template/include                 \
		-I$(DFB_ROOT)/usr/local/include/directfb 

CFLAGS      += $(INCLUDE)


LDFLAGS=-L$(IARM_PATH)/core/
LDFLAGS+=-L$(DFB_LIB) -L$(OPENSOURCE_BASE)/lib
ifeq ($(USE_DBUS),y)
FUSION_LIBS=-ldirect -lfusion -lpthread
LDFLAGS += -ldbus-1
else
CFLAGS      += -I$(FUSION_PATH)/src -I$(FUSION_PATH)/include
FUSION_LIBS=-ldirect -lfusiondale -lfusion  -lpthread
endif
LDFLAGS += $(FUSION_LIBS)
LDFLAGS+=-L$(GLIB_LIBRARY_PATH)/
LDFLAGS+=$(GLIBS)

LDFLAGS += -lIARMBus 

.PHONY: $(BINARIES)

BINARIES    := $(patsubst %.c,%,$(wildcard *.c))

all: clean $(BINARIES)  
	@echo "Build Finished...."

$(BINARIES):
	@echo "Building $@ ...."
	$(CXX) $(CFLAGS) $@.c -o $@ $(LDFLAGS)
	
clean:
	@echo "Cleaning the directory..."
	@$(RM) $(BINARIES)



