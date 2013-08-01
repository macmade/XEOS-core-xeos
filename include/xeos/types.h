/*******************************************************************************
 * XEOS - X86 Experimental Operating System
 * 
 * Copyright (c) 2010-2013, Jean-David Gadina - www.xs-labs.com
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

/*!
 * @header          types.h
 * @author          Jean-David Gadina
 * @copyright       (c) 2010-2013, Jean-David Gadina - www.xs-labs.com
 */

#ifndef __XEOS_TYPES_H__
#define __XEOS_TYPES_H__
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <xeos/macros.h>

#define XEOS_NULL                       ( ( void * )0 )
#define XEOS_FLT_EVAL_METHOD            1

typedef unsigned int                    XEOS_Size;
typedef long                            XEOS_Clock;
typedef unsigned long                   XEOS_Time;
typedef long                            XEOS_IntPointer;
typedef unsigned long                   XEOS_UIntPointer;

#ifdef __clang__
    typedef __builtin_va_list           XEOS_VAList;
#else
    typedef char *                      XEOS_VAList;
#endif

#ifdef __WCHAR_TYPE__
    typedef __WCHAR_TYPE__              XEOS_WChar;
#else
    typedef short                       XEOS_WChar;
#endif

typedef int                             XEOS_BlockCount;
typedef int                             XEOS_BlockSize;
typedef int                             XEOS_ClockID;
typedef int                             XEOS_Device;
typedef int                             XEOS_FSBlockCount;
typedef int                             XEOS_FSFileCount;
typedef int                             XEOS_GroupID;
typedef int                             XEOS_ID;
typedef int                             XEOS_Inode;
typedef int                             XEOS_Key;
typedef int                             XEOS_Mode;
typedef int                             XEOS_NLink;
typedef int                             XEOS_Offset;
typedef int                             XEOS_ProcessID;
typedef int                             XEOS_PThreadAttribute;
typedef int                             XEOS_PThreadBarrier;
typedef int                             XEOS_PThreadBarrierAttribute;
typedef int                             XEOS_PThreadCondition;
typedef int                             XEOS_PThreadConditionAttribute;
typedef int                             XEOS_PThreadKey;
typedef int                             XEOS_PThreadMutex;
typedef int                             XEOS_PThreadMutexAttribute;
typedef int                             XEOS_PThreadOnce;
typedef int                             XEOS_PThreadRWLock;
typedef int                             XEOS_PThreadRWLockAttribute;
typedef int                             XEOS_PThreadSpinlock;
typedef int                             XEOS_PThread;
typedef int                             XEOS_SSize;
typedef int                             XEOS_SUSeconds;
typedef int                             XEOS_Timer;
typedef int                             XEOS_TraceAttribute;
typedef int                             XEOS_TraceEventID;
typedef int                             XEOS_TraceEventSet;
typedef int                             XEOS_TraceID;
typedef int                             XEOS_UserID;
typedef int                             XEOS_USeconds;

#ifdef __cplusplus
}
#endif

#endif /* __XEOS_TYPES_H__ */
