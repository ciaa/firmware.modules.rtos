/** \page Windows Support for Windows (cygwin)
 *
 * \section winintro Inroduction
 *
 * If you do not have Linux or any posix compatible system you can run OpenSEK on windows.
 * For this propouse you are going to need cygwin. <a href="http://www.cygwin.com/">http://www.cygwin.com/</a>. You can
 * download and get help for the instalation on cygwin page.
 *
 * \section winipc Interrupt Simulation on Windows
 * 
 * To simulate the interrupts on windows you are going to need to install an extra
 * packet of cywgin called <b>cygrunsrv</b> you can find it in the Admin tools on the
 * cygwin configuration.
 *
 * After installing the packet you have to configure and start the cygserver for the first time,
 * the cygserver is going to take care of the IPC for the interrupts simulations on Windows.
 * you have to run the <b>cygserver-config</b> to create the default configuration.
 *
 * After loading the default configuration you have to run the server with:
 * net start cygserver or stop for stoping.
 *
 * The last thing you have to do is to enable the server so you have to define
 * the environment variable CYGWIN to server.
 *
 * export CYGWIN=server
 *
 * Then you can run OpenSEK on windows. :)
 *
 * \section winstack Stack Size on Windows
 *
 * The size of the stack of your tasks in windows has to be realtive BIG if you are going to use
 * system calls. I hope we can find a better solution for the next release but at this moment the
 * needed stack is about 50kb. But the problem is not the opensek alos the Cygwin Windows interfaces like
 * usleep and printf.
 *
 */
