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
 * @header          proc.h
 * @author          Jean-David Gadina
 * @copyright       (c) 2010-2013, Jean-David Gadina - www.xs-labs.com
 */

#ifndef __XEOS_PROC_H__
#define __XEOS_PROC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <xeos/macros.h>
#include <xeos/info.h>
#include <stdbool.h>

/*!
 * @typedef         XEOS_Mem_ZoneType
 * @abstract        Type of a memory entry
 * @constant        XEOS_Mem_ZoneTypeUnknown            Unknown entry type
 * @constant        XEOS_Mem_ZoneTypeUsable             Usable (free) memory region
 * @constant        XEOS_Mem_ZoneTypeReserved           Reserved (unusable) memory region
 * @constant        XEOS_Mem_ZoneTypeACPIReclaimable    ACPI reclaimable memory region
 * @constant        XEOS_Mem_ZoneTypeACPINVS            ACPI NVS memory regions
 * @constant        XEOS_Mem_ZoneTypeBad                Bad memory region
 */
typedef enum
{
    XEOS_Mem_ZoneTypeUnknown            = XEOS_Info_MemoryEntryTypeUnknown,
    XEOS_Mem_ZoneTypeUsable             = XEOS_Info_MemoryEntryTypeUsable,
    XEOS_Mem_ZoneTypeReserved           = XEOS_Info_MemoryEntryTypeReserved,
    XEOS_Mem_ZoneTypeACPIReclaimable    = XEOS_Info_MemoryEntryTypeACPIReclaimable,
    XEOS_Mem_ZoneTypeACPINVS            = XEOS_Info_MemoryEntryTypeACPINVS,
    XEOS_Mem_ZoneTypeBad                = XEOS_Info_MemoryEntryTypeBad
}
XEOS_Mem_ZoneType;

typedef struct __XEOS_Mem_Zone    * XEOS_Mem_ZoneRef;

void                XEOS_Mem_Initialize( XEOS_Info_MemoryRef memory, int ( * outputHandler )( const char *, ... ) );
XEOS_Mem_ZoneRef    XEOS_Mem_GetZoneAtIndex( unsigned int index );
unsigned int        XEOS_Mem_GetNumberOfZones( void );

void              * XEOS_Mem_AllocPage( void );
void              * XEOS_Mem_AllocPages( unsigned int n );
void                XEOS_Mem_FreePage( void * address );
void                XEOS_Mem_FreePages( void * address, unsigned int n );

XEOS_Mem_ZoneType   XEOS_Mem_ZoneGetType( XEOS_Mem_ZoneRef object );
void              * XEOS_Mem_ZoneGetAddress( XEOS_Mem_ZoneRef object );
uint64_t            XEOS_Mem_ZoneGetLength( XEOS_Mem_ZoneRef object );
XEOS_Mem_ZoneRef    XEOS_Mem_ZoneGetNext( XEOS_Mem_ZoneRef object );
uint64_t            XEOS_Mem_ZoneGetPageCount( XEOS_Mem_ZoneRef object );
uint64_t            XEOS_Mem_ZoneGetFreePageCount( XEOS_Mem_ZoneRef object );
uint8_t           * XEOS_Mem_ZoneGetPages( XEOS_Mem_ZoneRef object );

uint64_t            XEOS_Mem_GetTotalBytes( void );

#ifdef __cplusplus
}
#endif

#endif /* __XEOS_PROC_H__ */
