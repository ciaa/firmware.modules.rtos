##############################################################################
# add library
#
-include OpenGEN$(DIR)mak$(DIR)$(ARCH)$(DIR)Makefile
-include $(GENDIR)$(DIR)mak$(DIR)Make_OpenGEN.mak

LIB += OpenGEN.a

GEN +=

LFLAGS +=

OpenGEN_OBJ +=

GENFILES += OpenGEN$(DIR)gen$(DIR)mak$(DIR)Make_OpenGEN.mak.php

VPATH += OpenGEN$(DIR)src	\
			OpenGEN$(DIR)src$(DIR)$(ARCH)

INCLUDE +=	-IOpenGEN$(DIR)inc												\
				-IOpenGEN$(DIR)inc$(DIR)$(ARCH)								\
				-IOpenGEN$(DIR)inc$(DIR)$(ARCH)$(DIR)$(DERIVATE)

SPLINT +=

OpenGEN.a : $(OpenGEN_OBJ)
	ar -rcs $(LIBDIR)$(DIR)OpenGEN.a $(foreach obj, $(OpenGEN_OBJ), $(OBJDIR)$(DIR)$(obj))
