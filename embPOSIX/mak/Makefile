##############################################################################
# add library
#
#-include embPOSIX$(DIR)mak$(DIR)$(ARCH)$(DIR)Makefile

LIB += embPOSIX.a

GEN += 

LFLAGS +=

embPOSIX_OBJ +=	string$(DIR)memcpy.o													\

GENFILES += 

VPATH += embPOSIX$(DIR)src

INCLUDE += 	-IembPOSIX$(DIR)inc															\
				-IembPOSIX$(DIR)inc$(DIR)$(ARCH)

embPOSIX.a : $(embPOSIX_OBJ)
	ar -rcs $(LIBDIR)$(DIR)embPOSIX.a $(foreach obj, $(embPOSIX_OBJ), $(OBJDIR)$(DIR)$(obj))


