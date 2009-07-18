-include OpenDRV$(DIR)Pwm$(DIR)mak$(DIR)$(ARCH)$(DIR)Makefile

OPENDRV_PWM_OBJ +=		Pwm_Init.o														\
								Pwm_Init_Arch.o												\
								Pwm_SetDutyCycle.o

INCLUDE += 	-IOpenDRV$(DIR)Pwm$(DIR)inc											\
				-IOpenDRV$(DIR)Pwm$(DIR)inc$(DIR)$(ARCH)							\
				-IOpenDRV$(DIR)Pwm$(DIR)inc$(DIR)$(ARCH)$(DIR)$(CPUTYPE)

LIB += OpenDRV_Pwm.a

VPATH += OpenDRV$(DIR)Pwm$(DIR)src												\
			OpenDRV$(DIR)Pwm$(DIR)src$(DIR)$(ARCH)								\
			OpenDRV$(DIR)Pwm$(DIR)src$(DIR)$(ARCH)$(DIR)$(CPUTYPE)

GENFILES += OpenDRV$(DIR)Pwm$(DIR)gen$(DIR)inc$(DIR)Pwm_Cfg.h.php		\
				OpenDRV$(DIR)Pwm$(DIR)gen$(DIR)inc$(DIR)$(ARCH)$(DIR)$(CPUTYPE)$(DIR)Pwm_Arch_Cfg.h.php				\
				OpenDRV$(DIR)Pwm$(DIR)gen$(DIR)inc$(DIR)$(ARCH)$(DIR)$(CPUTYPE)$(DIR)Pwm_Internal_Arch_Cfg.h.php

OpenDRV_Pwm.a : $(OPENDRV_PWM_OBJ)
	$(AR) -rcs $(LIBDIR)$(DIR)OpenDRV_Pwm.a $(foreach obj, $(OPENDRV_PWM_OBJ), $(OBJDIR)$(DIR)$(obj))
