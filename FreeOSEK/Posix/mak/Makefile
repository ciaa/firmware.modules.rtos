##############################################################################
# add library
#
#-include embPOSIX$(DIR)mak$(DIR)$(ARCH)$(DIR)Makefile

LIB += Posix.a

GEN += 

LFLAGS +=

POSIX_OBJ +=	memcpy.o													\
					memset.o

GENFILES += 

VPATH += FreeOSEK$(DIR)Posix$(DIR)src						\
			FreeOSEK$(DIR)Posix$(DIR)src$(DIR)string

INCLUDE += 	-IFreeOSEK$(DIR)Posix$(DIR)inc															\
				-IFreeOSEK$(DIR)Posix$(DIR)inc$(DIR)$(ARCH)

Posix.a : $(POSIX_OBJ)
	ar -rcs $(LIBDIR)$(DIR)Posix.a $(foreach obj, $(POSIX_OBJ), $(OBJDIR)$(DIR)$(obj))

