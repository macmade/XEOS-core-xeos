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

typedef unsigned int                    __xeos_size_t;
typedef char *                          __xeos_va_list;
typedef long                            __xeos_clock_t;
typedef unsigned long                   __xeos_time_t;
typedef long                            __xeos_intptr_t;
typedef unsigned long                   __xeos_uintptr_t;

#ifdef __WCHAR_TYPE__
    typedef __WCHAR_TYPE__              __xeos_wchar_t;
#else
    typedef short                       __xeos_wchar_t;
#endif

typedef int                             __xeos_blkcnt_t;
typedef int                             __xeos_blksize_t;
typedef int                             __xeos_clockid_t;
typedef int                             __xeos_dev_t;
typedef int                             __xeos_fsblkcnt_t;
typedef int                             __xeos_fsfilcnt_t;
typedef int                             __xeos_gid_t;
typedef int                             __xeos_id_t;
typedef int                             __xeos_ino_t;
typedef int                             __xeos_key_t;
typedef int                             __xeos_mode_t;
typedef int                             __xeos_nlink_t;
typedef int                             __xeos_off_t;
typedef int                             __xeos_pid_t;
typedef int                             __xeos_pthread_attr_t;
typedef int                             __xeos_pthread_barrier_t;
typedef int                             __xeos_pthread_barrierattr_t;
typedef int                             __xeos_pthread_cond_t;
typedef int                             __xeos_pthread_condattr_t;
typedef int                             __xeos_pthread_key_t;
typedef int                             __xeos_pthread_mutex_t;
typedef int                             __xeos_pthread_mutexattr_t;
typedef int                             __xeos_pthread_once_t;
typedef int                             __xeos_pthread_rwlock_t;
typedef int                             __xeos_pthread_rwlockattr_t;
typedef int                             __xeos_pthread_spinlock_t;
typedef int                             __xeos_pthread_t;
typedef int                             __xeos_ssize_t;
typedef int                             __xeos_suseconds_t;
typedef int                             __xeos_timer_t;
typedef int                             __xeos_trace_attr_t;
typedef int                             __xeos_trace_event_id_t;
typedef int                             __xeos_trace_event_set_t;
typedef int                             __xeos_trace_id_t;
typedef int                             __xeos_uid_t;
typedef int                             __xeos_useconds_t;

#ifdef __cplusplus
}
#endif

#endif /* __XEOS___TYPES_H__ */
