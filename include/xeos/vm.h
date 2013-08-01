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
 * @header          vm.h
 * @author          Jean-David Gadina
 * @copyright       (c) 2010-2013, Jean-David Gadina - www.xs-labs.com
 */

#ifndef __XEOS_VM_H__
#define __XEOS_VM_H__
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <xeos/macros.h>
#include <xeos/info.h>
#include <stdint.h>
#include <stdbool.h>

typedef enum
{
    XEOS_VM_MemoryMapTypeUnknown        = 0x00,
    XEOS_VM_MemoryMapType32             = 0x01,
    XEOS_VM_MemoryMapType32PAE          = 0x02,
    XEOS_VM_MemoryMapType64             = 0x03
}
XEOS_VM_MemoryMapType;

typedef enum
{
    XEOS_VM_PML4TEntryFlagPresent       = 1 << 0,
    XEOS_VM_PML4TEntryFlagWriteable     = 1 << 1,
}
XEOS_VM_PML4TEntryFlag;

typedef enum
{
    XEOS_VM_PDPTEntryFlagPresent        = 1 << 0,
    XEOS_VM_PDPTEntryFlagWriteable      = 1 << 1,
}
XEOS_VM_PDPTEntryFlag;

typedef enum
{
    XEOS_VM_PDTEntryFlagPresent         = 1 << 0,
    XEOS_VM_PDTEntryFlagWriteable       = 1 << 1,
    XEOS_VM_PDTEntryFlagUser            = 1 << 2,
    XEOS_VM_PDTEntryFlagWriteThrough    = 1 << 3,
    XEOS_VM_PDTEntryFlagCacheDisbled    = 1 << 4,
    XEOS_VM_PDTEntryFlagAccessed        = 1 << 5,
    XEOS_VM_PDTEntryFlagPageSize        = 1 << 6,
    XEOS_VM_PDTEntryFlagGLobal          = 1 << 8,
}
XEOS_VM_PDTEntryFlag;

typedef enum
{
    XEOS_VM_PTEntryFlagPresent          = 1 << 0,
    XEOS_VM_PTEntryFlagWriteable        = 1 << 1,
    XEOS_VM_PTEntryFlagUser             = 1 << 2,
    XEOS_VM_PTEntryFlagWriteThrough     = 1 << 3,
    XEOS_VM_PTEntryFlagCacheDisbled     = 1 << 4,
    XEOS_VM_PTEntryFlagAccessed         = 1 << 5,
    XEOS_VM_PTEntryFlagDirty            = 1 << 6,
    XEOS_VM_PTEntryFlagGLobal           = 1 << 8,
}
XEOS_VM_PTEntryFlag;

typedef struct __XEOS_VM_MemoryMap  * XEOS_VM_MemoryMapRef;
typedef void                        * XEOS_VM_PML4TEntryRef;
typedef void                        * XEOS_VM_PML4TRef;
typedef void                        * XEOS_VM_PDPTEntryRef;
typedef void                        * XEOS_VM_PDPTRef;
typedef void                        * XEOS_VM_PDTEntryRef;
typedef void                        * XEOS_VM_PDTRef;
typedef void                        * XEOS_VM_PTEntryRef;
typedef void                        * XEOS_VM_PTRef;

XEOS_VM_MemoryMapRef    XEOS_VM_SystemMap( void );
void                    XEOS_VM_SystemMapInitialize( int ( * outputHandler )( const char *, ... ) );

void *                  XEOS_VM_MemoryMapGetAddress( XEOS_VM_MemoryMapRef object );
uint64_t                XEOS_VM_MemoryMapGetLength( XEOS_VM_MemoryMapRef object );
XEOS_VM_MemoryMapType   XEOS_VM_MemoryMapGetType( XEOS_VM_MemoryMapRef object );
uint32_t                XEOS_VM_MemoryMapGetCR3( XEOS_VM_MemoryMapRef object );
uint64_t                XEOS_VM_MemoryMapGetPTCount( XEOS_VM_MemoryMapRef object );
uint64_t                XEOS_VM_MemoryMapGetPDTCount( XEOS_VM_MemoryMapRef object );
uint64_t                XEOS_VM_MemoryMapGetPDPTCount( XEOS_VM_MemoryMapRef object );
uint64_t                XEOS_VM_MemoryMapGetPML4TCount( XEOS_VM_MemoryMapRef object );
void                    XEOS_VM_MemoryMapSetAddress( XEOS_VM_MemoryMapRef object, void * address );
void                    XEOS_VM_MemoryMapSetLength( XEOS_VM_MemoryMapRef object, uint64_t length );
void                    XEOS_VM_MemoryMapSetType( XEOS_VM_MemoryMapRef object, XEOS_VM_MemoryMapType type );
void                    XEOS_VM_MemoryMapSetCR3( XEOS_VM_MemoryMapRef object, uint32_t cr3 );
void                    XEOS_VM_MemoryMapSetPTCount( XEOS_VM_MemoryMapRef object, uint64_t count );
void                    XEOS_VM_MemoryMapSetPDTCount( XEOS_VM_MemoryMapRef object, uint64_t count );
void                    XEOS_VM_MemoryMapSetPDPTCount( XEOS_VM_MemoryMapRef object, uint64_t count );
void                    XEOS_VM_MemoryMapSetPML4TCount( XEOS_VM_MemoryMapRef object, uint64_t count );

