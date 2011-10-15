############################################################################### 
#
# Copyright 2011, Tamas Kenderes
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

# configuration for using the Yagarto toolchain #
CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
AR = arm-none-eabi-ar
AS = arm-none-eabi-as
GDB = arm-none-eabi-gdb
NM = arm-none-eabi-nm

# debug options #
#GDBO += -x FreeOSEK(DIR)Gen$(DIR)mak$(DIR)$(ARCH)$(DIR)$(CPUTYPE)$(DIR)$(COMPILER)$(DIR)debug.scr

# compiler options for ARM with GCC Compiler #
CFLAGS += -c -Wall -fno-common -O0 -g -fno-builtin
LFLAGS += $(LINKSCRIPT) -Map $(BINDIR)$(DIR)$(BIN).map
AFLAGS += -mapcs-32 -mfpu=softfpa
