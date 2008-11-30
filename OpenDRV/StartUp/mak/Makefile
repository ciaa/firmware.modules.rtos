-include OpenDRV$(DIR)StartUp$(DIR)mak$(DIR)$(ARCH)$(DIR)Makefile

LIB += OpenDRV_StartUp.a

VPATH += OpenDRV$(DIR)StartUp$(DIR)src					\
			OpenDRV$(DIR)StartUp$(DIR)src$(DIR)$(ARCH)


OpenDRV_StartUp.a : $(OPENDRV_STARTUP_OBJ)
	$(AR) -rcs $(LIBDIR)$(DIR)OpenDRV_StartUp.a $(foreach obj, $(OPENDRV_STARTUP_OBJ), $(OBJDIR)$(DIR)$(obj))
