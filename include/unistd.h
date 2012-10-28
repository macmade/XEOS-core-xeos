/*******************************************************************************
 * XEOS - X86 Experimental Operating System
 * 
 * Copyright (c) 2010-2012, Jean-David Gadina <macmade@eosgarden.com>
 * All rights reserved.
 * 
 * XEOS Software License - Version 1.0 - December 21, 2012
 * 
 * Permission is hereby granted, free of charge, to any person or organisation
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to deal in the Software, with or without
 * modification, without restriction, including without limitation the rights
 * to use, execute, display, copy, reproduce, transmit, publish, distribute,
 * modify, merge, prepare derivative works of the Software, and to permit
 * third-parties to whom the Software is furnished to do so, all subject to the
 * following conditions:
 * 
 *      1.  Redistributions of source code, in whole or in part, must retain the
 *          above copyright notice and this entire statement, including the
 *          above license grant, this restriction and the following disclaimer.
 * 
 *      2.  Redistributions in binary form must reproduce the above copyright
 *          notice and this entire statement, including the above license grant,
 *          this restriction and the following disclaimer in the documentation
 *          and/or other materials provided with the distribution, unless the
 *          Software is distributed by the copyright owner as a library.
 *          A "library" means a collection of software functions and/or data
 *          prepared so as to be conveniently linked with application programs
 *          (which use some of those functions and data) to form executables.
 * 
 *      3.  The Software, or any substancial portion of the Software shall not
 *          be combined, included, derived, or linked (statically or
 *          dynamically) with software or libraries licensed under the terms
 *          of any GNU software license, including, but not limited to, the GNU
 *          General Public License (GNU/GPL) or the GNU Lesser General Public
 *          License (GNU/LGPL).
 * 
 *      4.  All advertising materials mentioning features or use of this
 *          software must display an acknowledgement stating that the product
 *          includes software developed by the copyright owner.
 * 
 *      5.  Neither the name of the copyright owner nor the names of its
 *          contributors may be used to endorse or promote products derived from
 *          this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT OWNER AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE, TITLE AND NON-INFRINGEMENT ARE DISCLAIMED.
 * 
 * IN NO EVENT SHALL THE COPYRIGHT OWNER, CONTRIBUTORS OR ANYONE DISTRIBUTING
 * THE SOFTWARE BE LIABLE FOR ANY CLAIM, DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN ACTION OF CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF OR IN CONNECTION WITH
 * THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************/

/* $Id$ */

#ifndef __XEOS_HAL_H__
#define __XEOS_HAL_H__
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/__types.h>

#ifndef __NULL
#define __NULL
#define NULL                                    __XEOS_NULL
#endif

#ifndef __SIZE_T
#define __SIZE_T
typedef __xeos_size_t                           size_t;
#endif

#ifndef __SSIZE_T
#define __SSIZE_T
typedef __xeos_ssize_t                          ssize_t;
#endif

#ifndef __UID_T
#define __UID_T
typedef __xeos_uid_t                            uid_t;
#endif

#ifndef __OFF_T
#define __OFF_T
typedef __xeos_off_t                            off_t;
#endif

#ifndef __PID_T
#define __PID_T
typedef __xeos_pid_t                            pid_t;
#endif

#ifndef __USECONDS_T
#define __USECONDS_T
typedef __xeos_useconds_t                       useconds_t;
#endif

#ifndef __INTPTR_T
#define __INTPTR_T
typedef __xeos_intptr_t                         intptr_t;
#endif

#define	_POSIX_VERSION                          0
#define	_POSIX2_VERSION                         0
#define	_POSIX2_C_VERSION                       0
#define	_XOPEN_VERSION                          0
#define	_XOPEN_XCU_VERSION                      0

#define	_POSIX2_C_BIND                          0
#define	_POSIX2_C_VERSION                       0
#define	_POSIX2_CHAR_TERM                       0
#define	_POSIX2_LOCALEDEF                       0
#define	_POSIX2_UPE                             0
#define	_POSIX2_VERSION                         0

#define	_XOPEN_XPG2                             0
#define	_XOPEN_XPG3                             0
#define	_XOPEN_XPG4                             0
#define	_XOPEN_UNIX                             0

#define	_POSIX_CHOWN_RESTRICTED                 0
#define	_POSIX_NO_TRUNC                         0
#define	_POSIX_VDISABLE                         0
#define	_POSIX_SAVED_IDS                        0
#define	_POSIX_JOB_CONTROL                      0

