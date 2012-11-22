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
 * @header          info.h
 * @author          Jean-David Gadina
 * @copyright       (c) 2010-2012, Jean-David Gadina <macmade@eosgarden.com>
 */

#ifndef __XEOS_INFO_H__
#define __XEOS_INFO_H__
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/*!
 * @typedef         XEOS_InfoRef
 * @abstract        Opaque type for the info object (passed by the bootloader)
 */
typedef struct __XEOS_Info * XEOS_InfoRef;

/*!
 * @typedef         XEOS_Info_MemoryRef
 * @abstract        Opaque type for the memory info object
 */
typedef struct __XEOS_Info_Memory * XEOS_Info_MemoryRef;

/*!
 * @typedef         XEOS_Info_MemoryEntryRef
 * @abstract        Opaque type for a memory entry info object
 */
typedef struct __XEOS_Info_MemoryEntry * XEOS_Info_MemoryEntryRef;

/*!
 * @typedef         XEOS_Info_MemoryEntryType
 * @abstract        Type of a memory entry
 * @constant        XEOS_Info_MemoryEntryTypeUnknown            Unknown entry type
 * @constant        XEOS_Info_MemoryEntryTypeUsable             Usable (free) memory region
 * @constant        XEOS_Info_MemoryEntryTypeReserved           Reserved (unusable) memory region
 * @constant        XEOS_Info_MemoryEntryTypeACPIReclaimable    ACPI reclaimable memory region
 * @constant        XEOS_Info_MemoryEntryTypeACPINVS            ACPI NVS memory regions
 * @constant        XEOS_Info_MemoryEntryTypeBad                Bad memory region
 */
typedef enum
{
    XEOS_Info_MemoryEntryTypeUnknown            = 0x00,
    XEOS_Info_MemoryEntryTypeUsable             = 0x01,
    XEOS_Info_MemoryEntryTypeReserved           = 0x02,
    XEOS_Info_MemoryEntryTypeACPIReclaimable    = 0x03,
    XEOS_Info_MemoryEntryTypeACPINVS            = 0x04,
    XEOS_Info_MemoryEntryTypeBad                = 0x05
}
XEOS_Info_MemoryEntryType;

/*!
 * @function        XEOS_Info_GetMemory
 * @abstract        Gets the memory info object
 * @param           info        The info object
 * @result          The memory info object
 */
XEOS_Info_MemoryRef XEOS_Info_GetMemory( XEOS_InfoRef info );

/*!
 * @function        XEOS_Info_MemoryGetTotalBytes
 * @abstract        Gets the number of memory bytes available on the system
 * @param           memory      The memory info object
 * @result          The number of memory bytes available on the system
 */
uint64_t XEOS_Info_MemoryGetTotalBytes( XEOS_Info_MemoryRef memory );

/*!
 * @function        XEOS_Info_MemoryGetNumberOfEntries
 * @abstract        Gets the number of memory info entries
 * @param           memory      The memory info object
 * @result          The number of memory info entries
 */
unsigned int XEOS_Info_MemoryGetNumberOfEntries( XEOS_Info_MemoryRef memory );

/*!
 * @function        XEOS_Info_MemoryGetEntryAtIndex
 * @abstract        Gets a specific memory entry info object
 * @param           memory      The memory info object
 * @param           index       The index of the memory info object
 * @result          The memory entry info object
 */
XEOS_Info_MemoryEntryRef XEOS_Info_MemoryGetEntryAtIndex( XEOS_Info_MemoryRef memory, unsigned int index );

/*!
 * @function        XEOS_Info_MemoryEntryGetAddress
 * @abstract        Gets the start address of a memory entry info entry
 * @param           entry       The memory entry info object
 * @result          The start address of the memory entry info object
 */
uint64_t XEOS_Info_MemoryEntryGetAddress( XEOS_Info_MemoryEntryRef entry );

/*!
 * @function        XEOS_Info_MemoryEntryGetAddress
 * @abstract        Gets the length (in bytes) of a memory entry info entry
 * @param           entry       The memory entry info object
 * @result          The length (in bytes) of the memory entry info entry
 */
uint64_t XEOS_Info_MemoryEntryGetLength( XEOS_Info_MemoryEntryRef entry );

/*!
 * @function        XEOS_Info_MemoryEntryGetAddress
 * @abstract        Gets the type of a memory entry info entry
 * @param           entry       The memory entry info object
 * @result          The type of the memory entry info object
 */
XEOS_Info_MemoryEntryType XEOS_Info_MemoryEntryGetType( XEOS_Info_MemoryEntryRef entry );

/*!
 * @function        XEOS_Info_GetKernelStartAddress
 * @abstract        Gets the start address of the kernel
 * @result          The start address of the kernel
 */
uintptr_t XEOS_Info_GetKernelStartAddress( void );

/*!
 * @function        XEOS_Info_GetKernelEndAddress
 * @abstract        Gets the end address of the kernel
 * @result          The end address of the kernel
 */
uintptr_t XEOS_Info_GetKernelEndAddress( void );

/*!
 * @function        XEOS_Info_GetKernelTextSectionStartAddress
 * @abstract        Gets the start address of the .text kernel section
 * @result          The start address of the .text kernel kernel
 */
uintptr_t XEOS_Info_GetKernelTextSectionStartAddress( void );

/*!
 * @function        XEOS_Info_GetKernelTextSectionEndAddress
 * @abstract        Gets the end address of the .text kernel section
 * @result          The end address of the .text kernel kernel
 */
uintptr_t XEOS_Info_GetKernelTextSectionEndAddress( void );

/*!
 * @function        XEOS_Info_GetKernelRODataSectionStartAddress
 * @abstract        Gets the start address of the .rodata kernel section
 * @result          The start address of the .rodata kernel kernel
 */
uintptr_t XEOS_Info_GetKernelRODataSectionStartAddress( void );

/*!
 * @function        XEOS_Info_GetKernelRODataSectionEndAddress
 * @abstract        Gets the end address of the .rodata kernel section
 * @result          The end address of the .rodata kernel kernel
 */
uintptr_t XEOS_Info_GetKernelRODataSectionEndAddress( void );

/*!
 * @function        XEOS_Info_GetKernelDataSectionStartAddress
 * @abstract        Gets the start address of the .data kernel section
 * @result          The start address of the .data kernel kernel
 */
uintptr_t XEOS_Info_GetKernelDataSectionStartAddress( void );

/*!
 * @function        XEOS_Info_GetKernelDataSectionEndAddress
 * @abstract        Gets the end address of the .data kernel section
 * @result          The end address of the .data kernel kernel
 */
uintptr_t XEOS_Info_GetKernelDataSectionEndAddress( void );

/*!
 * @function        XEOS_Info_GetKernelBSSSectionStartAddress
 * @abstract        Gets the start address of the .bss kernel section
 * @result          The start address of the .bss kernel kernel
 */
uintptr_t XEOS_Info_GetKernelBSSSectionStartAddress( void );

/*!
 * @function        XEOS_Info_GetKernelBSSSectionEndAddress
 * @abstract        Gets the end address of the .bss kernel section
 * @result          The end address of the .bss kernel kernel
 */
uintptr_t XEOS_Info_GetKernelBSSSectionEndAddress( void );

#ifdef __cplusplus
}
#endif

#endif /* __XEOS_INFO_H__ */
