-include OpenDRV$(DIR)Eth$(DIR)mak$(DIR)$(ARCH)$(DIR)Makefile

OPENDRV_ETH_OBJ +=		Eth_Init.o														\
								Eth_MainFunction.o											\
								Eth_Transmit.o													\
								Eth_Init_Arch.h

INCLUDE += 	-IOpenDRV$(DIR)Eth$(DIR)inc											\
				-IOpenDRV$(DIR)Eth$(DIR)inc$(DIR)$(ARCH)							\
				-IOpenDRV$(DIR)Eth$(DIR)inc$(DIR)$(ARCH)$(DIR)$(CPUTYPE)

LIB += OpenDRV_Eth.a

VPATH += OpenDRV$(DIR)Eth$(DIR)src												\
			OpenDRV$(DIR)Eth$(DIR)src$(DIR)$(ARCH)								\
			OpenDRV$(DIR)Eth$(DIR)src$(DIR)$(ARCH)$(DIR)$(CPUTYPE)

GENFILES += OpenDRV$(DIR)Eth$(DIR)gen$(DIR)inc$(DIR)Eth_Cfg.h.php

OpenDRV_Eth.a : $(OPENDRV_ETH_OBJ)
	$(AR) -rcs $(LIBDIR)$(DIR)OpenDRV_Eth.a $(foreach obj, $(OPENDRV_ETH_OBJ), $(OBJDIR)$(DIR)$(obj))
