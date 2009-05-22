###############################################################################
# add library
#
OBJ +=	main.o					\
			BlinkingLedsTask.o	\
			CarSimulationTask.o	\
			CombiTask.o				\
			GearTask.o				\
			SetCarTask.o			\
			GlobalVar.o

VPATH += examples$(DIR)CarCombi$(DIR)src \
			examples$(DIR)CarCombi$(DIR)asm

INCLUDE += -Iexamples$(DIR)CarCombi$(DIR)inc

CFGFILES += examples$(DIR)CarCombi$(DIR)etc$(DIR)FreeOSEK.oil					\
				examples$(DIR)CarCombi$(DIR)etc$(DIR)$(BOARD)$(DIR)OpenDRV.oil

CLEAN += carcombiclean

carcombiclean :

