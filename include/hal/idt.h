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
 * @header          idt.h
 * @author          Jean-David Gadina
 * @copyright       (c) 2010-2013, Jean-David Gadina - www.xs-labs.com
 */

#ifndef __XEOS_HAL_IDT_H__
#define __XEOS_HAL_IDT_H__
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <xeos/macros.h>
#include <xeos/hal/cpu.h>
#include <stdint.h>
#include <stdbool.h>

/*!
 * @define          XEOS_HAL_IDT_MAX_DESCRIPTORS
 * @abstract        The maximum number of descriptors in the IDT
 */
#define XEOS_HAL_IDT_MAX_DESCRIPTORS            256

/*!
 * @typedef         XEOS_HAL_IDT_ISREntryType
 * @abstract        Type for an ISR entry
 * @constant        XEOS_HAL_IDT_ISREntryTypeUnknown        Unknown ISR entry
 * @constant        XEOS_HAL_IDT_ISREntryTypeTask32         32 bits task gate
 * @constant        XEOS_HAL_IDT_ISREntryTypeInterrupt16    16 bits interrupt gate
 * @constant        XEOS_HAL_IDT_ISREntryTypeTrap16         16 bits trap gate
 * @constant        XEOS_HAL_IDT_ISREntryTypeInterrupt32    32 bits interrupt gate
 * @constant        XEOS_HAL_IDT_ISREntryTypeTrap32         32 bits trap gate
 */
typedef enum
{
    XEOS_HAL_IDT_ISREntryTypeUnknown            = 0x00,
    XEOS_HAL_IDT_ISREntryTypeTask32             = 0x05,
    XEOS_HAL_IDT_ISREntryTypeInterrupt16        = 0x06,
    XEOS_HAL_IDT_ISREntryTypeTrap16             = 0x07,
    XEOS_HAL_IDT_ISREntryTypeInterrupt32        = 0x0E,
    XEOS_HAL_IDT_ISREntryTypeTrap32             = 0x0F
}
XEOS_HAL_IDT_ISREntryType;

/*!
 * @typedef         XEOS_HAL_IDT_ISREntryPrivilegeLevel
 * @abstract        Privilege level of an ISR entry
 * @constant        XEOS_HAL_IDT_ISREntryPrivilegeLevelRing0    Ring 0
 * @constant        XEOS_HAL_IDT_ISREntryPrivilegeLevelRing1    Ring 1
 * @constant        XEOS_HAL_IDT_ISREntryPrivilegeLevelRing2    Ring 2
 * @constant        XEOS_HAL_IDT_ISREntryPrivilegeLevelRing3    Ring 3
 */
typedef enum
{
    XEOS_HAL_IDT_ISREntryPrivilegeLevelRing0    = 0x00,
    XEOS_HAL_IDT_ISREntryPrivilegeLevelRing1    = 0x01,
    XEOS_HAL_IDT_ISREntryPrivilegeLevelRing2    = 0x02,
    XEOS_HAL_IDT_ISREntryPrivilegeLevelRing3    = 0x03
}
XEOS_HAL_IDT_ISREntryPrivilegeLevel;

/*!
 * @typedef         XEOS_HAL_IDT_ISRHandler
 * @abstract        Handler function for an ISR entry
 * @param           isr         The ISR number
 * @param           registers   The processor registers
 */
typedef void ( * XEOS_HAL_IDT_ISRHandler )( uint8_t isr, XEOS_HAL_CPU_Registers * registers );

/*!
 * @typedef         XEOS_HAL_IDT_ISREntryRef
 * @abstract        Opaque type for an ISR entry
 */
#ifdef __LP64__
typedef struct __XEOS_HAL_IDT_ISREntry64 * XEOS_HAL_IDT_ISREntryRef;
#else
typedef struct __XEOS_HAL_IDT_ISREntry32 * XEOS_HAL_IDT_ISREntryRef;
#endif

/*!
 * @function        XEOS_HAL_IDT_Init
 * @abstract        Initializes the Interrupt Descriptor Table (IDT)
 */
void XEOS_HAL_IDT_Init( void );

/*!
 * @function        XEOS_HAL_IDT_Reload
 * @abstract        Installs/Reload the Interrupt Descriptor Table (IDT)
 */
void XEOS_HAL_IDT_Reload( void );

/*!
 * @function        XEOS_HAL_IDT_GetISREntry
 * @abstract        Gets an ISR entry
 * @param           isr         The ISR number
 * @result          The ISR entry or NULL
 */
XEOS_HAL_IDT_ISREntryRef XEOS_HAL_IDT_GetISREntry( uint8_t isr );

/*!
 * @function        XEOS_HAL_IDT_SetISREntry
 * @abstract        Gets an ISR entry
 * @param           isr         The ISR number
 * @param           selector    The code segment selector
 * @param           type        The ISR entry type
 * @param           level       The privilege level
 * @param           present     The present flag
 * @param           handler     The ISR function handler
 */
