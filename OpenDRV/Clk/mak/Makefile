-include OpenDRV$(DIR)Clk$(DIR)mak$(DIR)$(ARCH)$(DIR)Makefile

OPENDRV_CLK_OBJ +=	Clk_Init.o														\
							Clk_Init_Arch.o

INCLUDE += 	-IOpenDRV$(DIR)Clk$(DIR)inc											\
				-IOpenDRV$(DIR)Clk$(DIR)inc$(DIR)$(ARCH)							\
				-IOpenDRV$(DIR)Clk$(DIR)inc$(DIR)$(ARCH)$(DIR)$(DERIVATE)

LIB += OpenDRV_Clk.a

VPATH += OpenDRV$(DIR)Clk$(DIR)src												\
			OpenDRV$(DIR)Clk$(DIR)src$(DIR)$(ARCH)								\
			OpenDRV$(DIR)Clk$(DIR)src$(DIR)$(ARCH)$(DIR)$(DERIVATE)

GENFILES += OpenDRV$(DIR)Clk$(DIR)gen$(DIR)inc$(DIR)Clk_Cfg.h.php

OpenDRV_Clk.a : $(OPENDRV_CLK_OBJ)
	$(AR) -rcs $(LIBDIR)$(DIR)OpenDRV_Clk.a $(foreach obj, $(OPENDRV_CLK_OBJ), $(OBJDIR)$(DIR)$(obj))
