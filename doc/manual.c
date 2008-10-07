/** \mainpage
 * \authors Mariano Cerdeiro (mcerdeiro@gmail.com)
 * \authors http://www.openosek.com.ar/
 *
 * \section intro Inroduction
 *
 * \subsection About OpenSEK
 *
 * OpenSEK is an Open Source Implementation of the RTOS specified by OSEK-VDX. You can get the
 * OSEK-VDX specification under http://www.osek-vdx.org/.
 *
 * \subsection forwhat For what can I use OpenSEK?
 *
 * At the moment OpenSEK is still in beta version, so you can use it if you are new with OSEK 
 * to win some know how. OpenSEK runs today only under posix system and it was tested only under
 * Linux. If you want to port it to a new architecture you are welcome.
 *
 * \subsection whatneed What do I need to run OpenSEK?
 *
 * To generate the system and to run it you will ned:
 *
 *  - php version 5.2.x (for the generation)
 *  - make
 *  - gcc
 * 
 * There are some other used tools that you are going to need if you want to have others 
 * features, like:*
 * 
 *  - SVN if you want to check it out from SVN server.
 *  - splint if you want to check the code
 *  - doxygen to generate the documentation
 * 
 * \subsection compiling Compiling OpenSEK for the first time
 *
 * If this is your fist time with OpenSEK I recomend you to download the last version
 * (at the moment the pre beta releas) as .tar.gz and to run followings commands:
 *
 * - tar -xzf OpenSEK_release_vx_x_x_YYYYMMDD_name
 * - cd OpenSEK_release_vx_x_x_YYYYMMDD_name
 * - make generate
 * - make
 * - make doc (only to generate the documentation)
 * - ./out/bin/OpenSEK
 *
 * If you dont change the original makefile you will generate and compile the module test, 
 * so if you run the executable after compiling it you are going to see the test cases and
 * OK, FAILED or NOTRUN.
 * If one or more of the test cases results are other than OK you are having problems, the code
 * is not running correctly.
 *
 * \subsection compilingyourown Compiling my own program with OpenSEK
 *
 * If you run the moduletests01 without problems you can try to run the example01 and start
 * changing the code. For that I recomend you to read the followings chapters
 *
 * \section directory OpenSEK Directory Three
 *
 * This section explains the Three used for OpenSEK and all used modules.
 *
 * \subsection rootdirectory Root Directory
 *
 * On the root directory of your OpenSEK instalation you can find the followings directories
 *
 * - out (output files are saved here)
 * - doc (documentation directory)
 * - modulesXX (OpenSEK modules)
 * 
 * and you will find the follogings files:
 *
 * - README (a short introduction)
 * - RELEASENOTES (release notes)
 * - FUTURERELEASES (some description from waht is comming)
 * - Makefile (general makefile)
 * 
 * \subsection moduledirectory Module Directory Three
 *
 * Every module (like for example OpenSEK) has the following directory structure:
 *
 * - OpenSEK
 *   - etc (configuration files)
 *   - gen (files to be generated)
 *   - src (source files)
 *   - inc (include files)
 *   - mak (make files)
 *
 * \subsection outdirectory Out Directory Three
 *
 * The out directory has the following structure:
 *
 * - out
 *   - doc (generated documentation)
 *   - bin (binary output)
 *   - gen (generated files output)
 *   - lib (libraries)
 *   - obj (object files)
 *
 * \section make Makefiles
 *
 * This section make an introduction to the make files strcture used in OpenSEK
 *
 * \subsection makegeneral General Makefile
 *
 * There is a principal make file which you can find in the root directory of OpenSEK.

 * In the general Makefile you shall indicate the architecture, indicate the modules you
 * are using, for example if you want to compile the example01 and not the moduletest01
 * you can change the following lines:
 *
 * MODS +=  TestSuite \
 *          OpenSEK \
 *          moduletest01
 *
 * to:
 *
 * MODS +=  TestSuite \
 *          OpenSEK \
 *          example01
 *
 * with the option PROJECT=OpenSEK you can set the name of the binary file.
 *
 * \subsection makemodule Module Makefile
 *
 * There is a make file for every module. You can find the module makefile in the directory mak
 * of the module.
 *
 * Following variables shall be defined on this file, lets take as example the OpenSEK make file
 *
 * LIB +=  OpenSEK.a
 *
 * defined the name of the module library name. All objects files of this module will be put
 * together as a library.
 *
 * GEN += genosek
 *
 * indicates which rules are necesary to generate this module, in this case GEN, this rules
 * are going to be executed with "make generate"
 *
 * OPENOSEK_OBJ +=
 *
 * are all object files needed for this module.
 *
 * GENFILES +=
 *
 * indicates all files that have to be generated for this module
 *
 * VPATH +=
 *
 * add all needed paths where make shall search for source files.
 *
 * INCLUDE +=
 *
 * add include directory for search of header files, take in account that allways the directory
 * has to be precceded with -I
 *
 * OpenOSEK.a
 *
 * is the rule to generate the library.
 *
 * genosek:
 *
 * indicates how to generate.
 *
 * \section config Configuration
 *
 * As you know the OpenSEK is a static configured operating system. For example the count
 * and types of task is defined at generation time. For that you have to write your own
 * configuration in oil format. The example01 contains a configuration under
 * example01/etc/example01.oil. If you need more information about the oil format take a
 * look on the OSEK-VDX page: http://www.osek-vdx.org
 *
 * Take into account that the oil format used on OpenSEK is still under development and
 * is in pre beta release, so do not surprise you if many thinks are not working as you want.
 * 
 * \section generation Generation
 *
 * After you have wrote your configuration you can generate your osek for that you have to run:
 *
 * make generate.
 *
 * The generator is a program who parse the oil file and generate the configuration for
 * the operating system in function from what you need, for example count of tasks, name
 * of the events, priority etc etc etc.
 *
 * The generator is written in php and the files to be generated too. 
 * \subsection generationinternal Internal Generation Structure
 *
 * For the generation the Makefile calls the script generator.php, this script has to be
 * called with some options that you can see editing the file.
 *
 * The generator file will call the config.php script to load the configuration and this
 * one calls the oilparser.php to parse the oilfiles given as input.
 *
 * The files to be generated are given as parameter too. 
 *
 * If you want to write your file to be generated is easy, take as example some of the
 * OpenOSEK/etc/src/\* to start.
 *
 * The generation process has to be optimized but is working.
 * Dependencis to each architecture
 *
 * At the moment OpenSEK is only available for POSIX.
 *
 * \section arch OpenSEK dependencies to every Architecture
 *
 * \subsection archposix OpenSEK for POSIX
 *
 * OpenSEK uses some posix services to simulate the hardware like interrupts and timers.
 * For the interrupt mechanisms a message queue with signal is used. Every time that you
 * send a message of only one byte to the message queue /dev/mqueue/BINNAME where BINNAME
 * is the binary name of the project defined in the Makefile with the PROJECT variable.
 * As defualt /dev/mqueue/OpenSEK. The received byte in this queue is interprated as an interrupt.
 *
 * \subsubsection archposixtimer Timers Simulations
 *
 * The POSIX variant has two simulated HW timers which have an interrupt every 10ms. Anyway
 * alarms are not working on the prebeta release.
 *
 */
