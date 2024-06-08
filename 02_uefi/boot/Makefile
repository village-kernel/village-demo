###########################################################################
# Makefile
# The Makefile of uefi boot
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# ASFLAGS
######################################
ASFLAGS += -g -gdwarf-2 -DDEBUG


######################################
# link script
######################################
LDSCRIPT-BOOT  := -T ./uefi/elf_ia32_efi.lds


#######################################
# compiler flags
#######################################
# boot loader c flags
CFLAGS        +=

# boot loader ld flags
LDFLAGS       += $(LDSCRIPT-BOOT) -ffreestanding -nostdlib
LDFLAGS       += -Wl,--no-warn-rwx-segment
LDFLAGS       += -Wl,-m,elf_i386


#######################################
# build task
#######################################
all:


clean:
	rm *.o *.so *.efi *.elf *.bin
