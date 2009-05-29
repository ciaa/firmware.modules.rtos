-include OpenDRV$(DIR)Adc$(DIR)mak$(DIR)$(ARCH)$(DIR)Makefile

OPENDRV_ADC_OBJ +=		Adc_Init.o														\
								Adc_Init_Arch.o												\
								Adc_GetGroupStatus.o											\
								Adc_ReadGroup.o												\
								Adc_StartGroupConversion.o

INCLUDE += 	-IOpenDRV$(DIR)Adc$(DIR)inc											\
				-IOpenDRV$(DIR)Adc$(DIR)inc$(DIR)$(ARCH)							\
				-IOpenDRV$(DIR)Adc$(DIR)inc$(DIR)$(ARCH)$(DIR)$(CPUTYPE)

LIB += OpenDRV_Adc.a

VPATH += OpenDRV$(DIR)Adc$(DIR)src												\
			OpenDRV$(DIR)Adc$(DIR)src$(DIR)$(ARCH)								\
			OpenDRV$(DIR)Adc$(DIR)src$(DIR)$(ARCH)$(DIR)$(CPUTYPE)

GENFILES += OpenDRV$(DIR)Adc$(DIR)gen$(DIR)inc$(DIR)Adc_Cfg.h.php		\
				OpenDRV$(DIR)Adc$(DIR)gen$(DIR)inc$(DIR)$(ARCH)$(DIR)$(CPUTYPE)$(DIR)Adc_Arch_Cfg.h.php				\
				OpenDRV$(DIR)Adc$(DIR)gen$(DIR)inc$(DIR)$(ARCH)$(DIR)$(CPUTYPE)$(DIR)Adc_Internal_Arch_Cfg.h.php

OpenDRV_Adc.a : $(OPENDRV_ADC_OBJ)
	$(AR) -rcs $(LIBDIR)$(DIR)OpenDRV_Adc.a $(foreach obj, $(OPENDRV_ADC_OBJ), $(OBJDIR)$(DIR)$(obj))
