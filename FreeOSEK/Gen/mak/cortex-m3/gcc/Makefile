############################################################################### 
#
# Copyright 2008, Mariano Cerdeiro
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

COMPILER_PREFFIX=arm-none-eabi-

# GCC ARM tools chains #
CC = $(COMPILER_PREFFIX)gcc
LD = $(COMPILER_PREFFIX)ld
AR = $(COMPILER_PREFFIX)ar
AS = $(COMPILER_PREFFIX)as
GDB = $(COMPILER_PREFFIX)gdb
NM = $(COMPILER_PREFFIX)nm

# debug options #
GDBO += -x FreeOSEK$(DIR)Gen$(DIR)mak$(DIR)$(ARCH)$(DIR)$(COMPILER)$(DIR)debug.scr

# compiler options for ARM with GCC Compiler #
#CFLAGS += -c -Wall
CFLAGS += -c -fno-common -O3 -g -fno-builtin
LFLAGS += $(LINKSCRIPT) -Map $(BINDIR)$(DIR)$(BIN).map
AFLAGS += -mapcs-32 -mfpu=softfpa
