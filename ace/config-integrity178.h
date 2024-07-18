// -*- C++ -*-

#ifndef ACE_CONFIG_INTEGRITY178_H
#define ACE_CONFIG_INTEGRITY178_H

/*
 * This config.h file is for version 11.4.x of the
 * INTEGRITY-178 RTOS from Green Hills Software
 * http://www.ghs.com/products/rtos/integrity.html
 */

// This is crafted to remove dependency on the POSIX calls provided
// by libraries available in INTEGRITY but not in INTEGRITY-178.
// Some network utility and socket functions are also turned off
// (see the sections near the end of the file).

#define ghs

/* compilation defines */
#define ACE_LACKS_GETPGID
#define ACE_LACKS_SETPGID
#define ACE_LACKS_SETREUID
#define ACE_LACKS_SETREGID
#define ACE_LACKS_SETSID
//#define ACE_LACKS_SETEGID
//#define ACE_LACKS_SETUID
//#define ACE_LACKS_SETEUID
//#define ACE_LACKS_GETEUID
//#define ACE_LACKS_GETUID
//#define ACE_LACKS_GETEGID
//#define ACE_LACKS_GETGID

#ifndef ACE_HAS_EXCEPTIONS
  #define ACE_HAS_EXCEPTIONS
#endif
#define ACE_NEW_THROWS_EXCEPTIONS
#define ACE_HAS_STANDARD_CPP_LIBRARY 1
#define ACE_HAS_TEMPLATE_SPECIALIZATION
#define ACE_TEMPLATES_REQUIRE_SOURCE 1
#define ACE_HAS_TEMPLATE_TYPEDEFS
#define TAO_USE_SEQUENCE_TEMPLATES
#define ACE_HAS_USING_KEYWORD
#define ACE_NEEDS_FUNC_DEFINITIONS
#define _REENTRANT
#define ACE_MT_SAFE 1

// Compiler/platform has correctly prototyped header files.
#define ACE_HAS_CPLUSPLUS_HEADERS

#define ACE_HAS_SHM_OPEN

/***** Operating System Defines *****/

/***** ANSI defines *****/
#define ACE_LACKS_TEMPNAM /* believe it or not, this is ANSI C */
#define ACE_HAS_STRERROR
#define ACE_LACKS_SENDMSG

/***** End Stack Defines *****/


/* SCA STUFF */
#define ACE_HAS_SIG_ATOMIC_T

#define ACE_HAS_SIGINFO_T
#define ACE_LACKS_SIGINFO_H
#define ACE_LACKS_UCONTEXT_H
#define ACE_HAS_SIG_C_FUNC
#define ACE_LACKS_SI_ADDR

#define ACE_HAS_POSIX_NONBLOCK
#define ACE_HAS_DIRENT

/***** End Threading Defines *****/

/***** Hardware Defines *****/
#define ACE_PAGE_SIZE 4096
/***** End Hardware Defines *****/

/****** SYSV_IPC STUFF *****/
#define ACE_LACKS_KEY_T

#define ACE_HAS_WCHAR
#define ACE_LACKS_ISCTYPE
#define ACE_LACKS_WCSICMP
#define ACE_LACKS_WCSNICMP
#define ACE_LACKS_WCSDUP
#define ACE_LACKS_WCSTOK
#define ACE_LACKS_ALPHASORT
#define ACE_LACKS_ITOW
#define ACE_LACKS_STRPTIME
#define ACE_LACKS_SYSTEM

/****** Posix Defines *****/
#define ACE_LACKS_KILL
#define ACE_LACKS_SIGSET
#define ACE_LACKS_SUSECONDS_T
#define ACE_LACKS_USECONDS_T
#define ACE_LACKS_WAIT
#define ACE_LACKS_WAITPID
#define ACE_HAS_POSIX_TIME
#define ACE_HAS_STRDUP_EMULATION
#define ACE_HAS_MSG
#define ACE_LACKS_CONDATTR_PSHARED
#define ACE_LACKS_EXEC
#define ACE_LACKS_FORK
#define ACE_LACKS_MKFIFO
#define ACE_LACKS_MKTEMP
#define ACE_LACKS_MKSTEMP
#define ACE_LACKS_MPROTECT
#define ACE_LACKS_MUTEXATTR_PSHARED
#define ACE_LACKS_RLIMIT
#define ACE_LACKS_RWLOCK_T
#define ACE_LACKS_SEMBUF_T
#define ACE_LACKS_UNIX_DOMAIN_SOCKETS
#define ACE_LACKS_SEEKDIR
#define ACE_LACKS_MSYNC
#define ACE_LACKS_NETDB_REENTRANT_FUNCTIONS
#define ACE_LACKS_SETGID
#define ACE_LACKS_PIPE
#define ACE_LACKS_SYS_PARAM_H
#define ACE_LACKS_SYS_MSG_H
#define ACE_LACKS_UNAME
#define ACE_LACKS_ISATTY
#define ACE_LACKS_STRCASECMP
#define ACE_LACKS_TRUNCATE
#define ACE_LACKS_PWD_FUNCTIONS
#define ACE_LACKS_UNIX_SIGNALS

