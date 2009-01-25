-include OpenDRV$(DIR)Io$(DIR)mak$(DIR)$(ARCH)$(DIR)Makefile

OPENDRV_IO_OBJ +=		Io_Init.o														\
							Io_Init_Arch.o

INCLUDE += 	-IOpenDRV$(DIR)Io$(DIR)inc											\
				-IOpenDRV$(DIR)Io$(DIR)inc$(DIR)$(ARCH)							\
				-IOpenDRV$(DIR)Io$(DIR)inc$(DIR)$(ARCH)$(DIR)$(DERIVATE)

LIB += OpenDRV_Io.a

VPATH += OpenDRV$(DIR)Io$(DIR)src												\
			OpenDRV$(DIR)Io$(DIR)src$(DIR)$(ARCH)								\
			OpenDRV$(DIR)Io$(DIR)src$(DIR)$(ARCH)$(DIR)$(DERIVATE)

GENFILES += OpenDRV$(DIR)Io$(DIR)gen$(DIR)inc$(DIR)Io_Cfg.h.php

OpenDRV_Io.a : $(OPENDRV_IO_OBJ)
	$(AR) -rcs $(LIBDIR)$(DIR)OpenDRV_Io.a $(foreach obj, $(OPENDRV_IO_OBJ), $(OBJDIR)$(DIR)$(obj))
