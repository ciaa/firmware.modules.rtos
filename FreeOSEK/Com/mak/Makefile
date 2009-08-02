##############################################################################
# add library
#
#-include OpenCOM$(DIR)mak$(DIR)$(ARCH)$(DIR)Makefile

LIB += Com.a

GEN += 

LFLAGS +=

COM_OBJ +=	GetCOMApplicationMode.o		\
				GetMessageStatus.o			\
				InitMessage.o					\
				ReceiveDynamicMessage.o		\
				ReceiveMessage.o				\
				SendDynamicMessage.o			\
				SendMessage.o					\
				SendZeroMessage.o				\
				StartCOM.o						\
				StartPeriodic.o				\
				StopCOM.o						\
				StopPeriodic.o					\
				Com.o								\
				Com_Cfg.o						\
				Com_Internal_Cfg.o

GENFILES += FreeOSEK$(DIR)Com$(DIR)gen$(DIR)inc$(DIR)Com_Cfg.h.php				\
				FreeOSEK$(DIR)Com$(DIR)gen$(DIR)src$(DIR)Com_Cfg.c.php				\
				FreeOSEK$(DIR)Com$(DIR)gen$(DIR)inc$(DIR)Com_Internal_Cfg.h.php	\
				FreeOSEK$(DIR)Com$(DIR)gen$(DIR)src$(DIR)Com_Internal_Cfg.c.php

VPATH += FreeOSEK$(DIR)Com$(DIR)src				\
			$(GENDIR)$(DIR)src						\
			$(GENDIR)$(DIR)src$(DIR)$(ARCH)

INCLUDE += 	-IFreeOSEK$(DIR)Com$(DIR)inc

Com.a : $(COM_OBJ)
	@echo
	@echo create Com library
	ar -rcs $(LIBDIR)$(DIR)Com.a $(foreach obj, $(COM_OBJ), $(OBJDIR)$(DIR)$(obj))


