###########################################################################
# Makefile
# The Makefile of x86bios boot
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
LDSCRIPT-BOOT  := -T boot.lds


#######################################
# compiler flags
#######################################
# boot loader ld flags
LDFLAGS       += $(LDSCRIPT-BOOT) -ffreestanding -nostdlib
LDFLAGS       += -Wl,--no-warn-rwx-segment
LDFLAGS       += -Wl,-m,elf_i386


#######################################
# build task
#######################################
all:
	i686-elf-gcc -x assembler-with-cpp -c $(ASFLAGS) boot.s -o boot.o
	i686-elf-gcc $(LDFLAGS) boot.o -o village-boot.elf
	i686-elf-objcopy -O binary -S village-boot.elf village-boot.bin

clean:
	rm *.o *.elf *.bin
