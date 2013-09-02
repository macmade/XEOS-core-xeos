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
 * @file            XEOS_Main.c
 * @author          Jean-David Gadina
 * @copyright       (c) 2010-2013, Jean-David Gadina - www.xs-labs.com
 */

#include "XEOS_Main.h"
#include "__XEOS_Main.h"
#include <xeos/video.h>
#include <xeos/system.h>
#include <xeos/mem.h>
#include <xeos/vm.h>
#include <xeos/hal.h>
#include <xeos/isr.h>
#include <xeos/irq.h>
#include <system/syscall.h>
#include <stdlib.h>
#include <string.h>
#include <acpi/acpi.h>
#include <acpi/acpica.h>

#define __NOP                       \
    __asm__                         \
    (                               \
        "nop;nop;nop;nop;nop;\n"    \
        "nop;nop;nop;nop;nop;\n"    \
    );

#define __KERN_INIT_SECTION( _msg_, _status_, _code_ )  \
        __XEOS_Main_Prompt( _msg_ );                    \
        _code_                                          \
        __XEOS_Main_PromptSuccess( _status_ )
    
void XEOS_Main( XEOS_InfoRef info )
{
    unsigned int i;
    
    /* Ensures interrupts are disabled, as we are setting up the kernel */
    XEOS_HAL_CPU_DisableInterrupts();
    XEOS_HAL_NMI_Disable();
    
    /* Clears the screen */
    XEOS_Video_SetFG( XEOS_Video_ColorWhite );
    XEOS_Video_SetBG( XEOS_Video_ColorBlack );
    XEOS_Video_Clear();
    
    __XEOS_Main_PrintCopyright();
    XEOS_Video_SetStickyLines( 0 );
    
    __XEOS_Main_PromptWithStatus( "Entering the kernel:", "XEOS-0.2.0", XEOS_Video_ColorGreenLight );
    
    /* Initializes the Interrupt Descriptor Table */
    __KERN_INIT_SECTION
    (
        "Initializing the IDT:",
        NULL,
        {
            XEOS_HAL_IDT_Init();
        }
    );
    
    /*
     * Maps IRQs 0-7 to 0x20-0x27 and IRQs 8-15 to 0x28-0x2F.
     * This will allow us to install the exception handlers, and avoid
     * conflicts with existing IRQs mapping to exceptions.
     */
    __KERN_INIT_SECTION
    (
        "Remapping IRQs:",
        NULL,
        {
            XEOS_HAL_PIC_Remap( 0x20, 0x28 );
        }
    );
    
    /* Installs the exception handlers */
    __KERN_INIT_SECTION
    (
        "Installing the exception handlers:",
        NULL,
        {
            for( i = 0x00; i < 0x14; i++ )
            {
                XEOS_HAL_IDT_SetISREntry
                (
                    ( uint8_t )i,
                    0x08,
                    XEOS_HAL_IDT_ISREntryTypeInterrupt32,
                    XEOS_HAL_IDT_ISREntryPrivilegeLevelRing0,
                    true,
                    XEOS_ISR_Exception
                );
            }
        }
    );
    
    /* Installs the IRQ handlers */
    __KERN_INIT_SECTION
    (
        "Installing the IRQs handlers:",
        NULL,
        {
            for( i = 0x20; i < 0x2F; i++ )
            {
                XEOS_HAL_IDT_SetISREntry
                (
                    ( uint8_t )i,
                    0x08,
                    XEOS_HAL_IDT_ISREntryTypeInterrupt32,
                    XEOS_HAL_IDT_ISREntryPrivilegeLevelRing0,
                    true,
                    XEOS_ISR_IRQ
                );
            }
        }
    );
    
    /* Installs the system call ISR */
    __KERN_INIT_SECTION
    (
        "Registering the system call ISR:",
        NULL,
        {
            XEOS_HAL_IDT_SetISREntry
            (
                0x80,
                0x08,
                XEOS_HAL_IDT_ISREntryTypeInterrupt32,
                XEOS_HAL_IDT_ISREntryPrivilegeLevelRing0,
                true,
                XEOS_ISR_SysCall
            );
        }
    );
    
    /* Installs the new Interrupt Descriptor Table */
    __KERN_INIT_SECTION
    (
        "Activating the IDT:",
        NULL,
        {
        XEOS_HAL_IDT_Reload();
        }
    );
    
    /* System timer IRQ */
    __KERN_INIT_SECTION
    (
        "Registering the system timer IRQ:",
        "IRQ:0",
        {
            XEOS_IRQ_AddIRQHandler( XEOS_HAL_PIC_IRQ0, XEOS_IRQ_SystemTimer );
            XEOS_HAL_PIC_UnmaskIRQLine( XEOS_HAL_PIC_IRQ0 );
        }
    );
    
    /* Keyboard IRQ */
    __KERN_INIT_SECTION
    (
        "Registering the keyboard IRQ:",
        "IRQ:1",
        {
            XEOS_IRQ_AddIRQHandler( XEOS_HAL_PIC_IRQ1, XEOS_IRQ_Keyboard );
            XEOS_HAL_PIC_UnmaskIRQLine( XEOS_HAL_PIC_IRQ1 );
            
            /* Only translated scan-code set 2 is supported */
            if( XEOS_HAL_Keyboard_GetScanCodeSet() != XEOS_HAL_Keyboard_ScanCodeSet2 )
            {
                __XEOS_Main_PromptFailure( "IRQ:1 - FAIL" );
                __XEOS_Main_FatalError();
            }
        }
    );
    
    /* RTC IRQ */
    __KERN_INIT_SECTION
    (
        "Registering the RTC IRQ:",
        "IRQ:8",
        {
            XEOS_IRQ_AddIRQHandler( XEOS_HAL_PIC_IRQ8, XEOS_IRQ_RealTimeClock );
            XEOS_HAL_PIC_UnmaskIRQLine( XEOS_HAL_PIC_IRQ8 );
            
            /*
             * Ensures we get RTC interrupts at a frequency of 1024 hertz
             * The RTC runs at 32'768 hertz. The frequency is computed as follow:
             * 
             * frequency =  32768 >> ( rate - 1 )
             * 
             * So for a frequency of 1024 hertz, the rate needs to be 6:
             * 
             * 32768 >> 5 = 1024
             */
            XEOS_HAL_RTC_SetRate( 6 );
        }
    );
    
    /* (Re)enables the interrupts (standard, NMI and RTC) */
    __KERN_INIT_SECTION
    (
        "Activating all interrupts:",
        NULL,
        {
            XEOS_HAL_RTC_EnablePeriodicInterrupts();
            XEOS_HAL_CPU_EnableInterrupts();
            XEOS_HAL_NMI_Enable();
        }
    );
    
    /* Makes sur the system time is initialized */
    __KERN_INIT_SECTION
    (
        "Getting the system time:",
        NULL,
        {
            while( XEOS_System_GetTime() == 0 )
            {
                __NOP;
            }
        }
    );
    
    __XEOS_Main_PrintInfoLine( "System time:  %lu", XEOS_System_GetTime() );
    
    {
        const char * cpuVendorID;
        const char * cpuBrandName;
        
        /* Gets CPU informations */
        __KERN_INIT_SECTION
        (
            "Getting CPU informations:",
            NULL,
            {
                cpuVendorID  = XEOS_HAL_CPU_GetVendorID();
                cpuBrandName = XEOS_HAL_CPU_GetBrandName();
            }
        );
        
        __XEOS_Main_PrintInfoLine( "CPU vendor:   %s", cpuVendorID );
        __XEOS_Main_PrintInfoLine( "CPU brand:    %s", cpuBrandName );
    }
    
    /* Initializes the physical memory system */
    __KERN_INIT_SECTION
    (
        "Initializing the physical memory allocator:",
        NULL,
        {
            XEOS_Mem_Initialize( XEOS_Info_GetMemory( info ), __XEOS_Main_PrintExternalInfoLine );
        }
    );
    
    /* Initializes the system map */
    __KERN_INIT_SECTION
    (
        "Creating the system memory map:",
        NULL,
        {
            XEOS_VM_SystemMapInitialize( __XEOS_Main_PrintExternalInfoLine );
        }
    );
    
    {
        __block int ii;
        void ( ^ b )( void );
        
        
        
        ii = 42;
        
        b = ^( void )
        {
            XEOS_Video_Printf( "%i\n", ii );
            
            ii = 13;
        };
        
        b();
        
        XEOS_Video_Printf( "%i\n", ii );
        
    }
    
    /* Initialize the ACPICA subsystem */
    __KERN_INIT_SECTION
    (
        "Initializing the ACPI subsystem:",
        NULL,
        {
            ACPI_STATUS status;
            
            ACPI_SetLoggingFunction( __XEOS_Main_VPrintExternalInfoLine );
            ACPI_EnableLogging();
            
            status = AcpiInitializeSubsystem();
            
            if( ACPI_FAILURE( status ) )
            {
                __XEOS_Main_PromptFailure( NULL );
                __XEOS_Main_FatalError();
            }
            
            /* Initialize the ACPICA Table Manager and get all ACPI tables */
            status = AcpiInitializeTables( NULL, 16, false );
            
            if( ACPI_FAILURE( status ) )
            {
                __XEOS_Main_PromptFailure( NULL );
                __XEOS_Main_FatalError();
            }
            
            /* Create the ACPI namespace from ACPI tables */
            status = AcpiLoadTables();
            
            if( ACPI_FAILURE( status ) )
            {
                __XEOS_Main_PromptFailure( NULL );
                __XEOS_Main_FatalError();
            }
            
            /* Note: local handlers should be installed here */
            
            /* Initialize the ACPI hardware */
            status = AcpiEnableSubsystem( ACPI_FULL_INITIALIZATION );
            
            if( ACPI_FAILURE( status ) )
            {
                __XEOS_Main_PromptFailure( NULL );
                __XEOS_Main_FatalError();
            }
            
            /* Complete the ACPI namespace object initialization */
            status = AcpiInitializeObjects( ACPI_FULL_INITIALIZATION );
            
            if( ACPI_FAILURE( status ) )
            {
                __XEOS_Main_PromptFailure( NULL );
                __XEOS_Main_FatalError();
            }
        }
    );
    
    for( ; ; )
    {
        __NOP;
    }
}
