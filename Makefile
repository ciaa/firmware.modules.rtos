###############################################################################
# Select modules
#

# ARCH
# define the architecture of the micro where the openosek will be executed
# at the moment the followings archictectures are supported:
#	- posix
#  - win
ARCH = posix

# DERIVATE
# defines the derivate. For each architecture none, one or more derivates can be
# defined
DERIVATE =

COMPILER = GCC

MODS +=	TestSuite \
			OpenSEK \
			moduletest01

all: OpenSEK

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

PROJECT = OpenSEK
BIN = $(PROJECT)

#TODO this has to be automatic depending in the COMPILER variable
CC = gcc

#CFLAGS = -c -Wall -ggdb3 $(INCLUDE) -DPROJECT=$(PROJECT) -DCOMPILER=$(COMPILER) -DARCH=$(ARCH) -DDERIVATE=$(DERIVATE) -fprofile-arcs -ftest-coverage
CFLAGS = -c -Wall -ggdb3 $(INCLUDE) -DPROJECT=$(PROJECT) -DCOMPILER=$(COMPILER) -DARCH=$(ARCH) -DDERIVATE=$(DERIVATE)

DOC += nm sizedoc reqdoc doxygen

###############################################################################
# include modules make files

%.o : %.c
	$(CC) $(CFLAGS) $< -o $(OBJDIR)$(DIR)$@

include $(foreach module, $(MODS), $(module)$(DIR)mak$(DIR)Makefile)

OpenSEK : $(OBJ) $(LIB)
	gcc $(foreach obj, $(OBJ), $(OBJDIR)$(DIR)$(obj)) $(foreach lib, $(LIB), $(LIBDIR)$(DIR)$(lib)) $(LFLAGS) -o $(BINDIR)$(DIR)$(BIN)
#	gcc $(foreach obj, $(OBJ), $(OBJDIR)$(DIR)$(obj)) $(foreach lib, $(LIB), $(LIBDIR)$(DIR)$(lib)) $(LFLAGS) -o $(BINDIR)$(DIR)$(BIN) -lgcov

generate : $(GEN)

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
	nm $(BINDIR)$(DIR)$(PROJECT) -f sysv -l -S > $(GENDIR)$(DIR)doc$(DIR)nm.out

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
	@echo OpenSEK Make Environment 0.1.0
	@echo Selected Architecture................: $(ARCH)
	@echo Selected Derivate....................: $(DERIVATE)
	@echo Selected Compiler....................: $(COMPILER)
	@echo Enabled Modules......................: $(MODS)
	@echo Output directory for object files....: $(OBJDIR)
	@echo Output directory for binary files....: $(BINDIR)
	@echo Output directory for library files...: $(LIBDIR)
	@echo Output directory for documentation...: $(DOCDIR)
	@echo Output directory for generated files.: $(GENDIR)
	@echo Configuration files..................: $(CFGFILES)


#ld -Map $(BINDIR)$(DIR)$(BIN).map $(foreach obj, $(OBJ), $(OBJDIR)$(DIR)$(obj)) $(foreach lib, $(LIB), $(LIBDIR)$(DIR)$(lib)) -o $(BINDIR)$(DIR)$(BIN)
	
