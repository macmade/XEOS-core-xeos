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

/*!
 * @author          Jean-David Gadina
 * @copyright       (c) 2010-2015, Jean-David Gadina - www.xs-labs.com
 */

#include <xeos/isr.h>
#include <xeos/irq.h>
#include <xeos/hal/pic.h>

void XEOS_ISR_IRQ( uint8_t isr, XEOS_HAL_CPU_Registers * registers )
{
    XEOS_HAL_PIC_IRQ irq;
    
    switch( isr )
    {
        case 0x20:  irq = XEOS_HAL_PIC_IRQ0;    break;
        case 0x21:  irq = XEOS_HAL_PIC_IRQ1;    break;
        case 0x22:  irq = XEOS_HAL_PIC_IRQ2;    break;
        case 0x23:  irq = XEOS_HAL_PIC_IRQ3;    break;
        case 0x24:  irq = XEOS_HAL_PIC_IRQ4;    break;
        case 0x25:  irq = XEOS_HAL_PIC_IRQ5;    break;
        case 0x26:  irq = XEOS_HAL_PIC_IRQ6;    break;
        case 0x27:  irq = XEOS_HAL_PIC_IRQ7;    break;
        case 0x28:  irq = XEOS_HAL_PIC_IRQ8;    break;
        case 0x29:  irq = XEOS_HAL_PIC_IRQ9;    break;
        case 0x2A:  irq = XEOS_HAL_PIC_IRQ10;   break;
        case 0x2B:  irq = XEOS_HAL_PIC_IRQ11;   break;
        case 0x2C:  irq = XEOS_HAL_PIC_IRQ12;   break;
        case 0x2D:  irq = XEOS_HAL_PIC_IRQ13;   break;
        case 0x2E:  irq = XEOS_HAL_PIC_IRQ14;   break;
        case 0x2F:  irq = XEOS_HAL_PIC_IRQ15;   break;
        default:    return;
    }
    
    XEOS_IRQ_ExecuteIRQHandlers( irq, registers );
    
    if( isr >= 0x28 )
    {
        XEOS_HAL_PIC_SendEOI( XEOS_HAL_PIC_Controller2 );
    }
    
    XEOS_HAL_PIC_SendEOI( XEOS_HAL_PIC_Controller1 );
}

