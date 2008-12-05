##############################################################################
# add library
#
-include OpenGEN$(DIR)mak$(DIR)$(ARCH)$(DIR)Makefile
-include $(GENDIR)$(DIR)mak$(DIR)Make_OpenGEN.mak

LIB += OpenGEN.a

GEN +=

LFLAGS +=

OpenGEN_OBJ +=

GENFILES += OpenGEN$(DIR)gen$(DIR)mak$(DIR)Make_OpenGEN.mak.php		\
				OpenGEN$(DIR)gen$(DIR)inc$(DIR)MemMap_Arch_Cfg.h.php

VPATH += OpenGEN$(DIR)src	\
			OpenGEN$(DIR)src$(DIR)$(ARCH)

INCLUDE +=	-IOpenGEN$(DIR)inc													\
				-IOpenGEN$(DIR)inc$(DIR)$(ARCH)									\
				-IOpenGEN$(DIR)inc$(DIR)$(ARCH)$(DIR)$(DERIVATE)			\
				-IOpenGEN$(DIR)inc$(DIR)compilers$(DIR)$(COMPILER)

SPLINT +=

OpenGEN.a : $(OpenGEN_OBJ)
	ar -rcs $(LIBDIR)$(DIR)OpenGEN.a $(foreach obj, $(OpenGEN_OBJ), $(OBJDIR)$(DIR)$(obj))
