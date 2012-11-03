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

#ifndef __HAL_IDT_H__
#define __HAL_IDT_H__
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#define XEOS_HAL_IDT_MAX_DESCRIPTORS    256

#ifdef __clang__
#pragma pack( 1 )
#endif

struct _XEOS_HAL_IDT_Entry32
{
    uint16_t    baseLow;
    uint16_t    selector;
    uint8_t     __reserved_0;
    uint8_t     flags;
    uint16_t    baseHigh;
};

struct _XEOS_HAL_IDT_Pointer32
{
    uint16_t    limit;
    uint32_t    base;
};

struct _XEOS_HAL_IDT_Entry64
{
    uint16_t    baseLow;
    uint16_t    selector;
    uint8_t     __reserved_0;
    uint8_t     flags;
    uint16_t    baseMiddle;
    uint32_t    baseHigh;
    uint32_t    __reserved_1;
};

struct _XEOS_HAL_IDT_Pointer64
{
    uint16_t    limit;
    uint64_t    base;
};

#ifdef __clang__
#pragma pack()
#endif

#ifdef __LP64__

typedef struct _XEOS_HAL_IDT_Entry64    XEOS_HAL_IDT_Entry;
typedef struct _XEOS_HAL_IDT_Pointer64  XEOS_HAL_IDT_Pointer;

#else

typedef struct _XEOS_HAL_IDT_Entry32    XEOS_HAL_IDT_Entry;
typedef struct _XEOS_HAL_IDT_Pointer32  XEOS_HAL_IDT_Pointer;

#endif

typedef void ( * XEOS_HAL_IDT_ISRHandler )( unsigned int isr );

typedef enum
{
    XEOS_HAL_IDT_EntryType_Task32       = 0x05,
    XEOS_HAL_IDT_EntryType_Interrupt16  = 0x06,
    XEOS_HAL_IDT_EntryType_Trap16       = 0x07,
    XEOS_HAL_IDT_EntryType_Interrupt32  = 0x0E,
    XEOS_HAL_IDT_EntryType_Trap32       = 0x0F
}
XEOS_HAL_IDT_EntryType;

typedef enum
{
    XEOS_HAL_IDT_PrivilegeLevel_Ring0 = 0x00,
    XEOS_HAL_IDT_PrivilegeLevel_Ring1 = 0x01,
    XEOS_HAL_IDT_PrivilegeLevel_Ring2 = 0x02,
    XEOS_HAL_IDT_PrivilegeLevel_Ring3 = 0x03
}
XEOS_HAL_IDT_PrivilegeLevel;

void                        XEOS_HAL_IDT_Init( uint16_t selector );
void                        XEOS_HAL_IDT_SetISR( unsigned int isr, XEOS_HAL_IDT_ISRHandler handler, XEOS_HAL_IDT_EntryType type, XEOS_HAL_IDT_PrivilegeLevel level, bool reload );
void                        XEOS_HAL_IDT_Reload( void );
XEOS_HAL_IDT_ISRHandler     XEOS_HAL_IDT_GetISRHandler( unsigned int isr );
XEOS_HAL_IDT_EntryType      XEOS_HAL_IDT_GetISREntryType( unsigned int isr );
XEOS_HAL_IDT_PrivilegeLevel XEOS_HAL_IDT_GetISRPrivilegeLevel( unsigned int isr );

extern XEOS_HAL_IDT_Pointer     __XEOS_HAL_IDT_Pointer;
extern XEOS_HAL_IDT_Entry       __XEOS_HAL_IDT_Entries[];
extern XEOS_HAL_IDT_ISRHandler  __XEOS_HAL_IDT_Handlers[];

#ifdef __cplusplus
}
#endif

#endif /* __HAL_IDT_H__ */
