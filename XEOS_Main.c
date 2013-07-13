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
 * @file            XEOS_Main.c
 * @author          Jean-David Gadina
 * @copyright       (c) 2010-2012, Jean-David Gadina - www.xs-labs.com
 */

#include "xeos/video.h"
#include "xeos/system.h"
#include "xeos/mem.h"
#include "xeos/vm.h"
#include "xeos/hal.h"
#include "xeos/isr.h"
#include "xeos/irq.h"
#include "xeos/info.h"
#include <sys/syscall.h>
#include <stdlib.h>
#include <string.h>
#include <acpi/acpica.h>

void __XEOS_Main_PrintCopyright( void );
void __XEOS_Main_PromptWithStatus( const char * message, const char * status, XEOS_Video_Color statusColor );
void __XEOS_Main_PrintInfoLine( const char * format, ... );
void __XEOS_Main_Prompt( const char * message );
void __XEOS_Main_PromptSuccess( const char * successMessage );
void __XEOS_Main_PromptFailure( const char * failureMessage );

void XEOS_Main( XEOS_InfoRef info ) XEOS_NORETURN_ATTRIBUTE;
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
    __XEOS_Main_PromptWithStatus( "Entering the kernel:", "XEOS-0.2.0", XEOS_Video_ColorGreenLight );
    __XEOS_Main_Prompt( "Initializing the IDT:" );
    
    /* Initializes the Interrupt Descriptor Table */
    {
        XEOS_HAL_IDT_Init();
        __XEOS_Main_PromptSuccess( NULL );
    }
    
    /*
     * Maps IRQs 0-7 to 0x20-0x27 and IRQs 8-15 to 0x28-0x2F.
     * This will allow us to install the exception handlers, and avoid
     * conflicts with existing IRQs mapping to exceptions.
     */
    {
        __XEOS_Main_Prompt( "Remapping IRQs:" );
        XEOS_HAL_PIC_Remap( 0x20, 0x28 );
        __XEOS_Main_PromptSuccess( NULL );
    }
    
    
    /* Installs the exception handlers */
    {
        __XEOS_Main_Prompt( "Installing the exception handlers:" );
        
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
        
        __XEOS_Main_PromptSuccess( NULL );
    }
    
    /* Installs the IRQ handlers */
    {
        __XEOS_Main_Prompt( "Installing the IRQs handlers:" );
        
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
        
        __XEOS_Main_PromptSuccess( NULL );
    }
    
    /* Installs the system call ISR */
    {
        __XEOS_Main_Prompt( "Registering the system call ISR:" );
        
        XEOS_HAL_IDT_SetISREntry
        (
            0x80,
            0x08,
            XEOS_HAL_IDT_ISREntryTypeInterrupt32,
            XEOS_HAL_IDT_ISREntryPrivilegeLevelRing0,
            true,
            XEOS_ISR_SysCall
        );
        
        __XEOS_Main_PromptSuccess( NULL );
    }
    
    /* Installs the new Interrupt Descriptor Table */
    {
        __XEOS_Main_Prompt( "Activating the IDT:" );
        XEOS_HAL_IDT_Reload();
        __XEOS_Main_PromptSuccess( NULL );
    }
    
    /* System timer IRQ */
    {
        __XEOS_Main_Prompt( "Registering the system timer IRQ:" );
        XEOS_IRQ_AddIRQHandler( XEOS_HAL_PIC_IRQ0, XEOS_IRQ_SystemTimer );
        XEOS_HAL_PIC_UnmaskIRQLine( XEOS_HAL_PIC_IRQ0 );
        __XEOS_Main_PromptSuccess( "IRQ:0" );
    }
    
    /* Keyboard IRQ */
    {
        __XEOS_Main_Prompt( "Registering the keyboard IRQ:" );
        XEOS_IRQ_AddIRQHandler( XEOS_HAL_PIC_IRQ0, XEOS_IRQ_Keyboard );
        XEOS_HAL_PIC_UnmaskIRQLine( XEOS_HAL_PIC_IRQ1 );
        
        /* Only translated scan-code set 2 is supported */
        if( XEOS_HAL_Keyboard_GetScanCodeSet() != XEOS_HAL_Keyboard_ScanCodeSet2 )
        {
            __XEOS_Main_PromptFailure( "IRQ:1 - FAIL" );
        }
        else
        {
            __XEOS_Main_PromptSuccess( "IRQ:1" );
        }
    }
    
    /* RTC IRQ */
    {
        __XEOS_Main_Prompt( "Registering the RTC IRQ:" );
        XEOS_IRQ_AddIRQHandler( XEOS_HAL_PIC_IRQ0, XEOS_IRQ_RealTimeClock );
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
        
        __XEOS_Main_PromptSuccess( "IRQ:8" );
    }
    
    /* (Re)enables the interrupts (standard, NMI and RTC) */
    {
        __XEOS_Main_Prompt( "Activating all interrupts:" );
        XEOS_HAL_RTC_EnablePeriodicInterrupts();
        XEOS_HAL_CPU_EnableInterrupts();
        XEOS_HAL_NMI_Enable();
        __XEOS_Main_PromptSuccess( NULL );
    }
    
    /* Makes sur the system time is initialized */
    {
        __XEOS_Main_Prompt( "Getting the system time:" );
        
        while( XEOS_System_GetTime() == 0 )
        {
            __asm__
            (
                "nop;nop;nop;nop;nop;\n"
                "nop;nop;nop;nop;nop;\n"
            );
        }
        
        __XEOS_Main_PromptSuccess( NULL );
        __XEOS_Main_PrintInfoLine( "System time: %u", XEOS_System_GetTime() );
    }
    
    {
        const char * cpuVendorID;
        const char * cpuBrandName;
        
        __XEOS_Main_Prompt( "Getting CPU informations:" );
        
        cpuVendorID  = XEOS_HAL_CPU_GetVendorID();
        cpuBrandName = XEOS_HAL_CPU_GetBrandName();
        
        __XEOS_Main_PromptSuccess( NULL );
        
        __XEOS_Main_PrintInfoLine( "CPU vendor: %s", cpuVendorID );
        __XEOS_Main_PrintInfoLine( "CPU brand:  %s", cpuBrandName );
    }
    
    ( void )info;
    
    /* Initializes the physical memory system */
    {
        __XEOS_Main_Prompt( "Initializing the physical memory allocator:" );
        XEOS_Mem_Initialize( XEOS_Info_GetMemory( info ), NULL );
        __XEOS_Main_PromptSuccess( NULL );
    }
    
    /* Initializes the system map */
    {
        __XEOS_Main_Prompt( "Creating the system memory map:" );
        XEOS_VM_SystemMapInitialize( NULL );
        __XEOS_Main_PromptSuccess( NULL );
    }
    
    {
        ACPI_STATUS status;
        
        __XEOS_Main_Prompt( "Initializing the ACPI subsystem:" );
        
        /* Initialize the ACPICA subsystem */
        status = AcpiInitializeSubsystem();
        
        if( ACPI_FAILURE( status ) )
        {
            __XEOS_Main_PromptFailure( NULL );
        }
        else
        {
            /* Initialize the ACPICA Table Manager and get all ACPI tables */
            status = AcpiInitializeTables( NULL, 16, false );
            
            if( ACPI_FAILURE( status ) )
            {
                __XEOS_Main_PromptFailure( NULL );
            }
            else
            {
                /* Create the ACPI namespace from ACPI tables */
                status = AcpiLoadTables();
                
                if( ACPI_FAILURE( status ) )
                {
                    __XEOS_Main_PromptFailure( NULL );
                }
                else
                {
                    /* Note: local handlers should be installed here */
                    
                    /* Initialize the ACPI hardware */
                    status = AcpiEnableSubsystem( ACPI_FULL_INITIALIZATION );
                    
                    if( ACPI_FAILURE( status ) )
                    {
                        __XEOS_Main_PromptFailure( NULL );
                    }
                    else
                    {
                        /* Complete the ACPI namespace object initialization */
                        status = AcpiInitializeObjects( ACPI_FULL_INITIALIZATION );
                        
                        if( ACPI_FAILURE( status ) )
                        {
                            __XEOS_Main_PromptFailure( NULL );
                        }
                        else
                        {
                            __XEOS_Main_PromptSuccess( NULL );
                        }
                    }
                }
            }
        }
    }
    
    for( ; ; )
    {
        __asm__
        (
            "nop;nop;nop;nop;nop;\n"
            "nop;nop;nop;nop;nop;\n"
        );
    }
}
