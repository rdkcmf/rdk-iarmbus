# ============================================================================
# RDK MANAGEMENT, LLC CONFIDENTIAL AND PROPRIETARY
# ============================================================================
# This file (and its contents) are the intellectual property of RDK Management, LLC.
# It may not be used, copied, distributed or otherwise  disclosed in whole or in
# part without the express written permission of RDK Management, LLC.
# ============================================================================
# Copyright (c) 2014 RDK Management, LLC. All rights reserved.
# ============================================================================
SUBDIRS = core
DIST_SUBDIRS = core

IPK_GEN_PATH = $(abs_top_builddir)/ipk
IPK_GEN_STAGING_DIR=$(abs_top_builddir)/staging_dir
IPK_GEN_INPUT  = debian-binary control.tar.gz data.tar.gz
IPK_GEN_OUTPUT = iarmbus.ipk

package_ipk:
	@echo "Generating IPK Package"
	$(MAKE) prefix=${abs_top_builddir}/staging_dir install
	$(mkdir_p) $(IPK_GEN_STAGING_DIR)/usr/lib
	$(mkdir_p) $(IPK_GEN_STAGING_DIR)/usr/bin
	$(mkdir_p) $(IPK_GEN_STAGING_DIR)/lib/systemd/system/
	cp -af ./conf/iarmbusd.service  $(IPK_GEN_STAGING_DIR)/lib/systemd/system/
	cp -af $(IPK_GEN_STAGING_DIR)/lib/*.so* $(IPK_GEN_STAGING_DIR)/usr/lib/
	cp -af $(IPK_GEN_STAGING_DIR)/bin/* $(IPK_GEN_STAGING_DIR)/usr/bin/
	rm -rf $(IPK_GEN_STAGING_DIR)/lib/libIARMBus*
	tar -czvf $(IPK_GEN_PATH)/data.tar.gz -C $(IPK_GEN_STAGING_DIR) usr lib
	tar -czvf $(IPK_GEN_PATH)/control.tar.gz -C $(IPK_GEN_PATH) control postinst prerm
	cd $(IPK_GEN_PATH) && ar cr $(IPK_GEN_OUTPUT) $(IPK_GEN_INPUT) && cd -
	rm -rf $(IPK_GEN_PATH)/data.tar.gz
	rm -rf $(IPK_GEN_PATH)/control.tar.gz
	rm -rf $(IPK_GEN_STAGING_DIR)
