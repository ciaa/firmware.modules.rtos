##############################################################################
# add library
#
LIB += TestSuite.a

TESTSUITE_OBJ += 	TestSuite.o				\
						TS_Internal_Cfg.o	

GENFILES += FreeOSEK$(DIR)TestSuite$(DIR)gen$(DIR)inc$(DIR)TS_Cfg.h.php					\
				FreeOSEK$(DIR)TestSuite$(DIR)gen$(DIR)src$(DIR)TS_Internal_Cfg.c.php

VPATH += FreeOSEK$(DIR)TestSuite$(DIR)src					\
			$(GENDIR)$(DIR)src

INCLUDE += 	-IFreeOSEK$(DIR)TestSuite$(DIR)inc				\
				-IFreeOSEK$(DIR)TestSuite$(DIR)inc$(DIR)$(ARCH)$(DIR)

TestSuite.a : $(TESTSUITE_OBJ)
	ar -rcs $(LIBDIR)$(DIR)TestSuite.a $(foreach obj, $(TESTSUITE_OBJ), $(OBJDIR)$(DIR)$(obj))
