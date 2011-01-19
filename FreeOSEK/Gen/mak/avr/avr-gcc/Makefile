############################################################################### 
#
# Copyright 2008, 2011, Mariano Cerdeiro
#
# This file is part of FreeOSEK.
#
# FreeOSEK is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# FreeOSEK is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with FreeOSEK. If not, see <http://www.gnu.org/licenses/>.
#
###############################################################################

###############################################################################
# includes

##############################################################################
# definitions

# GCC ARM tools chains #
CC = avr-gcc
LD = avr-gcc
AR = avr-ar
AS = avr-as
GDB = avr-gdb
NM = avr-nm

# debug options #
GDBO += -x FreeOSEK$(DIR)Gen$(DIR)mak$(DIR)$(ARCH)$(DIR)$(COMPILER)$(DIR)debug.scr

# compiler options for ARM with GCC Compiler #
#CFLAGS += -c -Wall
CFLAGS += -mmcu=$(CPU) -Wall -gdwarf-2 -Os -std=gnu99 -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -MD -MP -MT -c

LFLAGS += $(LINKSCRIPT) -mmcu=at90can128
AFLAGS += -mapcs-32 -mfpu=softfpa

%.o : %.c
	@ echo
	@ echo Compiling $<
	$(CC) $(CFLAGS) -o $(OBJDIR)$(DIR)$@ -c $<

%.o : %.s
	@ echo
	@ echo Assembling $<
	$(AS) $(AFLAGS) -o $(OBJDIR)$(DIR)$@ -c $<