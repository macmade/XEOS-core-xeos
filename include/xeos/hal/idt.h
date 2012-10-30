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

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define HAL_IDT_MAX_DESCRIPTORS 256

#define HAL_IDT_FLAG_16BITS     0x06    /* 00000110 */
#define HAL_IDT_FLAG_32BITS     0x0E    /* 00001110 */
#define HAL_IDT_FLAG_RING1      0x40    /* 01000000 */
#define HAL_IDT_FLAG_RING2      0x20    /* 00100000 */
#define HAL_IDT_FLAG_RING3      0x60    /* 01100000 */
#define HAL_IDT_FLAG_PRESENT    0x80    /* 10000000 */

/**
 * A descriptor for the IDT takes the following formats. Some of the format
 * changes depending on what type of descriptor this is:
 *      
 *      Bits 0-15:
 *          
 *          Interrupt:  Offset address - Bits 0-15 of IR address
 *          Trap Gate:  Offset address - Bits 0-15 of IR address
 *          Task Gate:  Not used.
 *      
 *      Bits 16-31:
 *          
 *          Interrupt:  Segment selector (useually 0x10)
 *          Trap Gate:  Segment selector (useually 0x10)
 *          Task Gate:  TSS Selector
 *      
 *      Bits 31-35:     Not used
 *      
 *      Bits 36-38:
 *          
 *          Interrupt:  Reserved. Must be 0.
 *          Trap Gate:  Reserved. Must be 0.
 *          Task Gate:  Not used.
 *      
 *      Bits 39-41:
 *          
 *          Interrupt:  Of the format 0D110, where D determins size:
 *              
 *              01110 - 32 bit descriptor
 *              00110 - 16 bit descriptor
 *              
 *          Trap Gate: Of the format 0D111, where D determins size
 *              
 *              01111 - 32 bit descriptor
 *              00111 - 16 bit descriptor
 *              
 *          Task Gate:  Must be 00101
 *      
 *      Bits 42-44: Descriptor Privilege Level (DPL)
 *          
 *          00:     Ring 0
 *          01:     Ring 1
 *          10:     Ring 2
 *          11:     Ring 3
 *      
 *      Bit 45: Segment is present (1: present, 0: not present)
 *      
 *      Bits 46-62:
 *          
 *          Interrupt:  Offset address - Bits 16-31 of IR address
 *          Trap Gate:  Offset address - Bits 16-31 of IR address
 *          Task Gate:  Not used
 */
struct hal_idt_entry
{
    uint16_t    address_low;
    uint16_t    selector;
    uint8_t     reserved;
    uint8_t     flags;
    uint16_t    address_high;
}
__attribute__( ( packed ) );

struct hal_idt_ptr
{
    uint16_t    limit;
    uint32_t    base;
}
__attribute__( ( packed ) );

typedef void ( * hal_irq_handler )( void );

void hal_idt_init( uint16_t sel, hal_irq_handler default_handler );
struct hal_idt_entry * hal_idt_get_descriptor( unsigned int i );
void hal_idt_set_descriptor( unsigned int i, hal_irq_handler handler, uint16_t sel, uint8_t flags );

#ifdef __cplusplus
}
#endif

#endif /* __HAL_IDT_H__ */
