##############################################################################
# add library
#
#-include OpenCOM$(DIR)mak$(DIR)$(ARCH)$(DIR)Makefile

LIB += OpenCOM.a

GEN += 

LFLAGS +=

OPENCOM_OBJ +=	

GENFILES += OpenCOM$(DIR)gen$(DIR)inc$(DIR)Com_Cfg.h.php

VPATH += OpenCOM$(DIR)src

INCLUDE += 	-IOpenCOM$(DIR)inc

OpenCOM.a : $(OPENCOM_OBJ)
	ar -rcs $(LIBDIR)$(DIR)OpenCOM.a $(foreach obj, $(OPENCOM_OBJ), $(OBJDIR)$(DIR)$(obj))


