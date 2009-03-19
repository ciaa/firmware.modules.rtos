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

# GCC ARM tools chains #
CC = arm-gcc
LD = arm-ld
AR = arm-ar
AS = arm-as
GDB = arm-gdb
NM = arm-nm

# debug options #
GDBO += -x OpenGEN$(DIR)mak$(DIR)$(ARCH)$(DIR)$(COMPILER)$(DIR)debug.scr

# compiler options for ARM with GCC Compiler #
#CFLAGS += -c -Wall
CFLAGS += -c -fno-common -O3 -g
LFLAGS += $(LINKSCRIPT) -Map $(BINDIR)$(DIR)$(BIN).map
AFLAGS += -mapcs-32
