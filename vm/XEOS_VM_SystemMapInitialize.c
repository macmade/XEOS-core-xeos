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
 * @file            XEOS_VM_SystemMap.c
 * @author          Jean-David Gadina
 * @copyright       (c) 2010-2012, Jean-David Gadina <macmade@eosgarden.com>
 */

#include "xeos/vm.h"
#include "xeos/__vm.h"
#include "xeos/hal/cpu.h"
#include <stdlib.h>
#include <string.h>

void XEOS_VM_SystemMapInitialize( XEOS_Info_MemoryRef memory, int ( * outputHandler )( const char *, ... ) )
{
    XEOS_VM_MemoryMapType       type;
    uint64_t                    totalMemoryBytes;
    uint64_t                    ptEntriesCount;
    uint64_t                    ptCount;
    uint64_t                    pdtCount;
    uint64_t                    pdptCount;
    uint64_t                    pml4tCount;
    uint64_t                    ptEntriesPerPT;
    uint64_t                    mapMemory;
    XEOS_Info_MemoryEntryRef    memoryEntry;
    XEOS_Info_MemoryEntryType   memoryType;
    uint64_t                    i;
    uint64_t                    memoryLength;
    uint64_t                    memoryStart;
    uint64_t                    memoryEnd;
    uint64_t                    systemMapAddress;
    uint64_t                    kernelStart;
    uint64_t                    kernelEnd;
    XEOS_VM_MemoryMapRef        systemMap;
    
    systemMap = XEOS_VM_SystemMap();
    
    /* Do not allows the system map to be initialized more than once */
    if( XEOS_VM_MemoryMapGetAddress( systemMap ) != NULL )
    {
        return;
    }
    
    #ifndef __LP64__
    
    /*
     * Disables paging on i386, as we are seeting up things
     * (not allowed on x86-64)
     */
    XEOS_HAL_CPU_DisablePaging();
    
    #endif
    
    #ifdef __LP64__
    
    /* x86-64 only has one paging mode (4 level paging) */
    type = XEOS_VM_MemoryMapType64;
    
    #else
    
    /* For 32 bits, paging layout depends on PAE status */
    if( XEOS_HAL_CPU_PAEEnabled() == true )
    {
        type = XEOS_VM_MemoryMapType32PAE;
    }
    else
    {
        type = XEOS_VM_MemoryMapType32;
    }
    
    #endif
    
    /* Gets the total amount of physical memory */
    totalMemoryBytes = XEOS_Info_MemoryGetTotalBytes( memory );
    
    /* For i386, no need for PAE if memory is lower than 4GB */
    if( type == XEOS_VM_MemoryMapType32PAE && totalMemoryBytes < 0x100000000 )
    {
        type = XEOS_VM_MemoryMapType32;
        
        XEOS_HAL_CPU_DisablePAE();
    }
    
    /* Computes the number of required page tables/page table entries */
    ptEntriesCount  = totalMemoryBytes / 0x1000;
    ptEntriesCount += ( ( totalMemoryBytes % 0x1000 ) == 0 ) ? 0 : 1;
    ptEntriesPerPT  = ( type == XEOS_VM_MemoryMapType32 ) ? 0x400 : 0x200;
    ptCount         = ptEntriesCount / ptEntriesPerPT;
    ptCount        += ( ( ptEntriesCount % ptEntriesPerPT ) == 0 ) ? 0 : 1;
    
    pdtCount        = 0;
    pdptCount       = 0;
    pml4tCount      = 0;
    
    /* For i386 without PAE, only one page directory table */
    if( type == XEOS_VM_MemoryMapType32 )
    {
        pdtCount = 1;
    }
    else
    {
        /* Computes the number of required page directory tables */
        if( ptCount > 0x200 )
        {
            pdtCount  = ptCount / 0x200;
            pdtCount  = ( pdtCount == 0 ) ? 1 : pdtCount;
            pdtCount += ( ( ptCount % 0x200 ) == 0 ) ? 0 : 1;
        }
        else
        {
            pdtCount = 1;
        }
        
        /* For i386 PAE, only one page directory pointer table */
        if( type == XEOS_VM_MemoryMapType32PAE )
        {
            pdptCount = 1;
        }
        else
        {
            /* Computes the number of required page directory pointer tables */
            if( pdtCount > 0x200 )
            {
                pdptCount  = pdtCount / 0x200;
                pdptCount  = ( pdptCount == 0 ) ? 1 : pdptCount;
                pdptCount += ( ( pdtCount % 0x200 ) == 0 ) ? 0 : 1;
            }
            else
            {
                pdptCount = 1;
            }
            
            /* Only one page-map level-4 table (x86-64) */
            pml4tCount = 1;
        }
    }
    
    /* Computes the required amount of memory to map all the available memory */
    mapMemory  = ptCount    * 0x1000;
    mapMemory += pdtCount   * 0x1000;
    mapMemory += pdptCount  * 0x1000;
    mapMemory += pml4tCount * 0x1000;
    
    if( outputHandler != NULL )
    {
        for( i = 0; i < XEOS_Info_MemoryGetNumberOfEntries( memory ); i++ )
        {
            memoryEntry     = XEOS_Info_MemoryGetEntryAtIndex( memory, ( unsigned int )i );
            memoryStart     = XEOS_Info_MemoryEntryGetAddress( memoryEntry );
            memoryLength    = XEOS_Info_MemoryEntryGetLength( memoryEntry );
            memoryType      = XEOS_Info_MemoryEntryGetType( memoryEntry );
            
            if( memoryLength == 0 )
            {
                continue;
            }
            
            outputHandler( "%016#llX -> %016#llX: ", memoryStart, ( memoryStart + memoryLength ) - 1 );
            
            switch( memoryType )
            {
                case XEOS_Info_MemoryEntryTypeUnknown:          outputHandler( "Unknown " ); break;
                case XEOS_Info_MemoryEntryTypeUsable:           outputHandler( "Usable  " ); break;
                case XEOS_Info_MemoryEntryTypeReserved:         outputHandler( "Reserved" ); break;
                case XEOS_Info_MemoryEntryTypeACPIReclaimable:  outputHandler( "ACPI    " ); break;
                case XEOS_Info_MemoryEntryTypeACPINVS:          outputHandler( "ACPI NVS" ); break;
                case XEOS_Info_MemoryEntryTypeBad:              outputHandler( "Bad     " ); break;
            }
            
            outputHandler( " - %llu B", memoryLength );
            
            if( memoryLength >= 0x100000 )
            {
                outputHandler( " (%llu MB)\n", ( ( memoryLength / 1024 ) / 1024 ) );
            }
            else
            {
                outputHandler( "\n" );
            }
        }
        
        outputHandler( "Memory map type:            %s\n", ( type == XEOS_VM_MemoryMapType32 ) ? "i386" : ( ( type == XEOS_VM_MemoryMapType32PAE ) ? "i386 PAE" : "x86-64" ) );
        outputHandler( "Total memory:               %llu B", totalMemoryBytes );
        
        if( totalMemoryBytes >= 0x100000 )
        {
            outputHandler( " (%llu MB)\n", ( ( totalMemoryBytes / 0x400 ) / 0x400 ) );
        }
        else
        {
            outputHandler( "\n" );
        }
        
        outputHandler( "PTE:                        %llu\n", ptEntriesCount );
        outputHandler( "PTE/PT:                     %llu\n", ptEntriesPerPT );
        outputHandler( "PT:                         %llu\n", ptCount );
        outputHandler( "PDT:                        %llu\n", pdtCount );
        outputHandler( "PDPT:                       %llu\n", pdptCount );
        outputHandler( "PML4T:                      %llu\n", pml4tCount );
        outputHandler( "System map memory use:      %llu B", mapMemory );
        
        if( mapMemory >= 0x100000 )
        {
            outputHandler( " (%llu MB)\n", ( ( mapMemory / 0x400 ) / 0x400 ) );
        }
        else
        {
            outputHandler( "\n" );
        }
    }
    
    /* Kernel location */
    kernelStart      = ( uint64_t )XEOS_Info_GetKernelStartAddress();
    kernelEnd        = ( uint64_t )XEOS_Info_GetKernelEndAddress();
    kernelEnd       &= UINT64_MAX - 0x0FFF;
    kernelEnd       += 0x1000;
    kernelEnd       -= 1;
    systemMapAddress = 0;
    
    /* Process each memory region to find room for the system map */
    for( i = 0; i < XEOS_Info_MemoryGetNumberOfEntries( memory ); i++ )
    {
        /* Gets informations about the current memory region */
        memoryEntry     = XEOS_Info_MemoryGetEntryAtIndex( memory, ( unsigned int )i );
        memoryLength    = XEOS_Info_MemoryEntryGetLength( memoryEntry );
        memoryStart     = XEOS_Info_MemoryEntryGetAddress( memoryEntry );
        memoryEnd       = ( memoryStart + memoryLength ) - 1;
        memoryType      = XEOS_Info_MemoryEntryGetType( memoryEntry );
        
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
        if( memoryLength < mapMemory )
        {
            continue;
        }
        
        /*
         * The second stage bootloader only maps the first 12 MB of memory
         * (0x300000000), so the system map needs to be contained in those
         * 12 first MB, otherwise we'll just page fault trying to write the
         * page tables in a still un-mapped memory area.
         */
        if( memoryStart >= 0x300000000 || ( memoryStart + mapMemory ) >= 0x300000000 )
        {
            break;
        }
        
        /* Found a suitable place */
        if( memoryStart > kernelEnd )
        {
            systemMapAddress = memoryStart;
            break;
        }
        
        /* Found a suitable place */
        if( memoryEnd > kernelEnd && ( memoryEnd - kernelEnd ) >= mapMemory )
        {
            systemMapAddress = kernelEnd + 1;
        }
    }
    
    /* Identity-maps the available memory if possible */
    if( systemMapAddress > 0 )
    {
        if( outputHandler != NULL )
        {
            outputHandler
            (
                "Kernel area:                %016#llX -> %016#llX\n"
                "System map area:            %016#llX -> %016#llX\n",
                kernelStart,
                kernelEnd,
                systemMapAddress,
                ( systemMapAddress + mapMemory ) - 1
            );
        }
        
        /* Stores the system map infos */
        XEOS_VM_MemoryMapSetAddress( systemMap, ( void * )systemMapAddress );
        XEOS_VM_MemoryMapSetLength( systemMap, mapMemory );
        XEOS_VM_MemoryMapSetType( systemMap, type );
        XEOS_VM_MemoryMapSetPTCount( systemMap, ptCount );
        XEOS_VM_MemoryMapSetPDTCount( systemMap, pdtCount );
        XEOS_VM_MemoryMapSetPDPTCount( systemMap, pdptCount );
        XEOS_VM_MemoryMapSetPML4TCount( systemMap, pml4tCount );
        
        {
            XEOS_VM_PTRef           pt;
            XEOS_VM_PTEntryRef      ptEntry;
            XEOS_VM_PDTRef          pdt;
            XEOS_VM_PDTEntryRef     pdtEntry;
            XEOS_VM_PDPTRef         pdpt;
            XEOS_VM_PDPTEntryRef    pdptEntry;
            XEOS_VM_PML4TRef        pml4t;
            XEOS_VM_PML4TEntryRef   pml4tEntry;
            void                  * p;
            uint64_t                address;
            uint64_t                j;
            unsigned int            k;
            
            p           = XEOS_VM_MemoryMapGetAddress( systemMap );
            address     = 0;
            ptEntry     = NULL;
            pdtEntry    = NULL;
            pdptEntry   = NULL;
            pml4tEntry  = NULL;
            
            if( outputHandler != NULL )
            {
                outputHandler( "Initializing PTs:           " );
            }
            
            /* Initializes the page tables */
            if( ptCount > 0 )
            {
                /* Process each page table */
                for( i = 0; i < ptCount; i++ )
                {
                    /* Address of the current page table */
                    pt = p;
                    
                    /* Clears the current page table */
                    XEOS_VM_PTClear( pt );
                    
                    /* Process each entry in the page table */
                    for( j = 0; j < ptEntriesPerPT; j++ )
                    {
                        /* Gets the page table entry */
                        ptEntry = XEOS_VM_PTGetEntryAtIndex( pt, ( unsigned int )j );
                        
                        /* Only map entries matching a physical memory address */
                        if( address >= totalMemoryBytes )
                        {
                            continue;
                        }
                        
                        /* Sets the physical memory address */
                        XEOS_VM_PTEntrySetAddress( ptEntry, address );
                        
                        /* Address in present in physical memory */
                        XEOS_VM_PTEntrySetFlag( ptEntry, XEOS_VM_PTEntryFlagPresent, true );
                        
                        /* Process each memory area */
                        for( k = 0; k < XEOS_Info_MemoryGetNumberOfEntries( memory ); k++ )
                        {
                            memoryEntry     = XEOS_Info_MemoryGetEntryAtIndex( memory, k );
                            memoryLength    = XEOS_Info_MemoryEntryGetLength( memoryEntry );
                            memoryStart     = XEOS_Info_MemoryEntryGetAddress( memoryEntry );
                            memoryType      = XEOS_Info_MemoryEntryGetType( memoryEntry );
                            
                            /* Checks if the current page belongs to the current memory area */
                            if( address < memoryStart || ( address - memoryStart ) > memoryLength )
                            {
                                continue;
                            }
                            
                            /* If the memory area is usable, marks the page table entry as writeable */
                            if( memoryType == XEOS_Info_MemoryEntryTypeUsable )
                            {
                                XEOS_VM_PTEntrySetFlag( ptEntry, XEOS_VM_PTEntryFlagWriteable, true );
                            }
                            
                            break;
                        }
                        
                        /* Next 4 KB aligned physical memory address */
                        address += 0x1000;
                    }
                    
                    /* Next 4KB aligned page table */
                    p = ( ( char * )p + 0x1000 );
                }
            }
            
            /* Address of the first page table */
            pt = XEOS_VM_MemoryMapGetAddress( systemMap );
            
            if( outputHandler != NULL )
            {
                outputHandler( "%016#lX -> %016#lX\n", pt, ( uint64_t )p - 1 );
                outputHandler( "Physical addresses mapped:  %016#llX -> %016#llX\n", ( uint64_t )0, address - ( uint64_t )1 );
                
                if( type == XEOS_VM_MemoryMapType32 )
                {
                    outputHandler( "Initializing PDT:           " );
                }
                else
                {
                    outputHandler( "Initializing PDTs:          " );
                }
            }
            
            /* Initializes the page directory tables */
            if( pdtCount > 0 )
            {
                /* Process each page directory table */
                for( i = 0; i < pdtCount; i++ )
                {
                    /* Address of the current page directory table */
                    pdt = p;
                    
                    /* Clears the current page directory table */
                    XEOS_VM_PDTClear( pdt );
                    
                    /* Process each entry in the page directory table */
                    for( j = 0; j < ptEntriesPerPT; j++ )
                    {
                        /* Only initializes entries with a valid page table */
                        if( ( ( i * ptEntriesPerPT ) + j ) >= ptCount )
                        {
                            break;
                        }
                        
                        /* Gets the page directory table entry */
                        pdtEntry = XEOS_VM_PDTGetEntryAtIndex( pdt, ( unsigned int )j );
                        
                        /* Sets the page table address */
                        XEOS_VM_PDTEntrySetPT( pdtEntry, pt );
                        
                        /* Entry is present and writeable */
                        XEOS_VM_PDTEntrySetFlag( pdtEntry, XEOS_VM_PDTEntryFlagPresent, true );
                        XEOS_VM_PDTEntrySetFlag( pdtEntry, XEOS_VM_PDTEntryFlagWriteable, true );
                        
                        /* Next 4 KB aligned entry */
                        pt = ( void * )( ( char * )pt + 0x1000 );
                    }
                    
                    /* Next 4KB aligned page directory table */
                    p = ( ( char * )p + 0x1000 );
                }
            }
            
            /* Address of the first page directory table */
            pdt = ( XEOS_VM_PDPTRef )pt;
            
            if( outputHandler != NULL )
            {
                outputHandler( "%016#lX -> %016#lX\n", pdt, ( uint64_t )p - 1 );
            }
            
            /* For i386 (without PAE), we're actually done */
            if( type == XEOS_VM_MemoryMapType32 )
            {  
                if( outputHandler != NULL )
                {
                    outputHandler( "Updating CR3 with PDT:      %016#lX\n", pdt );
                }
                
                /* Updates CR3 with the page directory table address */
                XEOS_HAL_CPU_SetCR3( ( uint32_t )pdt );
                XEOS_VM_MemoryMapSetCR3( systemMap, ( uint32_t )pdt );
            }
            else
            {
                if( outputHandler != NULL )
                {
                    if( type == XEOS_VM_MemoryMapType32PAE )
                    {
                        outputHandler( "Initializing PDPT:          " );
                    }
                    else
                    {
                        outputHandler( "Initializing PDPTs:         " );
                    }
                }
                
                /* Initializes the page directory pointer tables */
                if( pdptCount > 0 )
                {
                    /* Process each page directory pointer table */
                    for( i = 0; i < pdptCount; i++ )
                    {
                        /* Address of the current page directory pointer table */
                        pdpt = p;
                        
                        /* Clears the current page directory pointer table */
                        XEOS_VM_PDPTClear( pdpt );
                        
                        /* Process each entry in the page directory pointer table */
                        for( j = 0; j < ptEntriesPerPT; j++ )
                        {
                            /* Only initializes entries with a valid page directory table */
                            if( ( ( i * ptEntriesPerPT ) + j ) >= pdtCount )
                            {
                                break;
                            }
                            
                            /* Gets the page directory pointer table entry */
                            pdptEntry = XEOS_VM_PDPTGetEntryAtIndex( pdpt, ( unsigned int )j );
                            
                            /* Sets the page directory table address */
                            XEOS_VM_PDPTEntrySetPDT( pdptEntry, pdt );
                            
                            /* ENtry is present */
                            XEOS_VM_PDPTEntrySetFlag( pdptEntry, XEOS_VM_PDPTEntryFlagPresent, true );
                            
                            /* For x86-64, marks the entry as writeable */
                            if( type == XEOS_VM_MemoryMapType64 )
                            {
                                XEOS_VM_PDPTEntrySetFlag( pdptEntry, XEOS_VM_PDPTEntryFlagWriteable, true );
                            }
                            
                            /* Next 4 KB aligned entry */
                            pdt = ( void * )( ( char * )pdt + 0x1000 );
                        }
                        
                        /* Next 4KB aligned page directory pointer table */
                        p = ( ( char * )p + 0x1000 );
                    }
                }
                
                /* Address of the first page directory pointer table */
                pdpt = ( XEOS_VM_PDPTRef )pdt;
                
                if( outputHandler != NULL )
                {
                    outputHandler( "%016#lX -> %016#lX\n", pdpt, ( uintptr_t )p - 1 );
                }
                
                /* For i386 (PAE), we're actually done */
                if( type == XEOS_VM_MemoryMapType32PAE )
                {
                    if( outputHandler != NULL )
                    {
                        outputHandler( "Updating CR3 with PDPT:     %016#lX\n", pdpt );
                    }
                    
                    /* Updates CR3 with the page directory pointer table address */
                    XEOS_HAL_CPU_SetCR3( ( uint32_t )pdpt );
                    XEOS_VM_MemoryMapSetCR3( systemMap, ( uint32_t )pdpt );
                }
                else
                {
                    if( outputHandler != NULL )
                    {
                        outputHandler( "Initializing PML4T:         " );
                    }
                    
                    /* Initializes the page-map level-4 tables */
                    if( pml4tCount > 0 )
                    {
                        /* Process each page-map level-4 table */
                        for( i = 0; i < pml4tCount; i++ )
                        {
                            /* Address of the current page-map level-4 table */
                            pml4t = p;
                            
                            /* Clears the current page-map level-4 table */
                            XEOS_VM_PML4TClear( pml4t );
                            
                            /* Process each entry in the page-map level-4 table */
                            for( j = 0; j < ptEntriesPerPT; j++ )
                            {
                                /* Only initializes entries with a valid page directory pointer table */
                                if( ( ( i * ptEntriesPerPT ) + j ) >= pdptCount )
                                {
                                    break;
                                }
                                
                                /* Gets the page-map level-4 table entry */
                                pml4tEntry = XEOS_VM_PML4TGetEntryAtIndex( pml4t, ( unsigned int )j );
                                
                                /* Sets the page directory pointer table address */
                                XEOS_VM_PML4TEntrySetPDPT( pml4tEntry, pdpt );
                                
                                /* Entry is present and writeable */
                                XEOS_VM_PML4TEntrySetFlag( pml4tEntry, XEOS_VM_PML4TEntryFlagPresent, true );
                                XEOS_VM_PML4TEntrySetFlag( pml4tEntry, XEOS_VM_PML4TEntryFlagWriteable, true );
                                
                                /* Next 4 KB aligned entry */
                                pdpt = ( void * )( ( char * )pdpt + 0x1000 );
                            }
                            
                            /* Next 4KB aligned page-map level-4 table */
                            p = ( ( char * )p + 0x1000 );
                        }
                    }
                    
                    /* Address of the first page-map level-4 table */
                    pml4t = ( XEOS_VM_PDPTRef )pdpt;
                    
                    if( outputHandler != NULL )
                    {
                        outputHandler( "%016#lX -> %016#lX\n", pml4t, ( uintptr_t )p - 1 );
                    }
                    
                    if( outputHandler != NULL )
                    {
                        outputHandler( "Updating CR3 with PML4T:    %016#lX\n", pml4t );
                    }
                    
                    /* Updates CR3 with the page-map level-4 table address */
                    XEOS_HAL_CPU_SetCR3( ( uint32_t )pml4t );
                    XEOS_VM_MemoryMapSetCR3( systemMap, ( uint32_t )pml4t );
                }
            }
        }
    }
    
    #ifndef __LP64__
    
    /* For i386, re-enables pagingC */
    XEOS_HAL_CPU_EnablePaging();
    
    #endif
}
