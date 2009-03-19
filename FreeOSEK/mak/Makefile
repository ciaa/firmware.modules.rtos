##############################################################################
# add library
#
-include FreeOSEK$(DIR)mak$(DIR)$(ARCH)$(DIR)Makefile

LIB += FreeOSEK.a

GEN += 

LFLAGS +=

OPENOSEK_OBJ +=	ActivateTask.o							\
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
						StartOs.o								\
						Schedule.o								\
						ShutdownOs.o							\
						WaitEvent.o								\
						GetAlarmBase.o							\
						GetAlarm.o								\
						GetActiveApplicationMode.o			\
						GetResource.o							\
																	\
						StartOs_Arch.o							\
						Osek.o									\
						Osek_Arch.o								\
																	\
						Osek_Internal.o						\
						Osek_Internal_Arch.o					\
																	\
						Osek_Cfg.o								\
						Osek_Internal_Cfg.o					\
						Osek_Internal_Arch_Cfg.o

GENFILES += FreeOSEK$(DIR)gen$(DIR)inc$(DIR)Osek_Internal_Cfg.h.php						\
				FreeOSEK$(DIR)gen$(DIR)inc$(DIR)Osek_Cfg.h.php									\
				FreeOSEK$(DIR)gen$(DIR)src$(DIR)Osek_Cfg.c.php									\
				FreeOSEK$(DIR)gen$(DIR)src$(DIR)Osek_Internal_Cfg.c.php 						\
				FreeOSEK$(DIR)gen$(DIR)src$(DIR)$(ARCH)$(DIR)Osek_Internal_Arch_Cfg.c.php 	\
				FreeOSEK$(DIR)gen$(DIR)inc$(DIR)$(ARCH)$(DIR)Osek_Internal_Arch_Cfg.h.php

VPATH += FreeOSEK$(DIR)src						\
			FreeOSEK$(DIR)src$(DIR)$(ARCH)		\
			$(GENDIR)$(DIR)src					\
			$(GENDIR)$(DIR)src$(DIR)$(ARCH)

INCLUDE += 	-IFreeOSEK$(DIR)inc 										\
				-IFreeOSEK$(DIR)inc$(DIR)$(ARCH) 								\
				-IFreeOSEK$(DIR)inc$(DIR)$(ARCH)$(DIR)$(CPUTYPE)				\
				-I$(GENDIR)$(DIR)inc										\
				-I$(GENDIR)$(DIR)inc$(DIR)$(ARCH)								\
            -I$(GENDIR)$(DIR)inc$(DIR)$(ARCH)$(DIR)$(CPUTYPE)

FreeOSEK.a : $(OPENOSEK_OBJ)
	ar -rcs $(LIBDIR)$(DIR)FreeOSEK.a $(foreach obj, $(OPENOSEK_OBJ), $(OBJDIR)$(DIR)$(obj))

SPLINT +=	FreeOSEK$(DIR)src$(DIR)*.c \
				FreeOSEK$(DIR)src$(DIR)$(ARCH)*.c \
				FreeOSEK$(DIR)src$(DIR)$(ARCH)$(DIR)$(CPUTYPE)$(DIR)*.c

