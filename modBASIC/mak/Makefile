##############################################################################
# add library
#
-include $(GENDIR)$(DIR)mak$(DIR)Make_modBASIC.mak

LIB += modBASIC.a

GEN += 

LFLAGS +=

MODBASIC_OBJ +=	

GENFILES +=	modBASIC$(DIR)gen$(DIR)mak$(DIR)Make_modBASIC.mak.php

VPATH += 

INCLUDE +=

modBASIC.a : $(MODBASIC_OBJ)
	ar -rcs $(LIBDIR)$(DIR)modBASIC.a $(foreach obj, $(SEENC_OBJ), $(OBJDIR)$(DIR)$(obj))

SPLINT +=

