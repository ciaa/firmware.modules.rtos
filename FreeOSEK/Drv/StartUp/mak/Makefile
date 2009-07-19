-include FreeOSEK$(DIR)Drv$(DIR)StartUp$(DIR)mak$(DIR)$(ARCH)$(DIR)Makefile

LIB += Drv_StartUp.a

VPATH += FreeOSEK$(DIR)Drv$(DIR)StartUp$(DIR)src						\
			FreeOSEK$(DIR)Drv$(DIR)StartUp$(DIR)src$(DIR)$(ARCH)	\
			FreeOSEK$(DIR)Drv$(DIR)StartUp$(DIR)asm						\
			FreeOSEK$(DIR)Drv$(DIR)StartUp$(DIR)asm$(DIR)$(ARCH)


Drv_StartUp.a : $(DRV_STARTUP_OBJ)
	$(AR) -rcs $(LIBDIR)$(DIR)Drv_StartUp.a $(foreach obj, $(DRV_STARTUP_OBJ), $(OBJDIR)$(DIR)$(obj))
