###############################################################################
# Select modules
#

# ARCH
# define the architecture of the micro where the openosek will be executed
# at the moment the followings archictectures are supported:
#	- posix
#  - win
#  - arm
ARCH = arm7

# CPU Types
# defines the CPU family. For each architecture none, one or more CPUTYPEs can be
# defined
CPUTYPE = lpc2xxx

# CPU
CPU = lpc2468

# BOARD
BOARD = lpc-e2468

# COMPILER
COMPILER = gcc

# MODULES
#
# Available modules are:
# OpenGEN				Generator and include files
# FreeOSEK 				RTOS OSEK OS
# TestSuite				Test suite
# seENC					Small Embedded Encryption Module
# OpenDRV				Drivers
# tst/moduletest01	Module tests for all modules
# examples/Blinking	Blinking Leds Example
#

MODS +=	examples/Blinking			\
			OpenGEN						\
			OpenDRV						\
			FreeOSEK

#MODS += 	tst/moduletest01		\
#			OpenGEN						\
#			OpenDRV						\
#			FreeOSEK						\
#			TestSuite

#MODS +=	tst/moduletest01			\
#			OpenGEN						\
#			OpenDRV						\
#			FreeOSEK						\
#			TestSuite
#			uIP							
#			embPOSIX

all: FreeOSEK

INCLUDE = 
OBJ = 
LIB =
DIR = /

###############################################################################
OBJDIR = out$(DIR)obj
BINDIR = out$(DIR)bin
LIBDIR = out$(DIR)lib
DOCDIR = out$(DIR)doc
GENDIR = out$(DIR)gen

PROJECT = FreeOSEK
BIN = $(PROJECT)

#CFLAGS = -c -Wall -ggdb3 $(INCLUDE) -DPROJECT=$(PROJECT) -DCOMPILER=$(COMPILER) -DARCH=$(ARCH) -DCPUTYPE=$(CPUTYPE) -fprofile-arcs -ftest-coverage
CFLAGS += $(INCLUDE) -DPROJECT=$(PROJECT) -DCOMPILER=$(COMPILER) -DARCH=$(ARCH) -DCPUTYPE=$(CPUTYPE) -DCPU=$(CPU)

DOC += nm sizedoc reqdoc doxygen

###############################################################################
# include modules make files

%.o : %.c
	@ echo
	@ echo Compiling $<
	$(CC) $(CFLAGS) $< -o $(OBJDIR)$(DIR)$@

%.o : %.s
	@ echo
	@ echo Assembling $<
	$(AS) $(AFLAGS) $< -o $(OBJDIR)$(DIR)$@


include $(foreach module, $(MODS), $(module)$(DIR)mak$(DIR)Makefile)

FreeOSEK : $(OBJ) $(LIB)
	@ echo
	@ echo Linking $(BINDIR)$(DIR)$(BIN)
	$(LD) $(foreach obj, $(OBJ), $(OBJDIR)$(DIR)$(obj)) $(foreach lib, $(LIB), $(LIBDIR)$(DIR)$(lib)) $(LFLAGS) -o $(BINDIR)$(DIR)$(BIN)

#	$(CC) $(foreach obj, $(OBJ), $(OBJDIR)$(DIR)$(obj)) $(foreach lib, $(LIB), $(LIBDIR)$(DIR)$(lib)) $(LFLAGS) -o $(BINDIR)$(DIR)$(BIN) -lgcov

generate : $(GEN)

debug : $(DEBUG)
	$(GDB) $(GDBO) $(BINDIR)$(DIR)$(BIN)

clean : $(CLEAN)
	rm -rf $(BINDIR)$(DIR)*
	rm -rf $(OBJDIR)$(DIR)*
	rm -rf $(LIBDIR)$(DIR)*
	rm -rf $(GENDIR)$(DIR)*
	rm -rf $(DOCDIR)$(DIR)*

doc : $(DOC)

reqdoc :
	./doc/reqdoc.pl

sizedoc :
	./doc/sizedoc.pl

doxygen :
	doxygen doc$(DIR)doxygen.cfg

splint :
	splint $(SPLINT) $(INCLUDE) +posixlib -Dstack_t=char +charindex -predboolint -boolops -type

nm :
	mkdir -p $(GENDIR)$(DIR)doc
	$(NM) $(BINDIR)$(DIR)$(PROJECT) -f sysv -l -S > $(GENDIR)$(DIR)doc$(DIR)nm.out

help :
	@echo ++++++++
	@echo + HELP +
	@echo ++++++++
	@echo the Makefiles has the followings options:
	@echo  
	@echo make help - to show this help
	@echo make info - to show the make environment variables
	@echo make generate - to generate the code
	@echo make - to compile the code, has to be executed after make generate
	@echo make clean - to remove all created files: binary, objects, libraries, doc, generated files
	@echo make doc - to generate the documentation (execute make reqdoc and make sizedoc automatically)
	@echo make splint - to perform splint analyze
	@echo make reqdoc - generate requirement tracing documentation
	@echo make sizedoc - generate size documentation

info :
	@echo ++++++++
	@echo + INFO +
	@echo ++++++++
	@echo FreeOSEK Make Environment 0.1.0
	@echo Selected Architecture................: $(ARCH)
	@echo Selected Cputype.....................: $(CPUTYPE)
	@echo Selected Cpu.........................: $(CPU)
	@echo Selected Board.......................: $(BOARD)
	@echo Selected Compiler....................: $(COMPILER)
	@echo Enabled Modules......................: $(MODS)
	@echo Output directory for object files....: $(OBJDIR)
	@echo Output directory for binary files....: $(BINDIR)
	@echo Output directory for library files...: $(LIBDIR)
	@echo Output directory for documentation...: $(DOCDIR)
	@echo Output directory for generated files.: $(GENDIR)
	@echo Configuration files..................: $(CFGFILES)


#ld -Map $(BINDIR)$(DIR)$(BIN).map $(foreach obj, $(OBJ), $(OBJDIR)$(DIR)$(obj)) $(foreach lib, $(LIB), $(LIBDIR)$(DIR)$(lib)) -o $(BINDIR)$(DIR)$(BIN)
	
