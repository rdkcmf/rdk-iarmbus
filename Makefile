# ============================================================================
# RDK MANAGEMENT, LLC CONFIDENTIAL AND PROPRIETARY
# ============================================================================
# This file (and its contents) are the intellectual property of RDK Management, LLC.
# It may not be used, copied, distributed or otherwise  disclosed in whole or in
# part without the express written permission of RDK Management, LLC.
# ============================================================================
# Copyright (c) 2014 RDK Management, LLC. All rights reserved.
# ============================================================================
# List of Libraries
lib_core := core/
install_dir := ./install
install_bin_dir := ./install/bin

exe_template        := template/
exe_test            := test/
exe_iarm_daemon     := core/IARMDaemonMain

# List of Executable
libraries := $(lib_core)
executable := $(exe_template) $(exe_test) 

.PHONY: clean all $(libraries) install

all: clean $(libraries) $(executable) install

$(libraries) $(executable):
	$(MAKE) -C $@

$(executable): $(libraries)

install:
	echo "Creating directory.."
	mkdir -p $(install_dir)
	mkdir -p $(install_bin_dir)
	echo "Copying files now..from $(lib_core) to $(install_dir)"
	cp $(lib_core)/*.so $(install_dir)
	echo "Copying files now..from $(exe_iarm_daemon) to $(install_bin_dir)"
	cp $(exe_iarm_daemon) $(install_bin_dir)
	mkdir -p $(FSROOT)/usr/local/lib
	cp $(lib_core)/*.so $(FSROOT)/usr/local/lib
clean:
	rm -rf $(install_dir) 

