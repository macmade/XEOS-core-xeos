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
 * @file            XEOS_Main.c
 * @author          Jean-David Gadina
 * @copyright       (c) 2010-2012, Jean-David Gadina <macmade@eosgarden.com>
 */

#include "xeos/video.h"
#include "xeos/system.h"
#include "xeos/hal.h"
#include "xeos/isr.h"
#include <sys/syscall.h>

void XEOS_Main( void );
void XEOS_Main( void )
{
    unsigned int             i;
    XEOS_HAL_IDT_ISREntryRef isrEntry;
    
    /* Ensures interrupts are disabled, as we are setting up the kernel */
    XEOS_HAL_CPU_DisableInterrupts();
    
    /* Clears the screen */
    XEOS_Video_SetFG( XEOS_Video_ColorWhite );
    XEOS_Video_SetBG( XEOS_Video_ColorBlack );
    XEOS_Video_Clear();
    
    /* Initializes the Interrupt Descriptor Table */
    XEOS_HAL_IDT_Init();
    
    /*
     * Maps IRQs 0-7 to 0x20-0x27 and IRQs 8-15 to 0x28-0x2F.
     * This will allow us to install the exception handlers, and avoid
     * conflicts with existing IRQs mapping to exceptions.
     */
    XEOS_HAL_PIC_Remap( 0x20, 0x28 );
    
    /* Installs the exception handlers */
    for( i = 0; i < 20; i++ )
    {
        isrEntry = XEOS_HAL_IDT_GetISREntry( ( uint8_t )i );
        
        XEOS_HAL_IDT_ISREntrySetSelector( isrEntry, 0x08 );
        XEOS_HAL_IDT_ISREntrySetType( isrEntry, XEOS_HAL_IDT_ISREntryTypeInterrupt32 );
        XEOS_HAL_IDT_ISREntrySetPrivilegeLevel( isrEntry, XEOS_HAL_IDT_ISREntryPrivilegeLevelRing0 );
        XEOS_HAL_IDT_ISREntrySetPresent( isrEntry, true );
        XEOS_HAL_IDT_ISREntrySetHandler( isrEntry, XEOS_ISR_ExceptionHandler );
    }
    
    /* Installs the system timer ISR */
    isrEntry = XEOS_HAL_IDT_GetISREntry( 0x20 );
    
    XEOS_HAL_IDT_ISREntrySetSelector( isrEntry, 0x08 );
    XEOS_HAL_IDT_ISREntrySetType( isrEntry, XEOS_HAL_IDT_ISREntryTypeInterrupt32 );
    XEOS_HAL_IDT_ISREntrySetPrivilegeLevel( isrEntry, XEOS_HAL_IDT_ISREntryPrivilegeLevelRing0 );
    XEOS_HAL_IDT_ISREntrySetPresent( isrEntry, true );
    XEOS_HAL_IDT_ISREntrySetHandler( isrEntry, ( XEOS_HAL_IDT_ISRHandler )XEOS_ISR_Timer );
    
    /* Installs the system call ISR */
    isrEntry = XEOS_HAL_IDT_GetISREntry( 0x80 );
    
    XEOS_HAL_IDT_ISREntrySetSelector( isrEntry, 0x08 );
    XEOS_HAL_IDT_ISREntrySetType( isrEntry, XEOS_HAL_IDT_ISREntryTypeInterrupt32 );
    XEOS_HAL_IDT_ISREntrySetPrivilegeLevel( isrEntry, XEOS_HAL_IDT_ISREntryPrivilegeLevelRing3 );
    XEOS_HAL_IDT_ISREntrySetPresent( isrEntry, true );
    XEOS_HAL_IDT_ISREntrySetHandler( isrEntry, ( XEOS_HAL_IDT_ISRHandler )XEOS_ISR_SysCall );
    
    /* Installs the new Interrupt Descriptor Table */
    XEOS_HAL_IDT_Reload();
    
    /* (Re)enables the interrupts */
    XEOS_HAL_CPU_EnableInterrupts();
    
    XEOS_System_Panic( "It works..." );
    XEOS_HAL_CPU_Halt();
}

