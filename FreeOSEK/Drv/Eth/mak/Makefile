-include FreeOSEK$(DIR)Drv$(DIR)Eth$(DIR)mak$(DIR)$(ARCH)$(DIR)Makefile
-include FreeOSEK$(DIR)Drv$(DIR)Eth$(DIR)Phy$(DIR)mak$(DIR)Makefile
-include $(GENDIR)$(DIR)mak$(DIR)Make_Drv_Eth.mak

DRV_ETH_OBJ +=	Eth_Init.o														\
					Eth_MainFunction.o											\
					Eth_Transmit.o													\
					Eth_Init_Arch.o												\
					Eth_Internal_Arch.o											\
					Eth.o

INCLUDE += 	-IFreeOSEK$(DIR)Drv$(DIR)Eth$(DIR)inc					\
				-IFreeOSEK$(DIR)Drv$(DIR)Eth$(DIR)inc$(DIR)$(MAC)

LIB += Drv_Eth.a

VPATH += FreeOSEK$(DIR)Drv$(DIR)Eth$(DIR)src												\
			FreeOSEK$(DIR)Drv$(DIR)Eth$(DIR)src$(DIR)$(MAC)

GENFILES += FreeOSEK$(DIR)Drv$(DIR)Eth$(DIR)gen$(DIR)inc$(DIR)Eth_Cfg.h.php					\
				FreeOSEK$(DIR)Drv$(DIR)Eth$(DIR)gen$(DIR)mak$(DIR)Make_OpenDRV_Eth.mak.php

Drv_Eth.a : $(DRV_ETH_OBJ)
	$(AR) -rcs $(LIBDIR)$(DIR)Drv_Eth.a $(foreach obj, $(DRV_ETH_OBJ), $(OBJDIR)$(DIR)$(obj))
