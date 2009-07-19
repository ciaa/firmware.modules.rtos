##############################################################################
# add library
#
-include $(GENDIR)$(DIR)mak$(DIR)Make_seENC.mak

LIB += seENC.a

GEN += 

LFLAGS +=

SEENC_OBJ +=	

GENFILES +=	seENC$(DIR)gen$(DIR)mak$(DIR)Make_seENC.mak.php

VPATH += 

INCLUDE +=

seENC.a : $(SEENC_OBJ)
	ar -rcs $(LIBDIR)$(DIR)seENC.a $(foreach obj, $(SEENC_OBJ), $(OBJDIR)$(DIR)$(obj))

SPLINT +=