// INTEGRITY has this concept of thread-specific storage in its native API.
// It's mentioned as Task-specific data in its document.
#define ACE_HAS_THREAD_SPECIFIC_STORAGE
#define ACE_LACKS_SYSV_SHMEM
#define ACE_LACKS_PUTENV
#define ACE_HAS_4_4BSD_SENDMSG_RECVMSG
#define ACE_LACKS_THREAD_PROCESS_SCOPING
#define ACE_LACKS_SETSCHED
#define ACE_LACKS_STRRECVFD
#define ACE_LACKS_SYSCONF

#define ACE_LACKS_REALPATH
#define ACE_LACKS_SWAB
#define ACE_HAS_CONSISTENT_SIGNAL_PROTOTYPES

/***** Not tied to standards AFAIK ****/
#define ACE_LACKS_MADVISE /* paging optimization not needed with INTEGRITY */
#define ACE_LACKS_INTTYPES_H
#define ACE_LACKS_SYS_RESOURCE_H
#define ACE_LACKS_SEARCH_H
#define ACE_LACKS_SYS_IPC_H
#define ACE_LACKS_SYS_SEM_H
#define ACE_LACKS_STROPTS_H
#define ACE_LACKS_SYS_SHM_H

/***** Network utility functions *****/
#define ACE_LACKS_GETADDRINFO
#define ACE_LACKS_GAI_STRERROR
#define ACE_LACKS_GETHOSTBYADDR
#define ACE_LACKS_GETHOSTBYADDR_R
#define ACE_LACKS_GETHOSTBYNAME
#define ACE_LACKS_GETNAMEINFO
#define ACE_LACKS_GETPROTOBYNAME
#define ACE_LACKS_GETPROTOBYNUMBER
#define ACE_LACKS_GETSERVBYNAME
#define ACE_LACKS_IF_NAMEINDEX
#define ACE_LACKS_IF_NAMETOINDEX
#define ACE_LACKS_INET_ADDR
#define ACE_LACKS_INET_ATON
#define ACE_LACKS_INET_NTOA
#define ACE_LACKS_INET_NTOP
#define ACE_LACKS_INET_PTON

/***** Socket functions *****/
#define ACE_LACKS_DUP
#define ACE_LACKS_DUP2
#define ACE_LACKS_FCNTL
#define ACE_LACKS_IOCTL
#define ACE_LACKS_RECVMSG
#define ACE_LACKS_SENDMSG
#define ACE_LACKS_SHUTDOWN
#define ACE_LACKS_SOCKETPAIR

// Add the following macros to config.h to
// build with --no-exceptions option in MULTI IDE
//#define ACE_INTEGRITY_NO_EXCEPT
// and use LEONET network library
//#define ACE_USES_GHS_LEONET

/***** STUFF INTEGRITY 4.0.8 APPEARS TO SUPPORT ****/
/* note, possibly untested with ace */

/***** TAO STUFF ****/
#define TAO_USE_DOTTED_DECIMAL_ADDRESSES 1

#include <INTEGRITY.h>

#include <time.h>

typedef void (*__sighandler_t)(int);

#ifdef ppc
#define ACE_HAS_POWERPC_TIMER
#endif

/* MIKEC Addtions */
#define ACE_HAS_NONCONST_SELECT_TIMEVAL
#include <sys/uio.h> // needed to define iovec
#define ACE_LACKS_READLINK
#define ACE_LACKS_GETPPID
#define NSIG (SIGRTMAX+1)
#define ACE_USES_STD_NAMESPACE_FOR_STDCPP_LIB 1
#define ACE_USE_RCSID 0
#define ACE_LACKS_CUSERID
#define ACE_NEEDS_HUGE_THREAD_STACKSIZE 0x5000
#define fileno(file) ((file)->io_channel) //Hack to get Svc_Conf_l.cpp compiled
#define ACE_DEFAULT_THREAD_PRIORITY 127
#define PRI_FIFO_MIN 1
#define PRI_FIFO_MAX 127
#define ACE_THR_PRI_FIFO_DEF 127
#define PRI_RR_MIN 1
#define PRI_RR_MAX 127
#define ACE_THR_PRI_RR_DEF 127
#define PRI_OTHER_MIN 1
#define PRI_OTHER_MAX 127
#define ACE_THR_PRI_OTHER_DEF 127
#define ACE_PTHREAD_RETURN_ON_EXIT
#undef ACE_LACKS_UNLINK

#define ACE_HAS_TIMED_MESSAGE_BLOCKS

extern "C" {
int unlink(const char *);
}

#define ACE_HAS_VOIDPTR_GETTIMEOFDAY
#define ACE_LACKS_UNIX_SYSLOG
#define ACE_LACKS_TELLDIR
#define ACE_LACKS_SEEKDIR
#define ACE_LACKS_GETHOSTENT


/* end MIKEC Addtions */

// Hack to avoid ensure that things defined in ind_io.h
// have the right linkage
#include <unistd.h>

#endif /* ACE_CONFIG_INTEGRITY178_H */
