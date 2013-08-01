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
 * @header          __idt.h
 * @author          Jean-David Gadina
 * @copyright       (c) 2010-2013, Jean-David Gadina - www.xs-labs.com
 */

#ifndef __XEOS_HAL___PRIVATE_IDT_H__
#define __XEOS_HAL___PRIVATE_IDT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <xeos/macros.h>
#include <xeos/hal/idt.h>

#ifdef __clang__
#pragma pack( 1 )
#endif

/*!
 * @struct          __XEOS_HAL_IDT_ISREntry32
 * @abstract        32 bits ISR entry
 * @var             baseLow         ISR address (bits 0-15)
 * @var             selector        Code segment selector
 * @var             __reserved_0    Unused
 * @var             flags           ISR entry flags
 * @var             baseHigh        ISR address (bits 16-31)
 */
struct __XEOS_HAL_IDT_ISREntry32
{
    uint16_t    baseLow;
    uint16_t    selector;
    uint8_t     __reserved_0;
    uint8_t     flags;
    uint16_t    baseHigh;
};

/*!
 * @struct          __XEOS_HAL_IDT_Pointer32
 * @abstract        32 bits IDT pointer
 * @var             limit           IDT size
 * @var             base            IDT address
 */
struct __XEOS_HAL_IDT_Pointer32
{
    uint16_t    limit;
    uint32_t    base;
};

/*!
 * @struct          __XEOS_HAL_IDT_ISREntry64
 * @abstract        64 bits ISR entry
 * @var             baseLow         ISR address (bits 0-15)
 * @var             selector        Code segment selector
 * @var             __reserved_0    Unused
 * @var             flags           ISR entry flags
 * @var             baseMiddle      ISR address (bits 16-31)
 * @var             baseHigh        ISR address (bits 32-63)
 * @var             __reserved_1    Unused
 */
struct __XEOS_HAL_IDT_ISREntry64
{
    uint16_t    baseLow;
    uint16_t    selector;
    uint8_t     __reserved_0;
    uint8_t     flags;
    uint16_t    baseMiddle;
    uint32_t    baseHigh;
    uint32_t    __reserved_1;
};

/*!
 * @struct          __XEOS_HAL_IDT_Pointer64
 * @abstract        64 bits IDT pointer
 * @var             limit           IDT size
 * @var             base            IDT address
 */
struct __XEOS_HAL_IDT_Pointer64
{
    uint16_t    limit;
    uint64_t    base;
};

#ifdef __clang__
#pragma pack()
#endif

/*!
 * @var         __XEOS_HAL_IDT_Address
 * @abstract    IDT pointer
 */
#ifdef __LP64__
    extern struct __XEOS_HAL_IDT_Pointer64      __XEOS_HAL_IDT_Address;
#else
    extern struct __XEOS_HAL_IDT_Pointer32      __XEOS_HAL_IDT_Address;
#endif

/*!
 * @var         __XEOS_HAL_IDT_ISREntries
 * @abstract    Array of ISR entries
 */
#ifdef __LP64__
    extern struct __XEOS_HAL_IDT_ISREntry64     __XEOS_HAL_IDT_ISREntries[];
#else
    extern struct __XEOS_HAL_IDT_ISREntry32     __XEOS_HAL_IDT_ISREntries[];
#endif

/*!
 * @typedef     __XEOS_HAL_IDT_ISREntry
 * @abstract    ISR entry type
 */
#ifdef __LP64__
    typedef struct __XEOS_HAL_IDT_ISREntry64    __XEOS_HAL_IDT_ISREntry;
#else
    typedef struct __XEOS_HAL_IDT_ISREntry32    __XEOS_HAL_IDT_ISREntry;
#endif

/*!
 * @typedef     __XEOS_HAL_IDT_Pointer
 * @abstract    ISR pointer type
 */
#ifdef __LP64__
    typedef struct __XEOS_HAL_IDT_Pointer64     __XEOS_HAL_IDT_Pointer;
#else
    typedef struct __XEOS_HAL_IDT_Pointer32     __XEOS_HAL_IDT_Pointer;
#endif

/*!
 * @var         __XEOS_HAL_IDT_ISRHandlers
 * @abstract    Array of ISR handler functions
 */
extern XEOS_HAL_IDT_ISRHandler __XEOS_HAL_IDT_ISRHandlers[];

#ifdef __cplusplus
}
#endif

#endif /* __XEOS_HAL___PRIVATE_IDT_H__ */