#define	_POSIX_THREADS
#define	_POSIX_THREAD_ATTR_STACKADDR            0
#define	_POSIX_THREAD_ATTR_STACKSIZE            0
#define	_POSIX_THREAD_PROCESS_SHARED            0
#define	_POSIX_THREAD_SAFE_FUNCTIONS            0

#define	_POSIX2_C_BIND                          0
#define	_POSIX2_C_DEV                           0
#define	_POSIX2_CHAR_TERM                       0
#define	_POSIX2_FORT_DEV                        0
#define	_POSIX2_FORT_RUN                        0
#define	_POSIX2_LOCALEDEF                       0
#define	_POSIX2_SW_DEV                          0
#define	_POSIX2_UPE                             0
#define	_XOPEN_CRYPT                            0
#define	_XOPEN_ENH_I18N                         0
#define	_XOPEN_LEGACY                           0
#define	_XOPEN_REALTIME                         0
#define	_XOPEN_REALTIME_THREADS                 0
#define	_XOPEN_SHM                              0
#define	_XBS5_ILP32_OFF32                       0
#define	_XBS5_ILP32_OFFBIG                      0
#define	_XBS5_LP64_OFF64                        0
#define	_XBS5_LPBIG_OFFBIG                      0

#define	_POSIX_ASYNCHRONOUS_IO                  0
#define	_POSIX_MEMLOCK                          0
#define	_POSIX_MEMLOCK_RANGE                    0
#define	_POSIX_MESSAGE_PASSING                  0
#define	_POSIX_PRIORITY_SCHEDULING              0
#define	_POSIX_REALTIME_SIGNALS                 0
#define	_POSIX_SEMAPHORES                       0
#define	_POSIX_SHARED_MEMORY_OBJECTS            0
#define	_POSIX_SYNCHRONIZED_IO                  0
#define	_POSIX_TIMERS                           0

#define	_POSIX_FSYNC                            0
#define	_POSIX_MAPPED_FILES                     0
#define	_POSIX_MEMORY_PROTECTION                0

#define	_POSIX_PRIORITIZED_IO                   0

#define	_POSIX_THREAD_PRIORITY_SCHEDULING       0
#define	_POSIX_THREAD_PRIO_INHERIT              0
#define	_POSIX_THREAD_PRIO_PROTECT              0

#define	_POSIX_ASYNC_IO                         0
#define	_POSIX_PRIO_IO                          0
#define	_POSIX_SYNC_IO                          0

#define	_CS_PATH                                0
#define	_CS_XBS5_ILP32_OFF32_CFLAGS             0
#define	_CS_XBS5_ILP32_OFF32_LDFLAGS            0
#define	_CS_XBS5_ILP32_OFF32_LIBS               0
#define	_CS_XBS5_ILP32_OFF32_LINTFLAGS          0
#define	_CS_XBS5_ILP32_OFFBIG_CFLAGS            0
#define	_CS_XBS5_ILP32_OFFBIG_LDFLAGS           0
#define	_CS_XBS5_ILP32_OFFBIG_LIBS              0
#define	_CS_XBS5_ILP32_OFFBIG_LINTFLAGS         0
#define	_CS_XBS5_LP64_OFF64_CFLAGS              0
#define	_CS_XBS5_LP64_OFF64_LDFLAGS             0
#define	_CS_XBS5_LP64_OFF64_LIBS                0
#define	_CS_XBS5_LP64_OFF64_LINTFLAGS           0
#define	_CS_XBS5_LPBIG_OFFBIG_CFLAGS            0
#define	_CS_XBS5_LPBIG_OFFBIG_LDFLAGS           0
#define	_CS_XBS5_LPBIG_OFFBIG_LIBS              0
#define	_CS_XBS5_LPBIG_OFFBIG_LINTFLAGS         0

