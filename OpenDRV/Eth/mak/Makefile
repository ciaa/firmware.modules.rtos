-include OpenDRV$(DIR)Eth$(DIR)mak$(DIR)$(ARCH)$(DIR)Makefile
-include $(GENDIR)$(DIR)mak$(DIR)Make_OpenDRV_Eth.mak

OPENDRV_ETH_OBJ +=		Eth_Init.o														\
								Eth_MainFunction.o											\
								Eth_Transmit.o													\
								Eth_Init_Arch.o												\
								Eth.o

INCLUDE += 	-IOpenDRV$(DIR)Eth$(DIR)inc											\
				-IOpenDRV$(DIR)Eth$(DIR)inc$(DIR)$(MAC)

LIB += OpenDRV_Eth.a

VPATH += OpenDRV$(DIR)Eth$(DIR)src												\
			OpenDRV$(DIR)Eth$(DIR)src$(DIR)$(MAC)

GENFILES += OpenDRV$(DIR)Eth$(DIR)gen$(DIR)inc$(DIR)Eth_Cfg.h.php					\
				OpenDRV$(DIR)Eth$(DIR)gen$(DIR)mak$(DIR)Make_OpenDRV_Eth.mak.php

OpenDRV_Eth.a : $(OPENDRV_ETH_OBJ)
	$(AR) -rcs $(LIBDIR)$(DIR)OpenDRV_Eth.a $(foreach obj, $(OPENDRV_ETH_OBJ), $(OBJDIR)$(DIR)$(obj))
