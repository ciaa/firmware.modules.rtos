##############################################################################
# add library
#
-include OpenSEK$(DIR)mak$(DIR)$(ARCH)$(DIR)Makefile

LIB += OpenSEK.a

GEN += genosek

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

GENFILES += OpenSEK$(DIR)gen$(DIR)inc$(DIR)Osek_Internal_Cfg.h.php						\
				OpenSEK$(DIR)gen$(DIR)inc$(DIR)Osek_Cfg.h.php									\
				OpenSEK$(DIR)gen$(DIR)src$(DIR)Osek_Cfg.c.php									\
				OpenSEK$(DIR)gen$(DIR)src$(DIR)Osek_Internal_Cfg.c.php 						\
				OpenSEK$(DIR)gen$(DIR)src$(DIR)$(ARCH)$(DIR)Osek_Internal_Arch_Cfg.c.php 	\
				OpenSEK$(DIR)gen$(DIR)inc$(DIR)$(ARCH)$(DIR)Osek_Internal_Arch_Cfg.h.php

VPATH += OpenSEK$(DIR)src					\
			OpenSEK$(DIR)src$(DIR)$(ARCH)			\
			$(GENDIR)$(DIR)src					\
			$(GENDIR)$(DIR)src$(DIR)$(ARCH)

INCLUDE += 	-IOpenSEK$(DIR)inc 										\
				-IOpenSEK$(DIR)inc$(DIR)$(ARCH) 								\
				-IOpenSEK$(DIR)inc$(DIR)$(ARCH)$(DIR)$(DERIVATE)				\
				-I$(GENDIR)$(DIR)inc										\
				-I$(GENDIR)$(DIR)inc$(DIR)$(ARCH)								\
            -I$(GENDIR)$(DIR)inc$(DIR)$(ARCH)$(DIR)$(DERIVATE)

OpenSEK.a : $(OPENOSEK_OBJ)
	ar -rcs $(LIBDIR)$(DIR)OpenSEK.a $(foreach obj, $(OPENOSEK_OBJ), $(OBJDIR)$(DIR)$(obj))

SPLINT +=	OpenSEK$(DIR)src$(DIR)*.c \
				OpenSEK$(DIR)src$(DIR)$(ARCH)*.c \
				OpenSEK$(DIR)src$(DIR)$(ARCH)$(DIR)$(DERIVATE)$(DIR)*.c

genosek:
	mkdir -p $(GENDIR)$(DIR)inc$(DIR)$(ARCH)
	mkdir -p $(GENDIR)$(DIR)src$(DIR)$(ARCH)
	mkdir -p $(GENDIR)$(DIR)mak$(DIR)$(ARCH)
	php OpenSEK$(DIR)gen$(DIR)generator.php --cmdline -l -v -c $(CFGFILES) -f $(GENFILES) -o $(GENDIR)	
