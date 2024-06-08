###########################################################################
# Makefile
# The Makefile of app
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# CFLAGS
######################################
CFLAGS    += -g -gdwarf-2 -DDEBUG
CFLAGS    += -Wall -fdata-sections -ffunction-sections -fno-common


######################################
# link script
######################################
LDSCRIPT-BOOT  := -T kernel.lds


#######################################
# compiler flags
#######################################
# app ld flags
LDFLAGS       += $(LDSCRIPT-BOOT) -ffreestanding -nostdlib
LDFLAGS       += -Wl,--gc-sections
LDFLAGS       += -Wl,--no-warn-rwx-segment
LDFLAGS       += -Wl,-m,elf_i386
LDFLAGS       += -Wl,-static -pie


#######################################
# build task
#######################################
all:
	i686-elf-gcc -c $(CFLAGS) crt0.c -o crt0.o
	i686-elf-gcc -c $(CFLAGS) main.c -o main.o
	i686-elf-gcc $(LDFLAGS) crt0.o main.o -o village-kernel.elf
	i686-elf-objcopy -O binary -S village-kernel.elf village-kernel.bin

clean:
	rm *.o *.elf *.bin
