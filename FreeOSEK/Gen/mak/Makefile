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
-include FreeOSEK$(DIR)Gen$(DIR)mak$(DIR)$(ARCH)$(DIR)Makefile
-include $(GENDIR)$(DIR)mak$(DIR)Make_Gen.mak

###############################################################################
# definitions
LIB += Gen.a

GEN += Gengen

LFLAGS +=

GEN_OBJ +=

GENFILES += FreeOSEK$(DIR)Gen$(DIR)gen$(DIR)mak$(DIR)Make_Gen.mak.php			\
				FreeOSEK$(DIR)Gen$(DIR)gen$(DIR)inc$(DIR)MemMap_Arch_Cfg.h.php

VPATH += FreeOSEK$(DIR)Gen$(DIR)src	\
			FreeOSEK$(DIR)Gen$(DIR)src$(DIR)$(ARCH)

INCLUDE +=	-IFreeOSEK$(DIR)Gen$(DIR)inc													\
				-IFreeOSEK$(DIR)Gen$(DIR)inc$(DIR)$(ARCH)									\
				-IFreeOSEK$(DIR)Gen$(DIR)inc$(DIR)$(ARCH)$(DIR)$(CPUTYPE)			\
				-IFreeOSEK$(DIR)Gen$(DIR)inc$(DIR)compilers$(DIR)$(COMPILER)		\
				-I$(GENDIR)$(DIR)inc

SPLINT +=

###############################################################################
# rules
Gen.a : $(GEN_OBJ)
	ar -rcs $(LIBDIR)$(DIR)Gen.a $(foreach obj, $(GEN_OBJ), $(OBJDIR)$(DIR)$(obj))
# generation rule #
Gengen:
	php FreeOSEK$(DIR)Gen$(DIR)gen$(DIR)generator.php --cmdline -l -v -c $(CFGFILES) -f $(GENFILES) -o $(GENDIR)	

