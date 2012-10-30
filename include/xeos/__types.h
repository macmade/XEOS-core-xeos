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

#ifndef __XEOS___TYPES_H__
#define __XEOS___TYPES_H__
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define __XEOS_NULL                     ( ( void * )0 )
#define __XEOS_FLT_EVAL_METHOD__        1

typedef unsigned int                    __XEOS_size_t;
typedef long                            __XEOS_clock_t;
typedef unsigned long                   __XEOS_time_t;
typedef long                            __XEOS_intptr_t;
typedef unsigned long                   __XEOS_uintptr_t;

#ifdef __clang__
    typedef __builtin_va_list           __XEOS_va_list;
#else
    typedef char *                      __XEOS_va_list;
#endif

#ifdef __WCHAR_TYPE__
    typedef __WCHAR_TYPE__              __XEOS_wchar_t;
#else
    typedef short                       __XEOS_wchar_t;
#endif

typedef int                             __XEOS_blkcnt_t;
typedef int                             __XEOS_blksize_t;
typedef int                             __XEOS_clockid_t;
typedef int                             __XEOS_dev_t;
typedef int                             __XEOS_fsblkcnt_t;
typedef int                             __XEOS_fsfilcnt_t;
typedef int                             __XEOS_gid_t;
typedef int                             __XEOS_id_t;
typedef int                             __XEOS_ino_t;
typedef int                             __XEOS_key_t;
typedef int                             __XEOS_mode_t;
typedef int                             __XEOS_nlink_t;
typedef int                             __XEOS_off_t;
typedef int                             __XEOS_pid_t;
typedef int                             __XEOS_pthread_attr_t;
typedef int                             __XEOS_pthread_barrier_t;
typedef int                             __XEOS_pthread_barrierattr_t;
typedef int                             __XEOS_pthread_cond_t;
typedef int                             __XEOS_pthread_condattr_t;
typedef int                             __XEOS_pthread_key_t;
typedef int                             __XEOS_pthread_mutex_t;
typedef int                             __XEOS_pthread_mutexattr_t;
typedef int                             __XEOS_pthread_once_t;
typedef int                             __XEOS_pthread_rwlock_t;
typedef int                             __XEOS_pthread_rwlockattr_t;
typedef int                             __XEOS_pthread_spinlock_t;
typedef int                             __XEOS_pthread_t;
typedef int                             __XEOS_ssize_t;
typedef int                             __XEOS_suseconds_t;
typedef int                             __XEOS_timer_t;
typedef int                             __XEOS_trace_attr_t;
typedef int                             __XEOS_trace_event_id_t;
typedef int                             __XEOS_trace_event_set_t;
typedef int                             __XEOS_trace_id_t;
typedef int                             __XEOS_uid_t;
typedef int                             __XEOS_useconds_t;

#ifdef __cplusplus
}
#endif

#endif /* __XEOS___TYPES_H__ */