void                    XEOS_VM_PML4TClear( XEOS_VM_PML4TRef object );
XEOS_VM_PML4TEntryRef   XEOS_VM_PML4TGetEntryAtIndex( XEOS_VM_PML4TRef object, unsigned int i );

void                    XEOS_VM_PML4TEntryClear( XEOS_VM_PML4TEntryRef object );
void                    XEOS_VM_PML4TEntrySetPDPT( XEOS_VM_PML4TEntryRef object, XEOS_VM_PDPTRef pdpt );
void                    XEOS_VM_PML4TEntrySetFlag( XEOS_VM_PML4TEntryRef object, XEOS_VM_PML4TEntryFlag flag, bool value );
XEOS_VM_PDPTRef         XEOS_VM_PML4TEntryGetPDPT( XEOS_VM_PML4TEntryRef object );
bool                    XEOS_VM_PML4TEntryGetFlag( XEOS_VM_PML4TEntryRef object, XEOS_VM_PML4TEntryFlag flag );

void                    XEOS_VM_PDPTClear( XEOS_VM_PDPTRef object );
XEOS_VM_PDPTEntryRef    XEOS_VM_PDPTGetEntryAtIndex( XEOS_VM_PDPTRef object, unsigned int i );

void                    XEOS_VM_PDPTEntryClear( XEOS_VM_PDPTEntryRef object );
void                    XEOS_VM_PDPTEntrySetPDT( XEOS_VM_PDPTEntryRef object, XEOS_VM_PDTRef pdt );
void                    XEOS_VM_PDPTEntrySetFlag( XEOS_VM_PDPTEntryRef object, XEOS_VM_PDPTEntryFlag flag, bool value );
XEOS_VM_PDTRef          XEOS_VM_PDPTEntryGetPDT( XEOS_VM_PDPTEntryRef object );
bool                    XEOS_VM_PDPTEntryGetFlag( XEOS_VM_PDPTEntryRef object, XEOS_VM_PDPTEntryFlag flag );

void                    XEOS_VM_PDTClear( XEOS_VM_PDTRef object );
XEOS_VM_PDTEntryRef     XEOS_VM_PDTGetEntryAtIndex( XEOS_VM_PDTRef object, unsigned int i );

void                    XEOS_VM_PDTEntryClear( XEOS_VM_PDTEntryRef object );
void                    XEOS_VM_PDTEntrySetPT( XEOS_VM_PTEntryRef object, XEOS_VM_PTRef pt );
void                    XEOS_VM_PDTEntrySetFlag( XEOS_VM_PTEntryRef object, XEOS_VM_PDTEntryFlag flag, bool value );
XEOS_VM_PTRef           XEOS_VM_PDTEntryGetPT( XEOS_VM_PTEntryRef object );
bool                    XEOS_VM_PDTEntryGetFlag( XEOS_VM_PTEntryRef object, XEOS_VM_PDTEntryFlag flag );

void                    XEOS_VM_PTClear( XEOS_VM_PTRef object );
XEOS_VM_PTEntryRef      XEOS_VM_PTGetEntryAtIndex( XEOS_VM_PTRef object, unsigned int i );

void                    XEOS_VM_PTEntryClear( XEOS_VM_PTEntryRef object );
void                    XEOS_VM_PTEntrySetAddress( XEOS_VM_PTEntryRef object, uint64_t address );
void                    XEOS_VM_PTEntrySetFlag( XEOS_VM_PTEntryRef object, XEOS_VM_PTEntryFlag flag, bool value );
uint64_t                XEOS_VM_PTEntryGetAddress( XEOS_VM_PTEntryRef object );
bool                    XEOS_VM_PTEntryGetFlag( XEOS_VM_PTEntryRef object, XEOS_VM_PTEntryFlag flag );

#ifdef __cplusplus
}
#endif

#endif /* __XEOS_VM_H__ */
