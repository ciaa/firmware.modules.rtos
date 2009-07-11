##############################################################################
# add library
#
#-include OpenCOM$(DIR)mak$(DIR)$(ARCH)$(DIR)Makefile

LIB += OpenCOM.a

GEN += 

LFLAGS +=

OPENCOM_OBJ +=	ReceiveMessage.o		\
					SendMessage.o			\
					Com_Cfg.o				\
					Com_Internal_Cfg.o

GENFILES += OpenCOM$(DIR)gen$(DIR)inc$(DIR)Com_Cfg.h.php    		\
				OpenCOM$(DIR)gen$(DIR)inc$(DIR)Com_Internal_Cfg.h.php \
				OpenCOM$(DIR)gen$(DIR)src$(DIR)Com_Cfg.c.php				\
				OpenCOM$(DIR)gen$(DIR)src$(DIR)Com_Internal_Cfg.c.php

VPATH += OpenCOM$(DIR)src						\
			$(GENDIR)$(DIR)src					\
			$(GENDIR)$(DIR)src$(DIR)$(ARCH)

INCLUDE += 	-IOpenCOM$(DIR)inc

OpenCOM.a : $(OPENCOM_OBJ)
	ar -rcs $(LIBDIR)$(DIR)OpenCOM.a $(foreach obj, $(OPENCOM_OBJ), $(OBJDIR)$(DIR)$(obj))