void XEOS_HAL_IDT_SetISREntry( uint8_t isr, uint16_t selector, XEOS_HAL_IDT_ISREntryType type, XEOS_HAL_IDT_ISREntryPrivilegeLevel level, bool present, XEOS_HAL_IDT_ISRHandler handler );

/*!
 * @function        XEOS_HAL_IDT_ISREntrySetSelector
 * @abstract        Sets the code segment selector of an ISR entry
 * @param           entry       The ISR entry
 * @param           selector    The code segment selector
 */
void XEOS_HAL_IDT_ISREntrySetSelector( XEOS_HAL_IDT_ISREntryRef entry, uint16_t selector );

/*!
 * @function        XEOS_HAL_IDT_ISREntrySetType
 * @abstract        Sets the type of an ISR entry
 * @param           entry       The ISR entry
 * @param           type        The ISR entry type
 */
void XEOS_HAL_IDT_ISREntrySetType( XEOS_HAL_IDT_ISREntryRef entry, XEOS_HAL_IDT_ISREntryType type );

/*!
 * @function        XEOS_HAL_IDT_ISREntrySetPrivilegeLevel
 * @abstract        Sets the privilege level of an ISR entry
 * @param           entry       The ISR entry
 * @param           level       The privilege level
 */
void XEOS_HAL_IDT_ISREntrySetPrivilegeLevel( XEOS_HAL_IDT_ISREntryRef entry, XEOS_HAL_IDT_ISREntryPrivilegeLevel level );

/*!
 * @function        XEOS_HAL_IDT_ISREntrySetPresent
 * @abstract        Sets the present flag for an ISR entry
 * @param           entry       The ISR entry
 * @param           present     The present flag
 */
void XEOS_HAL_IDT_ISREntrySetPresent( XEOS_HAL_IDT_ISREntryRef entry, bool present );

/*!
 * @function        XEOS_HAL_IDT_ISREntrySetHandler
 * @abstract        Sets the function handler for an ISR entry
 * @param           entry       The ISR entry
 * @param           handler     The ISR function handler
 */
void XEOS_HAL_IDT_ISREntrySetHandler( XEOS_HAL_IDT_ISREntryRef entry, XEOS_HAL_IDT_ISRHandler handler );

/*!
 * @function        XEOS_HAL_IDT_ISREntryGetSelector
 * @abstract        Gets the code segment selector of an ISR entry
 * @param           entry       The ISR entry
 * @result          The code segment selector of the ISR entry
 */
uint16_t XEOS_HAL_IDT_ISREntryGetSelector( XEOS_HAL_IDT_ISREntryRef entry );

/*!
 * @function        XEOS_HAL_IDT_ISREntryGetType
 * @abstract        Gets the type of an ISR entry
 * @param           entry       The ISR entry
 * @result          The type of the ISR entry
 */
XEOS_HAL_IDT_ISREntryType XEOS_HAL_IDT_ISREntryGetType( XEOS_HAL_IDT_ISREntryRef entry );

/*!
 * @function        XEOS_HAL_IDT_ISREntryPrivilegeLevel
 * @abstract        Gets the privilege level of an ISR entry
 * @param           entry       The ISR entry
 * @result          The privilege level of the ISR entry
 */
XEOS_HAL_IDT_ISREntryPrivilegeLevel XEOS_HAL_IDT_ISREntryGetPrivilegeLevel( XEOS_HAL_IDT_ISREntryRef entry );

/*!
 * @function        XEOS_HAL_IDT_ISREntryGetPresent
 * @abstract        Gets the present flag of an ISR entry
 * @param           entry       The ISR entry
 * @result          The present flag of the ISR entry
 */
bool XEOS_HAL_IDT_ISREntryGetPresent( XEOS_HAL_IDT_ISREntryRef entry );

/*!
 * @function        XEOS_HAL_IDT_ISREntryGetHandler
 * @abstract        Gets the function handler of an ISR entry
 * @param           entry       The ISR entry
 * @result          The function handler of the ISR entry or NULL
 */
XEOS_HAL_IDT_ISRHandler XEOS_HAL_IDT_ISREntryGetHandler( XEOS_HAL_IDT_ISREntryRef entry );

/*!
 * @function        XEOS_HAL_IDT_ISREntryGetIndex
 * @abstract        Gets the index of an ISR entry in the IDT
 * @param           entry       The ISR entry
 * @result          THe ISR entry index
 */
int XEOS_HAL_IDT_ISREntryGetIndex( XEOS_HAL_IDT_ISREntryRef entry );

#ifdef __cplusplus
}
#endif

#endif /* __XEOS_HAL_IDT_H__ */
