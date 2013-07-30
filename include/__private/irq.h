/*******************************************************************************
 * XEOS - X86 Experimental Operating System
 * 
 * Copyright (c) 2010-2012, Jean-David Gadina - www.xs-labs.com
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
 * @header          __irq.h
 * @author          Jean-David Gadina
 * @copyright       (c) 2010-2012, Jean-David Gadina - www.xs-labs.com
 */

#ifndef __XEOS___PRIVATE_IRQ_H__
#define __XEOS___PRIVATE_IRQ_H__
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <xeos/macros.h>
#include <xeos/irq.h>

#ifdef __clang__
#pragma pack( 1 )
#endif

/*!
 * @define      __XEOS_IRQ_MAX_HANDLERS
 * @abstract    The maximum number of handlers for an IRQ line
 */
#define __XEOS_IRQ_MAX_HANDLERS     32

/*!
 * @function    __XEOS_IRQ_Init
 * @abstract    Initialization of the IRQ chaining system
 */
void __XEOS_IRQ_Init( void );

/*!
 * @var         __XEOS_IRQ_Inited
 * @abstract    Whether the the IRQ chaining system is initialized or not
 */
extern bool __XEOS_IRQ_Inited;

/*!
 * @var         __XEOS_IRQ_IRQ0Handlers
 * @abstract    Handlers for IRQ line 0
 */
extern XEOS_IRQ_IRQHandler __XEOS_IRQ_IRQ0Handlers[];

/*!
 * @var         __XEOS_IRQ_IRQ0Handlers
 * @abstract    Handlers for IRQ line 1
 */
extern XEOS_IRQ_IRQHandler __XEOS_IRQ_IRQ1Handlers[];

/*!
 * @var         __XEOS_IRQ_IRQ0Handlers
 * @abstract    Handlers for IRQ line 2
 */
extern XEOS_IRQ_IRQHandler __XEOS_IRQ_IRQ2Handlers[];

/*!
 * @var         __XEOS_IRQ_IRQ0Handlers
 * @abstract    Handlers for IRQ line 3
 */
extern XEOS_IRQ_IRQHandler __XEOS_IRQ_IRQ3Handlers[];

/*!
 * @var         __XEOS_IRQ_IRQ0Handlers
 * @abstract    Handlers for IRQ line 4
 */
extern XEOS_IRQ_IRQHandler __XEOS_IRQ_IRQ4Handlers[];

/*!
 * @var         __XEOS_IRQ_IRQ0Handlers
 * @abstract    Handlers for IRQ line 5
 */
extern XEOS_IRQ_IRQHandler __XEOS_IRQ_IRQ5Handlers[];

/*!
 * @var         __XEOS_IRQ_IRQ0Handlers
 * @abstract    Handlers for IRQ line 6
 */
extern XEOS_IRQ_IRQHandler __XEOS_IRQ_IRQ6Handlers[];

/*!
 * @var         __XEOS_IRQ_IRQ0Handlers
 * @abstract    Handlers for IRQ line 7
 */
extern XEOS_IRQ_IRQHandler __XEOS_IRQ_IRQ7Handlers[];

/*!
 * @var         __XEOS_IRQ_IRQ0Handlers
 * @abstract    Handlers for IRQ line 8
 */
extern XEOS_IRQ_IRQHandler __XEOS_IRQ_IRQ8Handlers[];

/*!
 * @var         __XEOS_IRQ_IRQ0Handlers
 * @abstract    Handlers for IRQ line 9
 */
extern XEOS_IRQ_IRQHandler __XEOS_IRQ_IRQ9Handlers[];

/*!
 * @var         __XEOS_IRQ_IRQ0Handlers
 * @abstract    Handlers for IRQ line 10
 */
extern XEOS_IRQ_IRQHandler __XEOS_IRQ_IRQ10Handlers[];

/*!
 * @var         __XEOS_IRQ_IRQ0Handlers
 * @abstract    Handlers for IRQ line 11
 */
extern XEOS_IRQ_IRQHandler __XEOS_IRQ_IRQ11Handlers[];

/*!
 * @var         __XEOS_IRQ_IRQ0Handlers
 * @abstract    Handlers for IRQ line 12
 */
extern XEOS_IRQ_IRQHandler __XEOS_IRQ_IRQ12Handlers[];

/*!
 * @var         __XEOS_IRQ_IRQ0Handlers
 * @abstract    Handlers for IRQ line 13
 */
extern XEOS_IRQ_IRQHandler __XEOS_IRQ_IRQ13Handlers[];

/*!
 * @var         __XEOS_IRQ_IRQ0Handlers
 * @abstract    Handlers for IRQ line 14
 */
extern XEOS_IRQ_IRQHandler __XEOS_IRQ_IRQ14Handlers[];

/*!
 * @var         __XEOS_IRQ_IRQ0Handlers
 * @abstract    Handlers for IRQ line 15
 */
extern XEOS_IRQ_IRQHandler __XEOS_IRQ_IRQ15Handlers[];

#ifdef __clang__
#pragma pack()
#endif

#ifdef __cplusplus
}
#endif

#endif /* __XEOS___PRIVATE_IRQ_H__ */
