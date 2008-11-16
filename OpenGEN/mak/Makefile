##############################################################################
# add library
#
-include $(GENDIR)$(DIR)mak$(DIR)Make_OpenGEN.mak

LIB += OpenGEN.a

GEN +=

LFLAGS +=

OPENOSEK_OBJ +=

GENFILES += OpenGEN$(DIR)gen$(DIR)mak$(DIR)Make_OpenGEN.mak.php

VPATH +=

INCLUDE +=	-IOpenGEN$(DIR)inc												\
				-IOpenGEN$(DIR)inc$(DIR)$(ARCH)								\
				-IOpenGEN$(DIR)inc$(DIR)$(ARCH)$(DIR)$(DERIVATE)

SPLINT +=

OpenGEN.a : $(OpenGEN_OBJ)
	ar -rcs $(LIBDIR)$(DIR)OpenGEN.a $(foreach obj, $(OpenGEN_OBJ), $(OBJDIR)$(DIR)$(obj))
