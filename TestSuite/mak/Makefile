##############################################################################
# add library
#
LIB += TestSuite.a

TESTSUITE_OBJ += 	TestSuite.o				\
						TS_Internal_Cfg.o	

GENFILES += TestSuite$(DIR)gen$(DIR)inc$(DIR)TS_Cfg.h.php					\
				TestSuite$(DIR)gen$(DIR)src$(DIR)TS_Internal_Cfg.c.php

VPATH += TestSuite$(DIR)src					\
			$(GENDIR)$(DIR)src

INCLUDE += 	-ITestSuite$(DIR)inc

TestSuite.a : $(TESTSUITE_OBJ)
	ar -rcs $(LIBDIR)$(DIR)TestSuite.a $(foreach obj, $(TESTSUITE_OBJ), $(OBJDIR)$(DIR)$(obj))
