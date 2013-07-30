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
 * @header          irq.h
 * @author          Jean-David Gadina
 * @copyright       (c) 2010-2012, Jean-David Gadina - www.xs-labs.com
 */

#ifndef __XEOS_IRQ_H__
#define __XEOS_IRQ_H__
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <xeos/macros.h>
#include <xeos/hal/pic.h>
#include <xeos/hal/cpu.h>
#include <stdint.h>
#include <stdbool.h>

/*!
 * @typedef         XEOS_IRQ_IRQHandler
 * @abstract        Handler function for an IRQ
 * @param           irq         The IRQ line
 * @param           registers   The processor registers
 */
typedef void ( * XEOS_IRQ_IRQHandler )( XEOS_HAL_PIC_IRQ irq, XEOS_HAL_CPU_Registers * registers );

/*!
 * @function        XEOS_IRQ_AddIRQHandler
 * @abstract        Installs a handler function for an IRQ line
 * @discussion      Note that the number of handlers for an IRQ line is limited.
 *                  If the maximum number of handlers is reached, the handler
 *                  won't be installed and the function will return false.
 * @param           irq         The IRQ line
 * @param           handler     The IRQ handler function
 * @result          True if the handler was installed, otherwise false
 */
bool XEOS_IRQ_AddIRQHandler( XEOS_HAL_PIC_IRQ irq, XEOS_IRQ_IRQHandler handler );

/*!
 * @function        XEOS_IRQ_RemoveIRQHandler
 * @abstract        Removes a handler function for an IRQ line
 * @param           irq         The IRQ line
 * @param           handler     The IRQ handler function
 */
void XEOS_IRQ_RemoveIRQHandler( XEOS_HAL_PIC_IRQ irq, XEOS_IRQ_IRQHandler handler );

/*!
 * @function        XEOS_IRQ_ExecuteIRQHandlers
 * @abstract        Executes all installed handlers for an IRQ line
 * @param           irq         The IRQ line
 * @param           registers   The processor registers
 */
void XEOS_IRQ_ExecuteIRQHandlers( XEOS_HAL_PIC_IRQ irq, XEOS_HAL_CPU_Registers * registers );

/*!
 * @function        XEOS_IRQ_SystemTimer
 * @abstract        IRQ handler for the system timer (IRQ0)
 * @param           irq         The IRQ line
 * @param           registers   The processor registers
 */
void XEOS_IRQ_SystemTimer( XEOS_HAL_PIC_IRQ irq, XEOS_HAL_CPU_Registers * registers );

/*!
 * @function        XEOS_IRQ_RealTimeClock
 * @abstract        IRQ handler for the real time clock (IRQ8)
 * @param           irq         The IRQ line
 * @param           registers   The processor registers
 */
void XEOS_IRQ_RealTimeClock( XEOS_HAL_PIC_IRQ irq, XEOS_HAL_CPU_Registers * registers );

/*!
 * @function        XEOS_IRQ_Keyboard
 * @abstract        IRQ handler for the keyboard (IRQ1)
 * @param           irq         The IRQ line
 * @param           registers   The processor registers
 */
void XEOS_IRQ_Keyboard( XEOS_HAL_PIC_IRQ irq, XEOS_HAL_CPU_Registers * registers );

#ifdef __cplusplus
}
#endif

#endif /* __XEOS_IRQ_H__ */
