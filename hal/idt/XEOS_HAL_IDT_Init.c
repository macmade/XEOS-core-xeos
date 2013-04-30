/*******************************************************************************
 * XEOS - X86 Experimental Operating System
 * 
 * Copyright (c) 2010-2012, Jean-David Gadina - www.xs-labs.com
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
 * @file            XEOS_HAL_IDT_Init.c
 * @author          Jean-David Gadina
 * @copyright       (c) 2010-2012, Jean-David Gadina - www.xs-labs.com
 */

#include "xeos/hal/idt.h"
#include "xeos/hal/__idt.h"
#include <string.h>

#ifdef __LP64__
    
    #define __XEOS_HAL_IDT_INIT_ISR( _i_ )                                                          \
                                                                                                    \
        {                                                                                           \
            __XEOS_HAL_IDT_ISREntry * entry;                                                        \
                                                                                                    \
            void ( * isr )( void );                                                                 \
                                                                                                    \
            __asm__ __volatile__                                                                    \
            (                                                                                       \
                "leaq __XEOS_HAL_IDT_ISR_" # _i_ ", %[isr];"                                        \
                : [ isr ] "=r" ( isr )                                                              \
                :                                                                                   \
            );                                                                                      \
                                                                                                    \
            entry = &(  __XEOS_HAL_IDT_ISREntries[ 0x ## _i_ ] );                                   \
                                                                                                    \
            entry->baseLow    = ( uint16_t )(   ( uintptr_t )&( * isr )       & 0x0000FFFF );       \
            entry->baseMiddle = ( uint16_t )( ( ( uintptr_t )&( * isr ) >> 16 & 0x0000FFFF ) );     \
            entry->baseHigh   = ( uint32_t )( ( ( uintptr_t )&( * isr ) >> 32 & 0xFFFFFFFF ) );     \
        }
        
#else
    
    #define __XEOS_HAL_IDT_INIT_ISR( _i_ )                                                          \
                                                                                                    \
        {                                                                                           \
            __XEOS_HAL_IDT_ISREntry * entry;                                                        \
                                                                                                    \
            void ( * isr )( void );                                                                 \
                                                                                                    \
            __asm__ __volatile__                                                                    \
            (                                                                                       \
                "leal __XEOS_HAL_IDT_ISR_" # _i_ ", %[isr];"                                        \
                : [ isr ] "=r" ( isr )                                                              \
                :                                                                                   \
            );                                                                                      \
                                                                                                    \
            entry = &(  __XEOS_HAL_IDT_ISREntries[ 0x ## _i_ ] );                                   \
                                                                                                    \
            entry->baseLow    = ( uint16_t )(   ( uintptr_t )&( * isr )       & 0x0000FFFF );       \
            entry->baseHigh   = ( uint16_t )( ( ( uintptr_t )&( * isr ) >> 16 & 0x0000FFFF ) );     \
        }
    
#endif

#define __XEOS_HAL_IDT_INIT_ISR_GROUP( _i_ )    \
        __XEOS_HAL_IDT_INIT_ISR( _i_ ## 0 )     \
        __XEOS_HAL_IDT_INIT_ISR( _i_ ## 1 )     \
        __XEOS_HAL_IDT_INIT_ISR( _i_ ## 2 )     \
        __XEOS_HAL_IDT_INIT_ISR( _i_ ## 3 )     \
        __XEOS_HAL_IDT_INIT_ISR( _i_ ## 4 )     \
        __XEOS_HAL_IDT_INIT_ISR( _i_ ## 5 )     \
        __XEOS_HAL_IDT_INIT_ISR( _i_ ## 6 )     \
        __XEOS_HAL_IDT_INIT_ISR( _i_ ## 7 )     \
        __XEOS_HAL_IDT_INIT_ISR( _i_ ## 8 )     \
        __XEOS_HAL_IDT_INIT_ISR( _i_ ## 9 )     \
        __XEOS_HAL_IDT_INIT_ISR( _i_ ## A )     \
        __XEOS_HAL_IDT_INIT_ISR( _i_ ## B )     \
        __XEOS_HAL_IDT_INIT_ISR( _i_ ## C )     \
        __XEOS_HAL_IDT_INIT_ISR( _i_ ## D )     \
        __XEOS_HAL_IDT_INIT_ISR( _i_ ## E )     \
        __XEOS_HAL_IDT_INIT_ISR( _i_ ## F )

void XEOS_HAL_IDT_Init( void )
{
    unsigned int             i;
    XEOS_HAL_IDT_ISREntryRef isrEntry;
    
    memset( &__XEOS_HAL_IDT_Address,     0, sizeof( __XEOS_HAL_IDT_Pointer ) );
    memset(  __XEOS_HAL_IDT_ISREntries,  0, sizeof( __XEOS_HAL_IDT_ISREntry ) * XEOS_HAL_IDT_MAX_DESCRIPTORS );
    memset(  __XEOS_HAL_IDT_ISRHandlers, 0, sizeof( XEOS_HAL_IDT_ISRHandler ) * XEOS_HAL_IDT_MAX_DESCRIPTORS );
    
    __XEOS_HAL_IDT_INIT_ISR_GROUP( 0 )
    __XEOS_HAL_IDT_INIT_ISR_GROUP( 1 )
    __XEOS_HAL_IDT_INIT_ISR_GROUP( 2 )
    __XEOS_HAL_IDT_INIT_ISR_GROUP( 3 )
    __XEOS_HAL_IDT_INIT_ISR_GROUP( 4 )
    __XEOS_HAL_IDT_INIT_ISR_GROUP( 5 )
    __XEOS_HAL_IDT_INIT_ISR_GROUP( 6 )
    __XEOS_HAL_IDT_INIT_ISR_GROUP( 7 )
    __XEOS_HAL_IDT_INIT_ISR_GROUP( 8 )
    __XEOS_HAL_IDT_INIT_ISR_GROUP( 9 )
    __XEOS_HAL_IDT_INIT_ISR_GROUP( A )
    __XEOS_HAL_IDT_INIT_ISR_GROUP( B )
    __XEOS_HAL_IDT_INIT_ISR_GROUP( C )
    __XEOS_HAL_IDT_INIT_ISR_GROUP( D )
    __XEOS_HAL_IDT_INIT_ISR_GROUP( E )
    __XEOS_HAL_IDT_INIT_ISR_GROUP( F )
    
    for( i = 0; i < XEOS_HAL_IDT_MAX_DESCRIPTORS; i++ )
    {
        isrEntry = XEOS_HAL_IDT_GetISREntry( ( uint8_t )i );
        
        XEOS_HAL_IDT_ISREntrySetSelector( isrEntry, 0x08 );
        XEOS_HAL_IDT_ISREntrySetType( isrEntry, XEOS_HAL_IDT_ISREntryTypeInterrupt32 );
        XEOS_HAL_IDT_ISREntrySetPrivilegeLevel( isrEntry, XEOS_HAL_IDT_ISREntryPrivilegeLevelRing3 );
        XEOS_HAL_IDT_ISREntrySetPresent( isrEntry, true );
        XEOS_HAL_IDT_ISREntrySetHandler( isrEntry, NULL );
    }
    
    __XEOS_HAL_IDT_Address.limit = ( uint16_t )( sizeof( __XEOS_HAL_IDT_ISREntry ) * XEOS_HAL_IDT_MAX_DESCRIPTORS ) - 1;
    
    #ifdef __LP64__
        
        __XEOS_HAL_IDT_Address.base = ( uint64_t )&__XEOS_HAL_IDT_ISREntries;
        
    #else
        
        __XEOS_HAL_IDT_Address.base = ( uint32_t )&__XEOS_HAL_IDT_ISREntries;
        
    #endif
    
    XEOS_HAL_IDT_Reload();
}
