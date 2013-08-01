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
 * @file            XEOS_Mem_Initialize.c
 * @author          Jean-David Gadina
 * @copyright       (c) 2010-2013, Jean-David Gadina - www.xs-labs.com
 */

#include <mem.h>
#include <__private/mem.h>
#include <stdlib.h>
#include <string.h>

void XEOS_Mem_Initialize( XEOS_Info_MemoryRef memory, int ( * outputHandler )( const char *, ... ) )
{
    uint64_t                    totalMemoryBytes;
    uint64_t                    zonesMemory;
    uint64_t                    kernelStart;
    uint64_t                    kernelEnd;
    uint64_t                    zonesAddress;
    uint64_t                    pageAddress;
    XEOS_Info_MemoryEntryRef    memoryEntry;
    XEOS_Info_MemoryEntryType   memoryType;
    uint64_t                    memoryLength;
    uint64_t                    memoryStart;
    uint64_t                    memoryEnd;
    uint64_t                    i;
    uint64_t                    j;
    XEOS_Mem_ZoneRef            zone;
    XEOS_Mem_ZoneRef            previousZone;
    uint8_t                   * pages;
    
    /* Gets the total amount of physical memory */
    totalMemoryBytes = XEOS_Info_MemoryGetTotalBytes( memory );
    
    /* Memory needed to store memory zones informations */
    zonesMemory  = XEOS_Info_MemoryGetNumberOfEntries( memory ) * sizeof( struct __XEOS_Mem_Zone );
    zonesMemory += ( uint64_t )( totalMemoryBytes / 0x1000 );
    
    /* Kernel location */
    kernelStart      = ( uint64_t )XEOS_Info_GetKernelStartAddress();
    kernelEnd        = ( uint64_t )XEOS_Info_GetKernelEndAddress();
    kernelEnd       &= UINT64_MAX - 0x0FFF;
    kernelEnd       += 0x1000;
    kernelEnd       -= 1;
    zonesAddress     = 0;
    
    /* Process each memory region to find room for the memory zones */
    for( i = 0; i < XEOS_Info_MemoryGetNumberOfEntries( memory ); i++ )
    {
        /* Gets informations about the current memory region */
        memoryEntry     = XEOS_Info_MemoryGetEntryAtIndex( memory, ( unsigned int )i );
        memoryLength    = XEOS_Info_MemoryEntryGetLength( memoryEntry );
        memoryStart     = XEOS_Info_MemoryEntryGetAddress( memoryEntry );
        memoryEnd       = ( memoryStart + memoryLength ) - 1;
        memoryType      = XEOS_Info_MemoryEntryGetType( memoryEntry );
        
        if( outputHandler != NULL )
        {
            if( memoryLength == 0 )
            {
                continue;
            }
            
            outputHandler( "%016#llX -> %016#llX - ", memoryStart, ( memoryStart + memoryLength ) - 1 );
            
            switch( memoryType )
            {
                case XEOS_Info_MemoryEntryTypeUnknown:          outputHandler( "Unknown:  " ); break;
                case XEOS_Info_MemoryEntryTypeUsable:           outputHandler( "Usable:   " ); break;
                case XEOS_Info_MemoryEntryTypeReserved:         outputHandler( "Reserved: " ); break;
                case XEOS_Info_MemoryEntryTypeACPIReclaimable:  outputHandler( "ACPI:     " ); break;
                case XEOS_Info_MemoryEntryTypeACPINVS:          outputHandler( "ACPI NVS: " ); break;
                case XEOS_Info_MemoryEntryTypeBad:              outputHandler( "Bad:      " ); break;
            }
            
            if( memoryLength >= 0x100000 )
            {
                outputHandler( "%9llu MB\n", ( ( memoryLength / 1024 ) / 1024 ) );
            }
            else
            {
                outputHandler( "%9llu B\n", memoryLength );
            }
        }
        
        /* Only consider usable memory */
        if( memoryType != XEOS_Info_MemoryEntryTypeUsable )
        {
            continue;
        }
        
        /* Makes sure the memory area address is aligned on 4 KB */
        if( ( memoryStart & 0xFFF ) != 0 )
        {
            memoryStart &= UINTPTR_MAX - 0x0FFF;
            memoryStart += 0x1000;
        }
        
        /* Not enough memory for the system map */
        if( memoryLength < zonesMemory )
        {
            continue;
        }
        
        /*
         * The second stage bootloader only maps the first 12 MB of memory
         * (0x300000000), so the system map needs to be contained in those
         * 12 first MB, otherwise we'll just page fault trying to write the
         * page tables in a still un-mapped memory area.
         */
        if( memoryStart >= 0x300000000 || ( memoryStart + zonesMemory ) >= 0x300000000 )
        {
            break;
        }
        
        /* Found a suitable place */
        if( memoryStart > kernelEnd )
        {
            zonesAddress = memoryStart;
            break;
        }
        
        /* Found a suitable place */
        if( memoryEnd > kernelEnd && ( memoryEnd - kernelEnd ) >= zonesMemory )
        {
            zonesAddress = kernelEnd + 1;
        }
    }
    
    /* Checks if we have an address in which to store the memory zones */
    if( zonesAddress > 0 )
    {
        /* Clears the memory area */
        memset( ( void * )zonesAddress, 0, ( size_t )zonesMemory );
        
        zone                    = NULL;
        previousZone            = NULL;
        pageAddress             = 0;
        __XEOS_Mem_Zones        = ( struct __XEOS_Mem_Zone * )zonesAddress;
        __XEOS_Mem_ZoneCount    = 0;
        
        /* Process each memory region */
        for( i = 0; i < XEOS_Info_MemoryGetNumberOfEntries( memory ); i++ )
        {
            /* Gets informations about the current memory region */
            memoryEntry     = XEOS_Info_MemoryGetEntryAtIndex( memory, ( unsigned int )i );
            memoryLength    = XEOS_Info_MemoryEntryGetLength( memoryEntry );
            memoryStart     = XEOS_Info_MemoryEntryGetAddress( memoryEntry );
            memoryEnd       = ( memoryStart + memoryLength ) - 1;
            memoryType      = XEOS_Info_MemoryEntryGetType( memoryEntry );
            
            zone = ( XEOS_Mem_ZoneRef )zonesAddress;
            
            __XEOS_Mem_ZoneCount++;
            
            if( previousZone != NULL )
            {
                previousZone->next = zone;
            }
            
            zone->base    = ( void * )memoryStart;
            zone->type    = ( XEOS_Mem_ZoneType )memoryType;
            zone->length  = memoryLength;
            pageAddress   = ( uint64_t )( zone->base );
            
            if( memoryLength > 0x1000 )
            {
                zone->pageCount = memoryLength / 0x1000;
                pages           = zone->pages;
                
                for( j = 0; j < XEOS_Mem_ZoneGetPageCount( zone ); j++ )
                {
                    if( memoryType == XEOS_Info_MemoryEntryTypeUsable && pageAddress >= ( zonesAddress + zonesMemory ) )
                    {
                        pages[ j ] = 0x01;
                        
                        zone->freePageCount++;
                    }
                    
                    pageAddress += 0x1000;
                }
            }
            
            previousZone  = zone;
            zonesAddress += sizeof( struct __XEOS_Mem_Zone );
            zonesAddress += zone->pageCount;
        }
    }
}
