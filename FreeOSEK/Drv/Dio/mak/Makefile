-include FreeOSEK$(DIR)Drv$(DIR)Dio$(DIR)mak$(DIR)$(ARCH)$(DIR)Makefile

DRV_DIO_OBJ +=	Dio_Init.o														\
				Dio_ReadChannel.o												\
				Dio_WriteChannel.o											\
				Dio_Init_Arch.o

INCLUDE += 	-IFreeOSEK$(DIR)Drv$(DIR)Dio$(DIR)inc											\
				-IFreeOSEK$(DIR)Drv$(DIR)Dio$(DIR)inc$(DIR)$(ARCH)							\
				-IFreeOSEK$(DIR)Drv$(DIR)Dio$(DIR)inc$(DIR)$(ARCH)$(DIR)$(CPUTYPE)

LIB += Drv_Dio.a

VPATH += FreeOSEK$(DIR)Drv$(DIR)Dio$(DIR)src												\
			FreeOSEK$(DIR)Drv$(DIR)Dio$(DIR)src$(DIR)$(ARCH)							\
			FreeOSEK$(DIR)Drv$(DIR)Dio$(DIR)src$(DIR)$(ARCH)$(DIR)$(CPUTYPE)

GENFILES += FreeOSEK$(DIR)Drv$(DIR)Dio$(DIR)gen$(DIR)inc$(DIR)Dio_Cfg.h.php															\
				FreeOSEK$(DIR)Drv$(DIR)Dio$(DIR)gen$(DIR)inc$(DIR)$(ARCH)$(DIR)$(CPUTYPE)$(DIR)Dio_Arch_Cfg.h.php				\
				FreeOSEK$(DIR)Drv$(DIR)Dio$(DIR)gen$(DIR)inc$(DIR)$(ARCH)$(DIR)$(CPUTYPE)$(DIR)Dio_Internal_Arch_Cfg.h.php

Drv_Dio.a : $(DRV_DIO_OBJ)
	$(AR) -rcs $(LIBDIR)$(DIR)Drv_Dio.a $(foreach obj, $(DRV_DIO_OBJ), $(OBJDIR)$(DIR)$(obj))
