##############################################################################
# add library
#
#-include embPOSIX$(DIR)mak$(DIR)$(ARCH)$(DIR)Makefile

LIB += embPOSIX.a

GEN += 

LFLAGS +=

embPOSIX_OBJ +=	memcpy.o													\
						memset.o

GENFILES += 

VPATH += embPOSIX$(DIR)src						\
			embPOSIX$(DIR)src$(DIR)string

INCLUDE += 	-IembPOSIX$(DIR)inc															\
				-IembPOSIX$(DIR)inc$(DIR)$(ARCH)

embPOSIX.a : $(embPOSIX_OBJ)
	ar -rcs $(LIBDIR)$(DIR)embPOSIX.a $(foreach obj, $(embPOSIX_OBJ), $(OBJDIR)$(DIR)$(obj))


