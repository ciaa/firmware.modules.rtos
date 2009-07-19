-include FreeOSEK$(DIR)Drv$(DIR)Mcu$(DIR)mak$(DIR)$(ARCH)$(DIR)Makefile

DRV_MCU_OBJ +=	Mcu_Init.o														\
					Mcu_InitClock.o												\
					Mcu_Init_Arch.o												\
					Mcu_InitClock_Arch.o

INCLUDE += 	-IFreeOSEK$(DIR)Drv$(DIR)Mcu$(DIR)inc											\
				-IFreeOSEK$(DIR)Drv$(DIR)Mcu$(DIR)inc$(DIR)$(ARCH)							\
				-IFreeOSEK$(DIR)Drv$(DIR)Mcu$(DIR)inc$(DIR)$(ARCH)$(DIR)$(CPUTYPE)

LIB += Drv_Mcu.a

VPATH += FreeOSEK$(DIR)Drv$(DIR)Mcu$(DIR)src											\
			FreeOSEK$(DIR)Drv$(DIR)Mcu$(DIR)src$(DIR)$(ARCH)						\
			FreeOSEK$(DIR)Drv$(DIR)Mcu$(DIR)src$(DIR)$(ARCH)$(DIR)$(CPUTYPE)

GENFILES += FreeOSEK$(DIR)Drv$(DIR)Mcu$(DIR)gen$(DIR)inc$(DIR)Mcu_Cfg.h.php

Drv_Mcu.a : $(DRV_MCU_OBJ)
	$(AR) -rcs $(LIBDIR)$(DIR)Drv_Mcu.a $(foreach obj, $(DRV_MCU_OBJ), $(OBJDIR)$(DIR)$(obj))
