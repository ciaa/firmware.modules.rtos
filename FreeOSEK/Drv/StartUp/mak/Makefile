-include FreeOSEK$(DIR)Drv$(DIR)StartUp$(DIR)mak$(DIR)$(ARCH)$(DIR)$(CPUTYPE)$(DIR)Makefile

LIB += Drv_StartUp.a

VPATH += FreeOSEK$(DIR)Drv$(DIR)StartUp$(DIR)src									\
			FreeOSEK$(DIR)Drv$(DIR)StartUp$(DIR)src$(DIR)$(ARCH)$(DIR)$(CPUTYPE)	\

Drv_StartUp.a : $(DRV_STARTUP_OBJ)
	$(AR) -rcs $(LIBDIR)$(DIR)Drv_StartUp.a $(foreach obj, $(DRV_STARTUP_OBJ), $(OBJDIR)$(DIR)$(obj))
