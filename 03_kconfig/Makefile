###########################################################################
# Makefile
# The Top Makefile of 03_kconfig project
#
# $Copyright: Copyright (C) village
############################################################################
-include .config

#######################################
# silence build
#######################################
ifeq ($(CONFIG_VERBOSE_MODE), y)
  Q = 
else
  Q = @
endif

export Q

#######################################
# menuconfig
#######################################
Scripts      := ./scripts
Kconfig      := ./Kconfig

menuconfig: $(Scripts)/kconfig/mconf
	$(Q)$< $(Kconfig)

silentoldconfig: $(Scripts)/kconfig/conf
	$(Q)mkdir -p include/config include/generated
	$(Q)$< -s --$@ $(Kconfig)

$(Scripts)/kconfig/mconf:
	$(Q)$(MAKE) -C $(Scripts)/kconfig HOST_CC=gcc-13

$(Scripts)/kconfig/conf:
	$(Q)$(MAKE) -C $(Scripts)/kconfig HOST_CC=gcc-13

#######################################
# clean up
#######################################
clean:
	$(Q)$(MAKE) -C $(Scripts)/kconfig clean
