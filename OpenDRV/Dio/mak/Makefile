-include OpenDRV$(DIR)Dio$(DIR)mak$(DIR)$(ARCH)$(DIR)Makefile

OPENDRV_DIO_OBJ +=		Dio_Init.o														\
								Dio_ReadChannel.o												\
								Dio_WriteChannel.o											\
								Dio_Init_Arch.o

INCLUDE += 	-IOpenDRV$(DIR)Dio$(DIR)inc											\
				-IOpenDRV$(DIR)Dio$(DIR)inc$(DIR)$(ARCH)							\
				-IOpenDRV$(DIR)Dio$(DIR)inc$(DIR)$(ARCH)$(DIR)$(DERIVATE)

LIB += OpenDRV_Dio.a

VPATH += OpenDRV$(DIR)Dio$(DIR)src												\
			OpenDRV$(DIR)Dio$(DIR)src$(DIR)$(ARCH)								\
			OpenDRV$(DIR)Dio$(DIR)src$(DIR)$(ARCH)$(DIR)$(DERIVATE)

GENFILES += OpenDRV$(DIR)Dio$(DIR)gen$(DIR)inc$(DIR)Dio_Cfg.h.php

OpenDRV_Dio.a : $(OPENDRV_DIO_OBJ)
	$(AR) -rcs $(LIBDIR)$(DIR)OpenDRV_Dio.a $(foreach obj, $(OPENDRV_DIO_OBJ), $(OBJDIR)$(DIR)$(obj))
