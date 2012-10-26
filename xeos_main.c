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

#define XEOS_CODE_SEGMENT         0x08
#define XEOS_SYSCALL_INTERRUPT    0x20
#define XEOS_INTERRUPT_FLAGS      HAL_IDT_FLAG_PRESENT | HAL_IDT_FLAG_32BITS

#define XEOS_HR                   "        --------------------------------------------------------------------"

void xeos_main( void );
void xeos_main( void )
{
    hal_smbios_table_entry     * smbios;
    hal_smbios_bios_infos      * infos_bios;
    hal_smbios_system_infos    * infos_sys;
    hal_smbios_processor_infos * infos_cpu;
    
    xeos_video_set_fg( XEOS_VIDEO_COLOR_WHITE );
    xeos_video_set_bg( XEOS_VIDEO_COLOR_LIGHTBLUE );
    xeos_video_clear();
    
    xeos_video_print
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
    
    xeos_video_prompt( "Entering the XEOS kernel:\n" XEOS_HR );
    xeos_video_print
    (
        "        $Revision$\n"
        "        $Date$\n\n"
    );
    
    xeos_video_prompt( "Initializing the IDT (Interrupt Descriptor Table)..." );
    
    hal_idt_init( 0x08, xeos_int_default_handler );
    
    xeos_video_prompt( "Registering the exception handlers..." );
    
    hal_idt_set_descriptor( HAL_INT_DIVIDE_ERROR,                   xeos_int_divide_error,                   XEOS_CODE_SEGMENT, XEOS_INTERRUPT_FLAGS );
    hal_idt_set_descriptor( HAL_INT_DEBUG_EXCEPTION,                xeos_int_debug_exception,                XEOS_CODE_SEGMENT, XEOS_INTERRUPT_FLAGS );
    hal_idt_set_descriptor( HAL_INT_NMI_INTERRUPT,                  xeos_int_nmi_interrupt,                  XEOS_CODE_SEGMENT, XEOS_INTERRUPT_FLAGS );
    hal_idt_set_descriptor( HAL_INT_BREAKPOINT_EXCEPTION,           xeos_int_breakpoint_exception,           XEOS_CODE_SEGMENT, XEOS_INTERRUPT_FLAGS );
    hal_idt_set_descriptor( HAL_INT_OVERFLOW_EXCEPTION,             xeos_int_overflow_exception,             XEOS_CODE_SEGMENT, XEOS_INTERRUPT_FLAGS );
    hal_idt_set_descriptor( HAL_INT_BOUND_RANGE_EXCEEDED_EXCEPTION, xeos_int_bound_range_exceeded_exception, XEOS_CODE_SEGMENT, XEOS_INTERRUPT_FLAGS );
    hal_idt_set_descriptor( HAL_INT_INVALID_OPCODE_EXCEPTION,       xeos_int_invalid_opcode_exception,       XEOS_CODE_SEGMENT, XEOS_INTERRUPT_FLAGS );
    hal_idt_set_descriptor( HAL_INT_DEVICE_NOT_AVAILABLE_EXCEPTION, xeos_int_device_not_available_exception, XEOS_CODE_SEGMENT, XEOS_INTERRUPT_FLAGS );
    hal_idt_set_descriptor( HAL_INT_DOUBLE_FAULT_EXCEPTION,         xeos_int_double_fault_exception,         XEOS_CODE_SEGMENT, XEOS_INTERRUPT_FLAGS );
    hal_idt_set_descriptor( HAL_INT_COPROCESSOR_SEGMENT_OVERRUN,    xeos_int_coprocessor_segment_overrun,    XEOS_CODE_SEGMENT, XEOS_INTERRUPT_FLAGS );
    hal_idt_set_descriptor( HAL_INT_INVALID_TSS_EXCEPTION,          xeos_int_invalid_tss_exception,          XEOS_CODE_SEGMENT, XEOS_INTERRUPT_FLAGS );
    hal_idt_set_descriptor( HAL_INT_SEGMENT_NOT_PRESENT,            xeos_int_segment_not_present,            XEOS_CODE_SEGMENT, XEOS_INTERRUPT_FLAGS );
    hal_idt_set_descriptor( HAL_INT_STACK_FAULT_EXCEPTION,          xeos_int_stack_fault_exception,          XEOS_CODE_SEGMENT, XEOS_INTERRUPT_FLAGS );
    hal_idt_set_descriptor( HAL_INT_GENERAL_PROTECTION_EXCEPTION,   xeos_int_general_protection_exception,   XEOS_CODE_SEGMENT, XEOS_INTERRUPT_FLAGS );
    hal_idt_set_descriptor( HAL_INT_PAGE_FAULT_EXCEPTION,           xeos_int_page_fault_exception,           XEOS_CODE_SEGMENT, XEOS_INTERRUPT_FLAGS );
    hal_idt_set_descriptor( HAL_INT_FLOATING_POINT_ERROR_EXCEPTION, xeos_int_floating_point_error_exception, XEOS_CODE_SEGMENT, XEOS_INTERRUPT_FLAGS );
    hal_idt_set_descriptor( HAL_INT_ALIGNMENT_CHECK_EXCEPTION,      xeos_int_alignment_check_exception,      XEOS_CODE_SEGMENT, XEOS_INTERRUPT_FLAGS );
    hal_idt_set_descriptor( HAL_INT_MACHINE_CHECK_EXCEPTION,        xeos_int_machine_check_exception,        XEOS_CODE_SEGMENT, XEOS_INTERRUPT_FLAGS );
    hal_idt_set_descriptor( HAL_INT_SIMD_FLOATING_POINT_EXCEPTION,  xeos_int_simd_floating_point_exception,  XEOS_CODE_SEGMENT, XEOS_INTERRUPT_FLAGS );
    
    xeos_video_prompt( "Registering the system calls..." );
    
    hal_idt_set_descriptor( XEOS_SYSCALL_INTERRUPT, xeos_int_syscall, XEOS_CODE_SEGMENT, XEOS_INTERRUPT_FLAGS );
    
    xeos_video_print( "\n" );
    xeos_video_prompt( "Locating the SMBIOS entry point:\n" XEOS_HR );
        
    if( ( smbios = hal_smbios_find_entry() ) == NULL )
    {
        /* Fatal error */
        
        xeos_video_printf( "        SMBIOS entry point not found!" );
        for( ; ; );
    }
    
    xeos_video_printf
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
    
    xeos_video_print( "\n" );
    xeos_video_prompt( "Getting BIOS informations:\n" XEOS_HR );
    
    infos_bios = ( hal_smbios_bios_infos * )hal_smbios_get_infos( smbios, HAL_SMBIOS_STRUCT_BIOS_INFORMATION );
    
    xeos_video_printf
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
        xeos_video_printf
        (
            "        System BIOS version: %i.%i\n",
            infos_bios->release_major,
            infos_bios->release_minor
        );
    }
    else
    {
        xeos_video_print( "        System BIOS version: Unknown\n" );
    }
    
    if( infos_bios->embedded_controller_firmware_major < 0xFF )
    {
        xeos_video_printf
        (
            "        ECF version:         %i.%i\n",
            infos_bios->embedded_controller_firmware_major,
            infos_bios->embedded_controller_firmware_minor
        );
    }
    else
    {
        xeos_video_print( "        ECF version:         Unknown\n" );
    }
    
    xeos_video_print( "\n" );
    xeos_video_prompt( "Getting system informations:\n" XEOS_HR );
    
    infos_sys = ( hal_smbios_system_infos * )hal_smbios_get_infos( smbios, HAL_SMBIOS_STRUCT_SYSTEM_INFORMATION );
    
    xeos_video_printf
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
    
    xeos_video_print( "\n" );
    xeos_video_prompt( "Getting CPU informations:\n" XEOS_HR );
    
    infos_cpu = ( hal_smbios_processor_infos * )hal_smbios_get_infos( smbios, HAL_SMBIOS_STRUCT_PROCESSOR_INFORMATION );
    
    xeos_video_printf
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
