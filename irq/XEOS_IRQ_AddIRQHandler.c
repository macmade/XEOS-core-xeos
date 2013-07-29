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
 * @file            XEOS_IRQ_AddIRQHandler.c
 * @author          Jean-David Gadina
 * @copyright       (c) 2010-2012, Jean-David Gadina - www.xs-labs.com
 */

#include "xeos/irq.h"
#include "xeos/__private/irq.h"
#include <stdlib.h>

bool XEOS_IRQ_AddIRQHandler( XEOS_HAL_PIC_IRQ irq, XEOS_IRQ_IRQHandler handler )
{
    unsigned int          i;
    XEOS_IRQ_IRQHandler * handlers;
    
    __XEOS_IRQ_Init();
    
    switch( irq )
    {
        case XEOS_HAL_PIC_IRQ0:     handlers = __XEOS_IRQ_IRQ0Handlers;     break;
        case XEOS_HAL_PIC_IRQ1:     handlers = __XEOS_IRQ_IRQ1Handlers;     break;
        case XEOS_HAL_PIC_IRQ2:     handlers = __XEOS_IRQ_IRQ2Handlers;     break;
        case XEOS_HAL_PIC_IRQ3:     handlers = __XEOS_IRQ_IRQ3Handlers;     break;
        case XEOS_HAL_PIC_IRQ4:     handlers = __XEOS_IRQ_IRQ4Handlers;     break;
        case XEOS_HAL_PIC_IRQ5:     handlers = __XEOS_IRQ_IRQ5Handlers;     break;
        case XEOS_HAL_PIC_IRQ6:     handlers = __XEOS_IRQ_IRQ6Handlers;     break;
        case XEOS_HAL_PIC_IRQ7:     handlers = __XEOS_IRQ_IRQ7Handlers;     break;
        case XEOS_HAL_PIC_IRQ8:     handlers = __XEOS_IRQ_IRQ8Handlers;     break;
        case XEOS_HAL_PIC_IRQ9:     handlers = __XEOS_IRQ_IRQ9Handlers;     break;
        case XEOS_HAL_PIC_IRQ10:    handlers = __XEOS_IRQ_IRQ10Handlers;    break;
        case XEOS_HAL_PIC_IRQ11:    handlers = __XEOS_IRQ_IRQ11Handlers;    break;
        case XEOS_HAL_PIC_IRQ12:    handlers = __XEOS_IRQ_IRQ12Handlers;    break;
        case XEOS_HAL_PIC_IRQ13:    handlers = __XEOS_IRQ_IRQ13Handlers;    break;
        case XEOS_HAL_PIC_IRQ14:    handlers = __XEOS_IRQ_IRQ14Handlers;    break;
        case XEOS_HAL_PIC_IRQ15:    handlers = __XEOS_IRQ_IRQ15Handlers;    break;
    }
    
    for( i = 0; i < __XEOS_IRQ_MAX_HANDLERS; i++ )
    {
        if( handlers[ i ] == NULL )
        {
            handlers[ i ] = handler;
            
            return true;
        }
    }
    
    return false;
}
