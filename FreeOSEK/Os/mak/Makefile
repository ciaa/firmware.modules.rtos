##############################################################################
# add library
#
-include FreeOSEK$(DIR)Os$(DIR)mak$(DIR)$(ARCH)$(DIR)Makefile

LIB += Os.a

GEN += 

LFLAGS +=

OS_OBJ +=	ActivateTask.o							\
				CancelAlarm.o							\
				ClearEvent.o							\
				GetEvent.o								\
				GetTaskID.o								\
				GetTaskState.o							\
				TerminateTask.o						\
				ChainTask.o								\
				ReleaseResource.o						\
				SetEvent.o								\
				SetRelAlarm.o							\
				SetAbsAlarm.o							\
				StartOS.o								\
				Schedule.o								\
				ShutdownOS.o							\
				WaitEvent.o								\
				GetAlarmBase.o							\
				GetAlarm.o								\
				GetActiveApplicationMode.o			\
				GetResource.o							\
															\
				StartOs_Arch.o							\
				Os.o										\
				Os_Arch.o								\
															\
				Os_Internal.o							\
				Os_Internal_Arch.o					\
															\
				Os_Cfg.o									\
				Os_Internal_Cfg.o						\
				Os_Internal_Arch_Cfg.o

GENFILES += FreeOSEK$(DIR)Os$(DIR)gen$(DIR)inc$(DIR)Os_Internal_Cfg.h.php							\
				FreeOSEK$(DIR)Os$(DIR)gen$(DIR)inc$(DIR)Os_Cfg.h.php										\
				FreeOSEK$(DIR)Os$(DIR)gen$(DIR)src$(DIR)Os_Cfg.c.php										\
				FreeOSEK$(DIR)Os$(DIR)gen$(DIR)src$(DIR)Os_Internal_Cfg.c.php 							\
				FreeOSEK$(DIR)Os$(DIR)gen$(DIR)src$(DIR)$(ARCH)$(DIR)Os_Internal_Arch_Cfg.c.php 	\
				FreeOSEK$(DIR)Os$(DIR)gen$(DIR)inc$(DIR)$(ARCH)$(DIR)Os_Internal_Arch_Cfg.h.php

VPATH += FreeOSEK$(DIR)Os$(DIR)src						\
			FreeOSEK$(DIR)Os$(DIR)src$(DIR)$(ARCH)		\
			$(GENDIR)$(DIR)src								\
			$(GENDIR)$(DIR)src$(DIR)$(ARCH)

INCLUDE += 	-IFreeOSEK$(DIR)Os$(DIR)inc 												\
				-IFreeOSEK$(DIR)Os$(DIR)inc$(DIR)$(ARCH) 								\
				-IFreeOSEK$(DIR)Os$(DIR)inc$(DIR)$(ARCH)$(DIR)$(CPUTYPE)			\
				-I$(GENDIR)$(DIR)inc															\
				-I$(GENDIR)$(DIR)inc$(DIR)$(ARCH)										\
            -I$(GENDIR)$(DIR)inc$(DIR)$(ARCH)$(DIR)$(CPUTYPE)

Os.a : $(OS_OBJ)
	@echo
	@echo create OS library
	ar -rcs $(LIBDIR)$(DIR)Os.a $(foreach obj, $(OS_OBJ), $(OBJDIR)$(DIR)$(obj))

SPLINT +=	FreeOSEK$(DIR)Os$(DIR)src$(DIR)*.c											\
				FreeOSEK$(DIR)Os$(DIR)src$(DIR)$(ARCH)*.c									\
				FreeOSEK$(DIR)Os$(DIR)src$(DIR)$(ARCH)$(DIR)$(CPUTYPE)$(DIR)*.c

