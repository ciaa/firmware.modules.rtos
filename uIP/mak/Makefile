LIB += uIP.a

GEN += 

LFLAGS +=

UIP_OBJ +=

GENFILES += uIP$(DIR)gen$(DIR)inc$(DIR)uip-conf.h.php

VPATH += 

INCLUDE += 	-IuIP$(DIR)inc

uIP.a : $(UIP_OBJ)
	ar -rcs $(LIBDIR)$(DIR)uIP.a $(foreach obj, $(UIP_OBJ), $(OBJDIR)$(DIR)$(obj))

