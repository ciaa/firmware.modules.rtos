-include FreeOSEK$(DIR)Drv$(DIR)Adc$(DIR)mak$(DIR)$(ARCH)$(DIR)Makefile

DRV_ADC_OBJ +=	Adc_Init.o														\
					Adc_Init_Arch.o												\
					Adc_GetGroupStatus.o											\
					Adc_ReadGroup.o												\
					Adc_StartGroupConversion.o

INCLUDE += 	-IFreeOSEK$(DIR)Drv$(DIR)Adc$(DIR)inc											\
				-IFreeOSEK$(DIR)Drv$(DIR)Adc$(DIR)inc$(DIR)$(ARCH)							\
				-IFreeOSEK$(DIR)Drv$(DIR)Adc$(DIR)inc$(DIR)$(ARCH)$(DIR)$(CPUTYPE)

LIB += Drv_Adc.a

VPATH += FreeOSEK$(DIR)Drv$(DIR)Adc$(DIR)src													\
			FreeOSEK$(DIR)Drv$(DIR)Adc$(DIR)src$(DIR)$(ARCH)								\
			FreeOSEK$(DIR)Drv$(DIR)Adc$(DIR)src$(DIR)$(ARCH)$(DIR)$(CPUTYPE)

GENFILES += FreeOSEK$(DIR)Drv$(DIR)Adc$(DIR)gen$(DIR)inc$(DIR)Adc_Cfg.h.php		\
				FreeOSEK$(DIR)Drv$(DIR)Adc$(DIR)gen$(DIR)inc$(DIR)$(ARCH)$(DIR)$(CPUTYPE)$(DIR)Adc_Arch_Cfg.h.php				\
				FreeOSEK$(DIR)Drv$(DIR)Adc$(DIR)gen$(DIR)inc$(DIR)$(ARCH)$(DIR)$(CPUTYPE)$(DIR)Adc_Internal_Arch_Cfg.h.php

Drv_Adc.a : $(DRV_ADC_OBJ)
	$(AR) -rcs $(LIBDIR)$(DIR)Drv_Adc.a $(foreach obj, $(DRV_ADC_OBJ), $(OBJDIR)$(DIR)$(obj))
