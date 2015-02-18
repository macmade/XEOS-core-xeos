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
 * @file            XEOS_ISR_Exception.c
 * @author          Jean-David Gadina
 * @copyright       (c) 2010-2013, Jean-David Gadina - www.xs-labs.com
 */

#include <xeos/isr.h>
#include <xeos/system.h>
#include <xeos/video.h>
#include <xeos/debug.h>

static void XEOS_ISR_Exception_PrintKernelTrace( void );
static void XEOS_ISR_Exception_PrintKernelTrace( void )
{
    XEOS_Debug_TraceRef     trace;
    unsigned int            i;
    XEOS_Debug_SymbolRef    symbol;
    void                  * address;
    
    trace = XEOS_Debug_GetKernelTrace();
    
    for( i = 5; i < XEOS_Debug_TraceGetSymbolCount( trace ); i++ )
    {
        if( i > 6 )
        {
            break;
        }
        
        symbol = XEOS_Debug_TraceGetSymbolAtIndex( trace, i );
        
        if
        (
               symbol == NULL
            || XEOS_Debug_SymbolGetFunctionAddress( symbol ) == NULL
            || XEOS_Debug_SymbolGetCallSiteAddress( symbol ) == NULL
        )
        {
            break;
        }
        
        address = XEOS_Debug_SymbolGetFunctionAddress( symbol );
        
        XEOS_Video_Printf
        (
            "0x%016llX %s\n",
            ( uint64_t )address,
            XEOS_Debug_SymbolGetFunctionName( symbol )
        );
    }
}

void XEOS_ISR_Exception( uint8_t isr, XEOS_HAL_CPU_Registers * registers )
{
    char * exception;
    
    switch( isr )
    {
        case 0x00:  exception = "CPU Exception - 0x00 / #DE: Divide-by-zero Error";             break;
        case 0x01:  exception = "CPU Exception - 0x01 / #DB: Debug";                            break;
        case 0x02:  exception = "CPU Exception - 0x02:       Non-maskable Interrupt";           break;
        case 0x03:  exception = "CPU Exception - 0x03 / #BP: Breakpoint";                       break;
        case 0x04:  exception = "CPU Exception - 0x04 / #OF: Overflow";                         break;
        case 0x05:  exception = "CPU Exception - 0x05 / #BR: Bound Range Exceeded";             break;
        case 0x06:  exception = "CPU Exception - 0x06 / #UD: Invalid Opcode";                   break;
        case 0x07:  exception = "CPU Exception - 0x07 / #NM: Device Not Available";             break;
        case 0x08:  exception = "CPU Exception - 0x08 / #DF: Double Fault";                     break;
        case 0x09:  exception = "CPU Exception - 0x09:       Coprocessor Segment Overrun";      break;
        case 0x0A:  exception = "CPU Exception - 0x0A / #TS: Invalid TSS";                      break;
        case 0x0B:  exception = "CPU Exception - 0x0B / #NP: Segment Not Present";              break;
        case 0x0C:  exception = "CPU Exception - 0x0C / #SS: Stack-Segment Fault";              break;
        case 0x0D:  exception = "CPU Exception - 0x0D / #GP: General Protection Fault";         break;
        case 0x0E:  exception = "CPU Exception - 0x0E / #PF: Page Fault";                       break;
        case 0x10:  exception = "CPU Exception - 0x10 / #MF: x87 Floating-Point Exception";     break;
        case 0x11:  exception = "CPU Exception - 0x11 / #AC: Alignment Check";                  break;
        case 0x12:  exception = "CPU Exception - 0x12 / #MC: Machine Check";                    break;
        case 0x13:  exception = "CPU Exception - 0x13 / #XM: SIMD Floating-Point Exception";    break;
        case 0x1E:  exception = "CPU Exception - 0x1E / #SX: Security Exception";               break;
        default:    exception = "CPU Exception - Unknown - No information available";           break;
    }
    
    #ifdef __LP64__
    
    XEOS_System_Panicf
    (
        "%s\n"
        "\n"
        "RAX: %#016lX RBX: %#016lX RCX: %#016lX\n"
        "RDX: %#016lX RDI: %#016lX RSI: %#016lX\n"
        "R8:  %#016lX R9:  %#016lX R10: %#016lX\n"
        "R11: %#016lX R12: %#016lX R13: %#016lX\n"
        "R14: %#016lX R15: %#016lX\n"
        "RSP: %#016lX RBP: %#016lX\n",
        XEOS_ISR_Exception_PrintKernelTrace,
        exception,
        ( long )( registers->rax ),
        ( long )( registers->rbx ),
        ( long )( registers->rcx ),
        ( long )( registers->rdx ),
        ( long )( registers->rdi ),
        ( long )( registers->rsi ),
        ( long )( registers->r8 ),
        ( long )( registers->r9 ),
        ( long )( registers->r10 ),
        ( long )( registers->r11 ),
        ( long )( registers->r12 ),
        ( long )( registers->r13 ),
        ( long )( registers->r14 ),
        ( long )( registers->r15 ),
        ( long )( registers->rsp ),
        ( long )( registers->rbp )
    );
    
    #else
    
    XEOS_System_Panicf
    (
        "%s\n"
        "\n"
        "EAX: %#08X EBX: %#08X ECX: %#08X EDI: %#08X\n"
        "ESI: %#08X ESP: %#08X EAX: %#08X EBP: %#08X\n",
        XEOS_ISR_Exception_PrintKernelTrace,
        exception,
        registers->eax,
        registers->ebx,
        registers->ecx,
        registers->edx,
        registers->edi,
        registers->esi,
        registers->esp,
        registers->ebp
    );
    
    #endif
}

