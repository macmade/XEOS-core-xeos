/*******************************************************************************
 * XEOS - x86 Experimental Operating System
 * 
 * Copyright (C) 2010 Jean-David Gadina (macmade@eosgarden.com)
 * All rights reserved
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 *  -   Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *  -   Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *  -   Neither the name of 'Jean-David Gadina' nor the names of its
 *      contributors may be used to endorse or promote products derived from
 *      this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************/

/* $Id$ */

#include <stdlib.h>
#include <hal/hal.h>
#include "private/video.h"
#include "private/interrupts.h"
#include "system.h"
#include "syscalls.h"

#define KERNEL_CODE_SEGMENT         0x08
#define KERNEL_SYSCALL_INTERRUPT    0x20
#define KERNEL_INTERRUPT_FLAGS      HAL_IDT_FLAG_PRESENT | HAL_IDT_FLAG_32BITS

#define KERNEL_HR                   "        --------------------------------------------------------------------"

void kernel_main( void );
void kernel_main( void )
{
    hal_smbios_table_entry     * smbios;
    hal_smbios_bios_infos      * infos_bios;
    hal_smbios_system_infos    * infos_sys;
    hal_smbios_processor_infos * infos_cpu;
    
    kernel_video_set_fg( KERNEL_VIDEO_COLOR_WHITE );
    kernel_video_set_bg( KERNEL_VIDEO_COLOR_LIGHTBLUE );
    kernel_video_clear();
    
    kernel_video_print
    (
        "\n"
        "    ------------------------------------------------------------------------ \n"
        "   |                                                                        |\n"
        "   |       00000     00000  00000000000  0000000000000  0000000000000       |\n"
        "   |        00000   00000   00000000000  0000000000000  0000000000000       |\n"
        "   |          000000000     000          000       000  000                 |\n"
        "   |           0000000      00000000000  000       000  0000000000000       |\n"
        "   |          000000000     000          000       000            000       |\n"
        "   |        00000   00000   00000000000  0000000000000  0000000000000       |\n"
        "   |       00000     00000  00000000000  0000000000000  0000000000000       |\n"
        "   |                                                                        |\n"
        "   |                XEOS - x86 Experimental Operating System                |\n"
        "   |                                                                        |\n"
        "   |      Copyright (C) 2010 Jean-David Gadina (macmade@eosgarden.com)      |\n"
        "   |                     All rights (& wrongs) reserved                     |\n"
        "   |                                                                        |\n"
        "    ------------------------------------------------------------------------ \n"
        "\n"
    );
    
    kernel_video_prompt( "Entering the XEOS kernel:\n" KERNEL_HR );
    kernel_video_print
    (
        "        $Revision$\n"
        "        $Date$\n\n"
    );
    
    kernel_video_prompt( "Initializing the IDT (Interrupt Descriptor Table)..." );
    
    hal_idt_init( 0x08, kernel_interrupt_default_handler );
    
    kernel_video_prompt( "Registering the exception handlers..." );
    
    hal_idt_set_descriptor( HAL_INT_DIVIDE_ERROR,                   kernel_interrupt_divide_error,                   KERNEL_CODE_SEGMENT, KERNEL_INTERRUPT_FLAGS );
    hal_idt_set_descriptor( HAL_INT_DEBUG_EXCEPTION,                kernel_interrupt_debug_exception,                KERNEL_CODE_SEGMENT, KERNEL_INTERRUPT_FLAGS );
    hal_idt_set_descriptor( HAL_INT_NMI_INTERRUPT,                  kernel_interrupt_nmi_interrupt,                  KERNEL_CODE_SEGMENT, KERNEL_INTERRUPT_FLAGS );
    hal_idt_set_descriptor( HAL_INT_BREAKPOINT_EXCEPTION,           kernel_interrupt_breakpoint_exception,           KERNEL_CODE_SEGMENT, KERNEL_INTERRUPT_FLAGS );
    hal_idt_set_descriptor( HAL_INT_OVERFLOW_EXCEPTION,             kernel_interrupt_overflow_exception,             KERNEL_CODE_SEGMENT, KERNEL_INTERRUPT_FLAGS );
    hal_idt_set_descriptor( HAL_INT_BOUND_RANGE_EXCEEDED_EXCEPTION, kernel_interrupt_bound_range_exceeded_exception, KERNEL_CODE_SEGMENT, KERNEL_INTERRUPT_FLAGS );
    hal_idt_set_descriptor( HAL_INT_INVALID_OPCODE_EXCEPTION,       kernel_interrupt_invalid_opcode_exception,       KERNEL_CODE_SEGMENT, KERNEL_INTERRUPT_FLAGS );
    hal_idt_set_descriptor( HAL_INT_DEVICE_NOT_AVAILABLE_EXCEPTION, kernel_interrupt_device_not_available_exception, KERNEL_CODE_SEGMENT, KERNEL_INTERRUPT_FLAGS );
    hal_idt_set_descriptor( HAL_INT_DOUBLE_FAULT_EXCEPTION,         kernel_interrupt_double_fault_exception,         KERNEL_CODE_SEGMENT, KERNEL_INTERRUPT_FLAGS );
    hal_idt_set_descriptor( HAL_INT_COPROCESSOR_SEGMENT_OVERRUN,    kernel_interrupt_coprocessor_segment_overrun,    KERNEL_CODE_SEGMENT, KERNEL_INTERRUPT_FLAGS );
    hal_idt_set_descriptor( HAL_INT_INVALID_TSS_EXCEPTION,          kernel_interrupt_invalid_tss_exception,          KERNEL_CODE_SEGMENT, KERNEL_INTERRUPT_FLAGS );
    hal_idt_set_descriptor( HAL_INT_SEGMENT_NOT_PRESENT,            kernel_interrupt_segment_not_present,            KERNEL_CODE_SEGMENT, KERNEL_INTERRUPT_FLAGS );
    hal_idt_set_descriptor( HAL_INT_STACK_FAULT_EXCEPTION,          kernel_interrupt_stack_fault_exception,          KERNEL_CODE_SEGMENT, KERNEL_INTERRUPT_FLAGS );
    hal_idt_set_descriptor( HAL_INT_GENERAL_PROTECTION_EXCEPTION,   kernel_interrupt_general_protection_exception,   KERNEL_CODE_SEGMENT, KERNEL_INTERRUPT_FLAGS );
    hal_idt_set_descriptor( HAL_INT_PAGE_FAULT_EXCEPTION,           kernel_interrupt_page_fault_exception,           KERNEL_CODE_SEGMENT, KERNEL_INTERRUPT_FLAGS );
    hal_idt_set_descriptor( HAL_INT_FLOATING_POINT_ERROR_EXCEPTION, kernel_interrupt_floating_point_error_exception, KERNEL_CODE_SEGMENT, KERNEL_INTERRUPT_FLAGS );
    hal_idt_set_descriptor( HAL_INT_ALIGNMENT_CHECK_EXCEPTION,      kernel_interrupt_alignment_check_exception,      KERNEL_CODE_SEGMENT, KERNEL_INTERRUPT_FLAGS );
    hal_idt_set_descriptor( HAL_INT_MACHINE_CHECK_EXCEPTION,        kernel_interrupt_machine_check_exception,        KERNEL_CODE_SEGMENT, KERNEL_INTERRUPT_FLAGS );
    hal_idt_set_descriptor( HAL_INT_SIMD_FLOATING_POINT_EXCEPTION,  kernel_interrupt_simd_floating_point_exception,  KERNEL_CODE_SEGMENT, KERNEL_INTERRUPT_FLAGS );
    
    kernel_video_prompt( "Registering the system calls..." );
    
    hal_idt_set_descriptor( KERNEL_SYSCALL_INTERRUPT, kernel_interrupt_syscall, KERNEL_CODE_SEGMENT, KERNEL_INTERRUPT_FLAGS );
    
    kernel_video_print( "\n" );
    kernel_video_prompt( "Locating the SMBIOS entry point:\n" KERNEL_HR );
        
    if( ( smbios = hal_smbios_find_entry() ) == NULL )
    {
        /* Fatal error */
        
        kernel_video_printf( "        SMBIOS entry point not found!" );
        for( ; ; );
    }
    
    kernel_video_printf
    (
        "        Entry point address:   %p\n"
        "        Number of structures:  %u\n"
        "        Start address:         %p\n"
        "        SMBIOS version:        %u.%u\n",
        smbios,
        smbios->structures_count,
        smbios->structure_table_address,
        ( unsigned int )smbios->version_major,
        ( unsigned int )smbios->version_minor
    );
    
    kernel_video_print( "\n" );
    kernel_video_prompt( "Getting BIOS informations:\n" KERNEL_HR );
    
    infos_bios = ( hal_smbios_bios_infos * )hal_smbios_get_infos( smbios, HAL_SMBIOS_STRUCT_BIOS_INFORMATION );
    
    kernel_video_printf
    (
        "        BIOS vendor:         %s\n"
        "        BIOS version:        %s\n"
        "        BIOS release date:   %s\n",
        ( infos_bios->vendor  == NULL ) ? "Unknown" : infos_bios->vendor,
        ( infos_bios->version == NULL ) ? "Unknown" : infos_bios->version,
        ( infos_bios->date    == NULL ) ? "Unknown" : infos_bios->date
    );
    
    if( infos_bios->release_major < 0xFF )
    {
        kernel_video_printf
        (
            "        System BIOS version: %i.%i\n",
            infos_bios->release_major,
            infos_bios->release_minor
        );
    }
    else
    {
        kernel_video_print( "        System BIOS version: Unknown\n" );
    }
    
    if( infos_bios->embedded_controller_firmware_major < 0xFF )
    {
        kernel_video_printf
        (
            "        ECF version:         %i.%i\n",
            infos_bios->embedded_controller_firmware_major,
            infos_bios->embedded_controller_firmware_minor
        );
    }
    else
    {
        kernel_video_print( "        ECF version:         Unknown\n" );
    }
    
    kernel_video_print( "\n" );
    kernel_video_prompt( "Getting system informations:\n" KERNEL_HR );
    
    infos_sys = ( hal_smbios_system_infos * )hal_smbios_get_infos( smbios, HAL_SMBIOS_STRUCT_SYSTEM_INFORMATION );
    
    kernel_video_printf
    (
        "        Manufacturer:  %s\n"
        "        Product name:  %s\n"
        "        Version:       %s\n"
        "        Serial number: %s\n"
        "        UUID:          %s\n"
        "        Wake-up type:  %s\n"
        "        SKU number:    %s\n"
        "        Family:        %s\n",
        ( infos_sys->manufacturer  == NULL ) ? "Unknown" : infos_sys->manufacturer,
        ( infos_sys->product_name  == NULL ) ? "Unknown" : infos_sys->product_name,
        ( infos_sys->version       == NULL ) ? "Unknown" : infos_sys->version,
        ( infos_sys->serial_number == NULL ) ? "Unknown" : infos_sys->serial_number,
        hal_smbios_uuid_string( &( infos_sys->uuid ) ),
        "Unknown",
        ( infos_sys->sku_number == NULL ) ? "Unknown" : infos_sys->sku_number,
        ( infos_sys->family     == NULL ) ? "Unknown" : infos_sys->family
    );
    
    kernel_video_print( "\n" );
    kernel_video_prompt( "Getting CPU informations:\n" KERNEL_HR );
    
    infos_cpu = ( hal_smbios_processor_infos * )hal_smbios_get_infos( smbios, HAL_SMBIOS_STRUCT_PROCESSOR_INFORMATION );
    
    kernel_video_printf
    (
        "        CPU socket:          %s\n"
        "        CPU type:            %s\n"
        "        CPU family:          %s\n"
        "        CPU manufacturer:    %s\n"
        "        CPU version:         %s\n"
        "        CPU voltage:         %f\n"
        "        CPU serial number:   %s\n"
        "        CPU asset tag:       %s\n"
        "        CPU part number:     %s\n",
        ( infos_cpu->socket == NULL ) ? "Unknown" : infos_cpu->socket,
        hal_smbios_processor_type_string( infos_cpu->type ),
        hal_smbios_processor_family_string( infos_cpu->family ),
        ( infos_cpu->manufacturer == NULL ) ? "Unknown" : infos_cpu->manufacturer,
        ( infos_cpu->version      == NULL ) ? "Unknown" : infos_cpu->version,
        infos_cpu->voltage,
        ( infos_cpu->serial_number == NULL ) ? "Unknown" : infos_cpu->serial_number,
        ( infos_cpu->asset_tag     == NULL ) ? "Unknown" : infos_cpu->asset_tag,
        ( infos_cpu->part_number   == NULL ) ? "Unknown" : infos_cpu->part_number
    );
    
    for( ; ; );
}