#define	_SC_2_C_BIND                            0
#define	_SC_2_C_DEV                             0
#define	_SC_2_C_VERSION                         0
#define	_SC_2_FORT_DEV                          0
#define	_SC_2_FORT_RUN                          0
#define	_SC_2_LOCALEDEF                         0
#define	_SC_2_SW_DEV                            0
#define	_SC_2_UPE                               0
#define	_SC_2_VERSION                           0
#define	_SC_ARG_MAX                             0
#define	_SC_AIO_LISTIO_MAX                      0
#define	_SC_AIO_MAX                             0
#define	_SC_AIO_PRIO_DELTA_MAX                  0
#define	_SC_ASYNCHRONOUS_IO                     0
#define	_SC_ATEXIT_MAX                          0
#define	_SC_BC_BASE_MAX                         0
#define	_SC_BC_DIM_MAX                          0
#define	_SC_BC_SCALE_MAX                        0
#define	_SC_BC_STRING_MAX                       0
#define	_SC_CHILD_MAX                           0
#define	_SC_CLK_TCK                             0
#define	_SC_COLL_WEIGHTS_MAX                    0
#define	_SC_DELAYTIMER_MAX                      0
#define	_SC_EXPR_NEST_MAX                       0
#define	_SC_FSYNC                               0
#define	_SC_GETGR_R_SIZE_MAX                    0
#define	_SC_GETPW_R_SIZE_MAX                    0
#define	_SC_IOV_MAX                             0
#define	_SC_JOB_CONTROL                         0
#define	_SC_LINE_MAX                            0
#define	_SC_LOGIN_NAME_MAX                      0
#define	_SC_MAPPED_FILES                        0
#define	_SC_MEMLOCK                             0
#define	_SC_MEMLOCK_RANGE                       0
#define	_SC_MEMORY_PROTECTION                   0
#define	_SC_MESSAGE_PASSING                     0
#define	_SC_MQ_OPEN_MAX                         0
#define	_SC_MQ_PRIO_MAX                         0
#define	_SC_NGROUPS_MAX                         0
#define	_SC_OPEN_MAX                            0
#define	_SC_PAGESIZE                            0
#define	_SC_PAGE_SIZE                           0
#define	_SC_PASS_MAX (LEGACY)                   0
#define	_SC_PRIORITIZED_IO                      0
#define	_SC_PRIORITY_SCHEDULING                 0
#define	_SC_RE_DUP_MAX                          0
#define	_SC_REALTIME_SIGNALS                    0
#define	_SC_RTSIG_MAX                           0
#define	_SC_SAVED_IDS                           0
#define	_SC_SEMAPHORES                          0
#define	_SC_SEM_NSEMS_MAX                       0
#define	_SC_SEM_VALUE_MAX                       0
#define	_SC_SHARED_MEMORY_OBJECTS               0
#define	_SC_SIGQUEUE_MAX                        0
#define	_SC_STREAM_MAX                          0
#define	_SC_SYNCHRONIZED_IO                     0
#define	_SC_THREADS                             0
#define	_SC_THREAD_ATTR_STACKADDR               0
#define	_SC_THREAD_ATTR_STACKSIZE               0
#define	_SC_THREAD_DESTRUCTOR_ITERATIONS        0
#define	_SC_THREAD_KEYS_MAX                     0
#define	_SC_THREAD_PRIORITY_SCHEDULING          0
#define	_SC_THREAD_PRIO_INHERIT                 0
#define	_SC_THREAD_PRIO_PROTECT                 0
#define	_SC_THREAD_PROCESS_SHARED               0
#define	_SC_THREAD_SAFE_FUNCTIONS               0
#define	_SC_THREAD_STACK_MIN                    0
#define	_SC_THREAD_THREADS_MAX                  0
#define	_SC_TIMERS                              0
#define	_SC_TIMER_MAX                           0
#define	_SC_TTY_NAME_MAX                        0
#define	_SC_TZNAME_MAX                          0
#define	_SC_VERSION                             0
#define	_SC_XOPEN_VERSION                       0
#define	_SC_XOPEN_CRYPT                         0
#define	_SC_XOPEN_ENH_I18N                      0
#define	_SC_XOPEN_SHM                           0
#define	_SC_XOPEN_UNIX                          0
#define	_SC_XOPEN_XCU_VERSION                   0
#define	_SC_XOPEN_LEGACY                        0
#define	_SC_XOPEN_REALTIME                      0
#define	_SC_XOPEN_REALTIME_THREADS              0
#define	_SC_XBS5_ILP32_OFF32                    0
#define	_SC_XBS5_ILP32_OFFBIG                   0
#define	_SC_XBS5_LP64_OFF64                     0
#define	_SC_XBS5_LPBIG_OFFBIG                   0

#define	_PC_ASYNC_IO                            0
#define	_PC_CHOWN_RESTRICTED                    0
#define	_PC_FILESIZEBITS                        0
#define	_PC_LINK_MAX                            0
#define	_PC_MAX_CANON                           0
#define	_PC_MAX_INPUT                           0
#define	_PC_NAME_MAX                            0
#define	_PC_NO_TRUNC                            0
#define	_PC_PATH_MAX                            0
#define	_PC_PIPE_BUF                            0
#define	_PC_PRIO_IO                             0
#define	_PC_SYNC_IO                             0
#define	_PC_VDISABLE                            0

