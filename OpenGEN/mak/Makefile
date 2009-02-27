############################################################################### 
#
# Copyright 2008, Mariano Cerdeiro
#
# This file is part of OpenSEK.
#
# OpenSEK is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# OpenSEK is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with OpenSEK. If not, see <http://www.gnu.org/licenses/>.
#
###############################################################################

###############################################################################
# includes
-include OpenGEN$(DIR)mak$(DIR)$(ARCH)$(DIR)Makefile
-include $(GENDIR)$(DIR)mak$(DIR)Make_OpenGEN.mak

###############################################################################
# definitions
LIB += OpenGEN.a

GEN += OpenGENgen

LFLAGS +=

OpenGEN_OBJ +=

GENFILES += OpenGEN$(DIR)gen$(DIR)mak$(DIR)Make_OpenGEN.mak.php		\
				OpenGEN$(DIR)gen$(DIR)inc$(DIR)MemMap_Arch_Cfg.h.php

VPATH += OpenGEN$(DIR)src	\
			OpenGEN$(DIR)src$(DIR)$(ARCH)

INCLUDE +=	-IOpenGEN$(DIR)inc													\
				-IOpenGEN$(DIR)inc$(DIR)$(ARCH)									\
				-IOpenGEN$(DIR)inc$(DIR)$(ARCH)$(DIR)$(CPUTYPE)			\
				-IOpenGEN$(DIR)inc$(DIR)compilers$(DIR)$(COMPILER)			\
				-I$(GENDIR)$(DIR)inc

SPLINT +=

###############################################################################
# rules
OpenGEN.a : $(OpenGEN_OBJ)
	ar -rcs $(LIBDIR)$(DIR)OpenGEN.a $(foreach obj, $(OpenGEN_OBJ), $(OBJDIR)$(DIR)$(obj))
# generation rule #
OpenGENgen:
	mkdir -p $(GENDIR)$(DIR)inc$(DIR)$(ARCH)
	mkdir -p $(GENDIR)$(DIR)src$(DIR)$(ARCH)
	mkdir -p $(GENDIR)$(DIR)mak$(DIR)$(ARCH)
	php OpenGEN$(DIR)gen$(DIR)generator.php --cmdline -l -v -c $(CFGFILES) -f $(GENFILES) -o $(GENDIR)	

