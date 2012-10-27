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

#ifndef __XEOS_TYPES_H__
#define __XEOS_TYPES_H__
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/__types.h>

#ifndef __BLKCNT_T
#define __BLKCNT_T
    typedef __xeos_blkcnt_t                     blkcnt_t;
#endif

#ifndef __BLKSIZE_T
#define __BLKSIZE_T
    typedef __xeos_blksize_t                    blksize_t;
#endif

#ifndef __CLOCK_T
#define __CLOCK_T
    typedef __xeos_clock_t                      clock_t;
#endif

#ifndef __CLOCKID_T
#define __CLOCKID_T
    typedef __xeos_clockid_t                    clockid_t;
#endif

#ifndef __DEV_T
#define __DEV_T
    typedef __xeos_dev_t                        dev_t;
#endif

#ifndef __FSBLKCNT_T
#define __FSBLKCNT_T
    typedef __xeos_fsblkcnt_t                   fsblkcnt_t;
#endif

#ifndef __FSFILCNT_T
#define __FSFILCNT_T
    typedef __xeos_fsfilcnt_t                   fsfilcnt_t;
#endif

#ifndef __GID_T
#define __GID_T
    typedef __xeos_gid_t                        gid_t;
#endif

#ifndef __ID_T
#define __ID_T
    typedef __xeos_id_t                         id_t;
#endif

#ifndef __INO_T
#define __INO_T
    typedef __xeos_ino_t                        ino_t;
#endif

#ifndef __KEY_T
#define __KEY_T
    typedef __xeos_key_t                        key_t;
#endif

#ifndef __MODE_T
#define __MODE_T
    typedef __xeos_mode_t                       mode_t;
#endif

#ifndef __NLINK_T
#define __NLINK_T
    typedef __xeos_nlink_t                      nlink_t;
#endif

#ifndef __OFF_T
#define __OFF_T
    typedef __xeos_off_t                        off_t;
#endif

#ifndef __PID_T
#define __PID_T
    typedef __xeos_pid_t                        pid_t;
#endif

#ifndef __PTHREAD_ATTR_T
#define __PTHREAD_ATTR_T
    typedef __xeos_pthread_attr_t               pthread_attr_t;
#endif

#ifndef __PTHREAD_BARRIER_T
#define __PTHREAD_BARRIER_T
    typedef __xeos_pthread_barrier_t            pthread_barrier_t;
#endif

#ifndef __PTHREAD_BARRIERATTR_T
#define __PTHREAD_BARRIERATTR_T
    typedef __xeos_pthread_barrierattr_t        pthread_barrierattr_t;
#endif

#ifndef __PTHREAD_COND_T
#define __PTHREAD_COND_T
    typedef __xeos_pthread_cond_t               pthread_cond_t;
#endif

#ifndef __PTHREAD_CONDATTR_T
#define __PTHREAD_CONDATTR_T
    typedef __xeos_pthread_condattr_t           pthread_condattr_t;
#endif

#ifndef __PTHREAD_KEY_T
#define __PTHREAD_KEY_T
    typedef __xeos_pthread_key_t                pthread_key_t;
#endif

#ifndef __PTHREAD_MUTEX_T
#define __PTHREAD_MUTEX_T
    typedef __xeos_pthread_mutex_t              pthread_mutex_t;
#endif

#ifndef __PTHREAD_MUTEXATTR_T
#define __PTHREAD_MUTEXATTR_T
    typedef __xeos_pthread_mutexattr_t          pthread_mutexattr_t;
#endif

#ifndef __PTHREAD_ONCE_T
#define __PTHREAD_ONCE_T
    typedef __xeos_pthread_once_t               pthread_once_t;
#endif

#ifndef __PTHREAD_RWLOCK_T
#define __PTHREAD_RWLOCK_T
    typedef __xeos_pthread_rwlock_t             pthread_rwlock_t;
#endif

#ifndef __PTHREAD_RWLOCKATTR_T
#define __PTHREAD_RWLOCKATTR_T
    typedef __xeos_pthread_rwlockattr_t         pthread_rwlockattr_t;
#endif

#ifndef __PTHREAD_SPINLOCK_T
#define__PTHREAD_SPINLOCK_T__
    typedef __xeos_pthread_spinlock_t           pthread_spinlock_t;
#endif

#ifndef __PTHREAD_T
#define __PTHREAD_T
    typedef __xeos_pthread_t                    pthread_t;
#endif

#ifndef __SIZE_T
#define __SIZE_T
    typedef __xeos_size_t                       size_t;
#endif

#ifndef __SSIZE_T
#define __SSIZE_T
    typedef __xeos_ssize_t                      ssize_t;
#endif

#ifndef __SUSECONDS_T
#define __SUSECONDS_T
    typedef __xeos_suseconds_t                  suseconds_t;
#endif

#ifndef __TIME_T
#define __TIME_T
    typedef __xeos_time_t                       time_t;
#endif

#ifndef __TIMER_T
#define __TIMER_T
    typedef __xeos_timer_t                      timer_t;
#endif

#ifndef __TRACE_ATTR_T
#define __TRACE_ATTR_T
    typedef __xeos_trace_attr_t                 trace_attr_t;
#endif

#ifndef __TRACE_EVENT_ID_T
#define __TRACE_EVENT_ID_T
    typedef __xeos_trace_event_id_t             trace_event_id_t;
#endif

#ifndef __TRACE_EVENT_SET_T
#define __TRACE_EVENT_SET_T
    typedef __xeos_trace_event_set_t            trace_event_set_t;
#endif

#ifndef __TRACE_ID_T
#define __TRACE_ID_T
    typedef __xeos_trace_id_t                   trace_id_t;
#endif

#ifndef __UID_T
#define __UID_T
    typedef __xeos_uid_t                        uid_t;
#endif

#ifndef __USECONDS_T
#define __USECONDS_T
    typedef __xeos_useconds_t                   useconds_t;
#endif

#ifdef __cplusplus
}
#endif

#endif /* __XEOS_TYPES_H__ */
