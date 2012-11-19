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

/*!
 * @file            __XEOS_HAL_IDT.c
 * @author          Jean-David Gadina
 * @copyright       (c) 2010-2012, Jean-David Gadina <macmade@eosgarden.com>
 */

#include "xeos/hal/idt.h"
#include "xeos/hal/__idt.h"
#include <stdlib.h>

#include "xeos/system.h"

#ifdef __LP64__
    
    struct __XEOS_HAL_IDT_Pointer64  __XEOS_HAL_IDT_Address;
    struct __XEOS_HAL_IDT_ISREntry64 __XEOS_HAL_IDT_ISREntries[ XEOS_HAL_IDT_MAX_DESCRIPTORS ];
    
#else
    
    struct __XEOS_HAL_IDT_Pointer32  __XEOS_HAL_IDT_Address;
    struct __XEOS_HAL_IDT_ISREntry32 __XEOS_HAL_IDT_ISREntries[ XEOS_HAL_IDT_MAX_DESCRIPTORS ];
    
#endif

XEOS_HAL_IDT_ISRHandler __XEOS_HAL_IDT_ISRHandlers[ XEOS_HAL_IDT_MAX_DESCRIPTORS ];

void __XEOS_HAL_IDT_HandleISR( uint8_t isr );
void __XEOS_HAL_IDT_HandleISR( uint8_t isr )
{
    XEOS_HAL_IDT_ISREntryRef entry;
    XEOS_HAL_IDT_ISRHandler  handler;
    
    entry = XEOS_HAL_IDT_GetISREntry( isr );
    
    if( entry == NULL )
    {
        return;
    }
    
    handler = XEOS_HAL_IDT_ISREntryGetHandler( entry );
    
    if( handler != NULL )
    {
       handler( isr );
    }
}

#ifdef __LP64__

#define __XEOS_HAL_IDT_DEF_ISR( _n_ )           \
                                                \
__asm__                                         \
(                                               \
    ".global __XEOS_HAL_IDT_ISR_" # _n_ "\n"    \
    "__XEOS_HAL_IDT_ISR_" # _n_ ":\n"           \
    "\n"                                        \
    "push %rax\n"                               \
    "push %rbx\n"                               \
    "push %rcx\n"                               \
    "push %rdx\n"                               \
    "push %rdi\n"                               \
    "push %rsi\n"                               \
    "push %r8\n"                                \
    "push %r9\n"                                \
    "push %r10\n"                               \
    "push %r11\n"                               \
    "push %r12\n"                               \
    "push %r13\n"                               \
    "push %r14\n"                               \
    "push %r15\n"                               \
    "push %rsp\n"                               \
    "push %rbp\n"                               \
    "\n"                                        \
    "movq $0x" # _n_ ", %rdi\n"                 \
    "call __XEOS_HAL_IDT_HandleISR\n"           \
    "\n"                                        \
    "pop %rbp\n"                                \
    "pop %rsp\n"                                \
    "pop %r15\n"                                \
    "pop %r14\n"                                \
    "pop %r13\n"                                \
    "pop %r12\n"                                \
    "pop %r11\n"                                \
    "pop %r10\n"                                \
    "pop %r9\n"                                 \
    "pop %r8\n"                                 \
    "pop %rsi\n"                                \
    "pop %rdi\n"                                \
    "pop %rdx\n"                                \
    "pop %rcx\n"                                \
    "pop %rbx\n"                                \
    "pop %rax\n"                                \
    "\n"                                        \
    "iretq\n"                                   \
)

#else

#define __XEOS_HAL_IDT_DEF_ISR( _n_ )           \
                                                \
__asm__                                         \
(                                               \
    ".global __XEOS_HAL_IDT_ISR_" # _n_ "\n"    \
    "\n"                                        \
    "__XEOS_HAL_IDT_ISR_" # _n_ ":\n"           \
    "\n"                                        \
    "push %eax\n"                               \
    "push %ebx\n"                               \
    "push %ecx\n"                               \
    "push %edx\n"                               \
    "push %edi\n"                               \
    "push %esi\n"                               \
    "push %esp\n"                               \
    "push %ebp\n"                               \
    "\n"                                        \
    "push $0x" # _n_ "\n"                       \
    "call __XEOS_HAL_IDT_HandleISR\n"           \
    "pop %eax\n"                                \
    "\n"                                        \
    "pop %ebp\n"                                \
    "pop %esp\n"                                \
    "pop %esi\n"                                \
    "pop %edi\n"                                \
    "pop %edx\n"                                \
    "pop %ecx\n"                                \
    "pop %ebx\n"                                \
    "pop %eax\n"                                \
    "\n"                                        \
    "iretl\n"                                   \
) 

#endif

#define __XEOS_HAL_IDT_DEF_ISR_GROUP( _n_ )     \
        __XEOS_HAL_IDT_DEF_ISR( _n_ ## 0 );     \
        __XEOS_HAL_IDT_DEF_ISR( _n_ ## 1 );     \
        __XEOS_HAL_IDT_DEF_ISR( _n_ ## 2 );     \
        __XEOS_HAL_IDT_DEF_ISR( _n_ ## 3 );     \
        __XEOS_HAL_IDT_DEF_ISR( _n_ ## 4 );     \
        __XEOS_HAL_IDT_DEF_ISR( _n_ ## 5 );     \
        __XEOS_HAL_IDT_DEF_ISR( _n_ ## 6 );     \
        __XEOS_HAL_IDT_DEF_ISR( _n_ ## 7 );     \
        __XEOS_HAL_IDT_DEF_ISR( _n_ ## 8 );     \
        __XEOS_HAL_IDT_DEF_ISR( _n_ ## 9 );     \
        __XEOS_HAL_IDT_DEF_ISR( _n_ ## A );     \
        __XEOS_HAL_IDT_DEF_ISR( _n_ ## B );     \
        __XEOS_HAL_IDT_DEF_ISR( _n_ ## C );     \
        __XEOS_HAL_IDT_DEF_ISR( _n_ ## D );     \
        __XEOS_HAL_IDT_DEF_ISR( _n_ ## E );     \
        __XEOS_HAL_IDT_DEF_ISR( _n_ ## F )

__XEOS_HAL_IDT_DEF_ISR_GROUP( 0 );
__XEOS_HAL_IDT_DEF_ISR_GROUP( 1 );
__XEOS_HAL_IDT_DEF_ISR_GROUP( 2 );
__XEOS_HAL_IDT_DEF_ISR_GROUP( 3 );
__XEOS_HAL_IDT_DEF_ISR_GROUP( 4 );
__XEOS_HAL_IDT_DEF_ISR_GROUP( 5 );
__XEOS_HAL_IDT_DEF_ISR_GROUP( 6 );
__XEOS_HAL_IDT_DEF_ISR_GROUP( 7 );
__XEOS_HAL_IDT_DEF_ISR_GROUP( 8 );
__XEOS_HAL_IDT_DEF_ISR_GROUP( 9 );
__XEOS_HAL_IDT_DEF_ISR_GROUP( A );
__XEOS_HAL_IDT_DEF_ISR_GROUP( B );
__XEOS_HAL_IDT_DEF_ISR_GROUP( C );
__XEOS_HAL_IDT_DEF_ISR_GROUP( D );
__XEOS_HAL_IDT_DEF_ISR_GROUP( E );
__XEOS_HAL_IDT_DEF_ISR_GROUP( F );
