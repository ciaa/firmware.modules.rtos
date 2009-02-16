-include OpenDRV$(DIR)Mcu$(DIR)mak$(DIR)$(ARCH)$(DIR)Makefile

OPENDRV_MCU_OBJ +=	Mcu_Init.o														\
							Mcu_InitClock.o												\
							Mcu_Init_Arch.o												\
							Mcu_InitClock_Arch.o

INCLUDE += 	-IOpenDRV$(DIR)Mcu$(DIR)inc											\
				-IOpenDRV$(DIR)Mcu$(DIR)inc$(DIR)$(ARCH)							\
				-IOpenDRV$(DIR)Mcu$(DIR)inc$(DIR)$(ARCH)$(DIR)$(DERIVATE)

LIB += OpenDRV_Mcu.a

VPATH += OpenDRV$(DIR)Mcu$(DIR)src												\
			OpenDRV$(DIR)Mcu$(DIR)src$(DIR)$(ARCH)								\
			OpenDRV$(DIR)Mcu$(DIR)src$(DIR)$(ARCH)$(DIR)$(DERIVATE)

GENFILES += OpenDRV$(DIR)Mcu$(DIR)gen$(DIR)inc$(DIR)Mcu_Cfg.h.php

OpenDRV_Mcu.a : $(OPENDRV_MCU_OBJ)
	$(AR) -rcs $(LIBDIR)$(DIR)OpenDRV_Mcu.a $(foreach obj, $(OPENDRV_MCU_OBJ), $(OBJDIR)$(DIR)$(obj))
