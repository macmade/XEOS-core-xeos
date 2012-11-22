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

XEOS_VM_SystemMapRef XEOS_VM_SystemMapInitialize( XEOS_Info_MemoryRef memory, int ( * outputHandler )( const char *, ... ) )
{
    XEOS_VM_SystemMapType       type;
    uint64_t                    totalMemoryBytes;
    uint64_t                    ptEntriesCount;
    uint64_t                    ptCount;
    uint64_t                    pdtCount;
    uint64_t                    pdptCount;
    uint64_t                    pml4tCount;
    uint64_t                    ptEntriesPerPT;
    uint64_t                    mapMemory;
    XEOS_Info_MemoryEntryRef    memoryEntry;
    uint64_t                    i;
    uint64_t                    memoryLength;
    uint64_t                    memoryStart;
    uint64_t                    memoryEnd;
    uint64_t                    systemMapAddress;
    uint64_t                    kernelEnd;
    
    #ifndef __LP64__
    
    XEOS_VM_DisablePaging();
    
    #endif
    
    #ifdef __LP64__
    
    type = XEOS_VM_SystemMapType64;
    
    #else
    
    if( XEOS_VM_PAEEnabled() == true )
    {
        type = XEOS_VM_SystemMapType32PAE;
    }
    else
    {
        type = XEOS_VM_SystemMapType32;
    }
    
    #endif
    
    totalMemoryBytes = XEOS_Info_MemoryGetTotalBytes( memory );
    
    /* For i386, no need for PAE if memory is lower than 4GB */
    if( type == XEOS_VM_SystemMapType32PAE && totalMemoryBytes < 0x100000000 )
    {
        type = XEOS_VM_SystemMapType32;
        
        XEOS_VM_DisablePAE();
    }
    
    if( outputHandler != NULL )
    {
        outputHandler
        (
            "Memory map type:     %s\n",
            ( type == XEOS_VM_SystemMapType32 ) ? "i386" : ( ( type == XEOS_VM_SystemMapType32PAE ) ? "i386 PAE" : "x86-64" )
        );
    }
    
    ptEntriesCount  = totalMemoryBytes / 0x1000;
    ptEntriesCount += ( ( totalMemoryBytes % 0x1000 ) == 0 ) ? 0 : 1;
    ptEntriesPerPT  = ( type == XEOS_VM_SystemMapType32 ) ? 0x400 : 0x200;
    ptCount         = ptEntriesCount / ptEntriesPerPT;
    ptCount        += ( ( ptEntriesCount % ptEntriesPerPT ) == 0 ) ? 0 : 1;
    
    if( outputHandler != NULL )
    {
        outputHandler( "Total memory:        %Lu (%Lu MB)\n", totalMemoryBytes, ( ( totalMemoryBytes / 0x400 ) / 0x400 ) );
        outputHandler( "PTE:                 %Lu\n", ptEntriesCount );
        outputHandler( "PTE/PT:              %Lu\n", ptEntriesPerPT );
        outputHandler( "PT:                  %Lu\n", ptCount );
    }
    
    pdtCount    = 0;
    pdptCount   = 0;
    pml4tCount  = 0;
    
    if( type == XEOS_VM_SystemMapType32 )
    {
        pdtCount = 1;
    }
    else
    {
        pdtCount  = ptCount / 0x200;
        pdtCount  = ( pdtCount == 0 ) ? 1 : pdtCount;
        pdtCount += ( ( pdtCount % 0x200 ) == 0 ) ? 0 : 1;
        
        if( type == XEOS_VM_SystemMapType32PAE )
        {
            pdptCount = 1;
        }
        else
        {
            pdptCount  = pdtCount / 0x200;
            pdptCount  = ( pdptCount == 0 ) ? 1 : pdptCount;
            pdptCount += ( ( pdptCount % 0x200 ) == 0 ) ? 0 : 1;
            pml4tCount = 1;
        }
    }
    
    if( outputHandler != NULL )
    {
        outputHandler( "PDT:                 %Lu\n", pdtCount );
        outputHandler( "PDPT:                %Lu\n", pdptCount );
        outputHandler( "PML4T:               %Lu\n", pml4tCount );
    }
    
    mapMemory  = ptCount    * 0x1000;
    mapMemory += pdtCount   * 0x1000;
    mapMemory += pdptCount  * 0x1000;
    mapMemory += pml4tCount * 0x1000;
    
    if( outputHandler != NULL )
    {
        outputHandler( "PML4T:               %Lu\n", pml4tCount );
        outputHandler( "Map memory:          %Lu (%Lu MB)\n", mapMemory, ( ( mapMemory / 1024 ) / 1024 ) );
    }
    
    kernelEnd        = ( uint64_t )XEOS_Info_GetKernelEndAddress();
    kernelEnd       &= UINTPTR_MAX - 0x0FFF;
    kernelEnd       += 0x1000;
    systemMapAddress = 0;
    
    for( i = 0; i < XEOS_Info_MemoryGetNumberOfEntries( memory ); i++ )
    {
        memoryEntry     = XEOS_Info_MemoryGetEntryAtIndex( memory, ( unsigned int )i );
        memoryLength    = XEOS_Info_MemoryEntryGetLength( memoryEntry );
        memoryStart     = XEOS_Info_MemoryEntryGetAddress( memoryEntry );
        memoryEnd       = ( memoryStart + memoryLength ) - 1;
        
        if( memoryStart < kernelEnd || memoryEnd < kernelEnd )
        {
            continue;
        }
        
        if( mapMemory <= memoryEnd - kernelEnd )
        {
            systemMapAddress = kernelEnd;
            
            break;
        }
    }
    
    /*
     * The second stage bootloader only maps the first 12 MB of memory
     * (0x300000000), so the system map needs to be contained in those
     * 12 first MB, otherwise we'll just page fault trying to write the
     * page tables in a still un-mapped memory area.
     */
    if( systemMapAddress > 0 && ( systemMapAddress - mapMemory ) < 0x300000000 )
    {
        if( outputHandler != NULL )
        {
            outputHandler( "System map address:  %016#LX\n", systemMapAddress );
        }
        
        __XEOS_VM_SystemMap.base        = ( void * )systemMapAddress;
        __XEOS_VM_SystemMap.length      = mapMemory;
        __XEOS_VM_SystemMap.type        = type;
        __XEOS_VM_SystemMap.ptCount     = ptCount;
        __XEOS_VM_SystemMap.pdtCount    = pdtCount;
        __XEOS_VM_SystemMap.pdptCount   = pdptCount;
        __XEOS_VM_SystemMap.pml4tCount  = pml4tCount;
        
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
            uintptr_t               address;
            uint64_t                j;
            
            p       = __XEOS_VM_SystemMap.base;
            address = 0;
            
            if( ptCount > 0 )
            {
                for( i = 0; i < ptCount; i++ )
                {
                    pt = p;
                    
                    XEOS_VM_PTClear( pt );
                    
                    for( j = 0; j < ptEntriesPerPT; j++ )
                    {
                        ptEntry = XEOS_VM_PTGetEntryAtIndex( pt, ( unsigned int )j );
                        
                        if( address < totalMemoryBytes )
                        {
                            XEOS_VM_PTEntrySetAddress( ptEntry, address );
                            XEOS_VM_PTEntrySetFlag( ptEntry, XEOS_VM_PTEntryFlagPresent, true );
                            XEOS_VM_PTEntrySetFlag( ptEntry, XEOS_VM_PTEntryFlagWriteable, true );
                        }
                        
                        address += 0x1000;
                    }
                    
                    p = ( ( char * )p + 0x1000 );
                }
            }
            
            if( outputHandler != NULL )
            {
                outputHandler( "Last mapped address: %016#LX\n", address );
            }
            
            pt = __XEOS_VM_SystemMap.base;
            
            if( pdtCount > 0 )
            {
                for( i = 0; i < pdtCount; i++ )
                {
                    pdt = p;
                    
                    XEOS_VM_PDTClear( pdt );
                    
                    for( j = 0; j < ptEntriesPerPT; j++ )
                    {
                        pdtEntry = XEOS_VM_PDTGetEntryAtIndex( pdt, ( unsigned int )j );
                        
                        XEOS_VM_PDTEntrySetPT( pdtEntry, pt );
                        XEOS_VM_PDTEntrySetFlag( pdtEntry, XEOS_VM_PDTEntryFlagPresent, true );
                        XEOS_VM_PDTEntrySetFlag( pdtEntry, XEOS_VM_PDTEntryFlagWriteable, true );
                        
                        pt = ( void * )( ( char * )pt + 0x1000 );
                    }
                    
                    p = ( ( char * )p + 0x1000 );
                }
            }
            
            pdt = ( XEOS_VM_PDPTRef )pt;
            
            if( type == XEOS_VM_SystemMapType32 )
            {
                XEOS_HAL_CPU_SetCR3( ( uint32_t )pdt );
            }
            else
            {
                if( pdptCount > 0 )
                {
                    for( i = 0; i < pdptCount; i++ )
                    {
                        pdpt = p;
                        
                        XEOS_VM_PDPTClear( pdpt );
                        
                        for( j = 0; j < ptEntriesPerPT; j++ )
                        {
                            pdptEntry = XEOS_VM_PDPTGetEntryAtIndex( pdpt, ( unsigned int )j );
                            
                            XEOS_VM_PDPTEntrySetPDT( pdptEntry, pdt );
                            XEOS_VM_PDPTEntrySetFlag( pdptEntry, XEOS_VM_PDPTEntryFlagPresent, true );
                            
                            if( type == XEOS_VM_SystemMapType64 )
                            {
                                XEOS_VM_PDPTEntrySetFlag( pdptEntry, XEOS_VM_PDPTEntryFlagWriteable, true );
                            }
                            
                            pdt = ( void * )( ( char * )pt + 0x1000 );
                        }
                        
                        p = ( ( char * )p + 0x1000 );
                    }
                }
                
                pdpt = ( XEOS_VM_PDPTRef )pdt;
                
                if( type == XEOS_VM_SystemMapType32PAE )
                {
                    XEOS_HAL_CPU_SetCR3( ( uint32_t )pdpt );
                }
                else
                {
                    if( pml4tCount > 0 )
                    {
                        for( i = 0; i < pml4tCount; i++ )
                        {
                            pml4t = p;
                            
                            XEOS_VM_PML4TClear( pml4t );
                            
                            for( j = 0; j < ptEntriesPerPT; j++ )
                            {
                                pml4tEntry = XEOS_VM_PML4TGetEntryAtIndex( pml4t, ( unsigned int )j );
                                
                                XEOS_VM_PML4TEntrySetPDPT( pml4tEntry, pdpt );
                                XEOS_VM_PML4TEntrySetFlag( pml4tEntry, XEOS_VM_PML4TEntryFlagPresent, true );
                                XEOS_VM_PML4TEntrySetFlag( pml4tEntry, XEOS_VM_PML4TEntryFlagWriteable, true );
                                
                                pdpt = ( void * )( ( char * )pt + 0x1000 );
                            }
                            
                            p = ( ( char * )p + 0x1000 );
                        }
                    }
                    
                    pml4t = ( XEOS_VM_PDPTRef )pdpt;
                    
                    XEOS_HAL_CPU_SetCR3( ( uint32_t )pml4t );
                }
            }
        }
    }
    
    #ifndef __LP64__
    
    XEOS_VM_EnablePaging();
    
    #endif
    
    return &__XEOS_VM_SystemMap;
}
