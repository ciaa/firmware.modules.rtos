-include FreeOSEK$(DIR)Drv$(DIR)Pwm$(DIR)mak$(DIR)$(ARCH)$(DIR)Makefile

DRV_PWM_OBJ +=	Pwm_Init.o														\
					Pwm_Init_Arch.o												\
					Pwm_SetDutyCycle.o

INCLUDE += 	-IFreeOSEK$(DIR)Drv$(DIR)Pwm$(DIR)inc											\
				-IFreeOSEK$(DIR)Drv$(DIR)Pwm$(DIR)inc$(DIR)$(ARCH)							\
				-IFreeOSEK$(DIR)Drv$(DIR)Pwm$(DIR)inc$(DIR)$(ARCH)$(DIR)$(CPUTYPE)

LIB += Drv_Pwm.a

VPATH += FreeOSEK$(DIR)Drv$(DIR)Pwm$(DIR)src												\
			FreeOSEK$(DIR)Drv$(DIR)Pwm$(DIR)src$(DIR)$(ARCH)							\
			FreeOSEK$(DIR)Drv$(DIR)Pwm$(DIR)src$(DIR)$(ARCH)$(DIR)$(CPUTYPE)

GENFILES += FreeOSEK$(DIR)Drv$(DIR)Pwm$(DIR)gen$(DIR)inc$(DIR)Pwm_Cfg.h.php															\
				FreeOSEK$(DIR)Drv$(DIR)Pwm$(DIR)gen$(DIR)inc$(DIR)$(ARCH)$(DIR)$(CPUTYPE)$(DIR)Pwm_Arch_Cfg.h.php				\
				FreeOSEK$(DIR)Drv$(DIR)Pwm$(DIR)gen$(DIR)inc$(DIR)$(ARCH)$(DIR)$(CPUTYPE)$(DIR)Pwm_Internal_Arch_Cfg.h.php

Drv_Pwm.a : $(DRV_PWM_OBJ)
	$(AR) -rcs $(LIBDIR)$(DIR)Drv_Pwm.a $(foreach obj, $(DRV_PWM_OBJ), $(OBJDIR)$(DIR)$(obj))