#define	F_LOCK                                  0
#define	F_ULOCK                                 0
#define	F_TEST                                  0
#define	F_TLOCK                                 0

#define	STDIN_FILENO                            0
#define	STDOUT_FILENO                           1
#define	STDERR_FILENO                           2

#define	F_OK                                    0
#define	X_OK                                    ( 1 << 0 )
#define	W_OK                                    ( 1 << 1 )
#define	R_OK                                    ( 1 << 2 )

#ifndef SEEK_SET
    #define SEEK_SET                            0
#endif

#ifndef SEEK_CUR
    #define SEEK_CUR                            1
#endif

#ifndef SEEK_END
    #define SEEK_END                            2
#endif

extern char * optarg;
extern int    optind;
extern int    opterr;
extern int    optopt;

int access( const char * name, int type );
unsigned int alarm( unsigned int seconds );
int brk( void * addr );
int chdir( const char * path );
int chroot( const char * path );
int chown( const char * file, uid_t owner, gid_t group );
int close( int fd );
size_t confstr( int name, char * buf, size_t len );
char * crypt( const char * key, const char * salt );
char * ctermid( char * s );
char * cuserid( char *  );
int dup( int fd );
int dup2( int fd1, int fd2 );
void encrypt( char block[ 64 ], int edflag );
int execl( const char * path, const char * arg, ... );
int execle( const char * path, const char * arg, ... );
int execlp( const char * path, const char * arg, ... );
int execv( const char * path, char * const argv[] );
int execve( const char * path, char * const argv[] , char * const envp[] );
int execvp( const char * path, char * const argv[] );
void _exit( int status );
int fchown( int fd, uid_t owner, gid_t group );
int fchdir( int fd );
int fdatasync( int fd );
pid_t fork( void );
long int fpathconf( int fd, int name );
int fsync( int fd );
int ftruncate( int fd, off_t len );
char * getcwd( char * buf, size_t size );
int getdtablesize( void );
gid_t getegid( void );
uid_t geteuid( void );
gid_t getgid( void );
int getgroups( int size, gid_t list[] );
long gethostid( void );
char * getlogin( void );
int getlogin_r( char * name, size_t len );
int getopt( int argc, char * const argv[], const char * options );
int getpagesize( void );
char * getpass( const char * prompt );
pid_t getpgid( pid_t pid );
pid_t getpgrp( void );
pid_t getpid( void );
pid_t getppid( void );
pid_t getsid( pid_t pid );
uid_t getuid( void );
char * getwd( char * buf );
int isatty( int );
int lchown( const char * file, uid_t owner, gid_t group );
int link( const char * from, const char * to );
int lockf( int fd, int cmd, off_t len );
off_t lseek( int fd, off_t offset, int whence );
int nice( int inc );
long int pathconf( const char * path, int name );
int pause( void );
int pipe( int desc[ 2 ] );
ssize_t pread( int fd, void * buf, size_t nbytes, off_t offset );
int pthread_atfork( void ( * prepare )( void ), void ( * parent )( void ), void ( * child )( void ) );
ssize_t pwrite( int fd, const void * buf, size_t nbytes, off_t offset );
ssize_t read( int fd, void * buf, size_t nbytes );
int readlink( const char * path, char * buf, size_t len );
int rmdir( const char * path );
void * sbrk( intptr_t delta );
int setgid( gid_t gid );
int setpgid( pid_t pid, pid_t pgid );
pid_t setpgrp( void );
int setregid( gid_t rgid, gid_t egid );
int setreuid( uid_t ruid, uid_t euid );
pid_t setsid( void );
int setuid( uid_t uid );
unsigned int sleep( unsigned int seconds );
void swab( const void * from, void * to, ssize_t n );
int symlink( const char * from, const char * to );
void sync( void );
long int sysconf( int name );
pid_t tcgetpgrp( int fd );
int tcsetpgrp( int fd, pid_t pgrp_id );
int truncate( const char * file, off_t len );
char * ttyname( int fd );
int ttyname_r( int fd, char * buf, size_t len );
useconds_t ualarm( useconds_t value, useconds_t interval );
int unlink( const char * name );
int usleep( useconds_t useconds );
pid_t vfork( void );
ssize_t write( int fd, const void * buf, size_t len );

#ifdef __cplusplus
}
#endif

#endif /* __XEOS_HAL_H__ */
