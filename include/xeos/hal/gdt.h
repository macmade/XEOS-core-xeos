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

#ifndef __HAL_GDT_H__
#define __HAL_GDT_H__
#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define HAL_GDT_MAX_DESCRIPTORS 5

/**
 * A descriptor for the GDT takes the following format:
 *      
 *      Bits  0 - 15:   Segment limit (0-15)
 * 
 *      Bits 16 - 30:   Base address (0-23)
 * 
 *      Bit  40:        Access bit (only for virtual memory)
 * 
 *      Bits 41 - 43:   Descriptor type
 * 
 *                          Bit 41: Readable and writeable
 *                                      0:  Read only (data segment)
 *                                          Execute only (code segment)
 *                                      1:  Read and write (data segment)
 *                                      1:  Read and execute (code segment)
 *                          Bit 42: Expansion direction (for data segment)
 *                                  or conforming (code segment)
 *                          Bit 43: Executable segment
 *                                      0:  Data segment
 *                                      1:  Code segment
 * 
 *      Bit  44:        Descriptor bit
 * 
 *                          0:      System descriptor
 *                          1:      Code or data descriptor
 * 
 *      Bits 45 - 46:   Descriptor privilege level (rings 0 to 3)
 * 
 *      Bit  47:        Segment is in memory (only for virtual memory)
 * 
 *      Bits 48 - 51:   Segment limit (16-19)
 * 
 *      Bit  52:        Reserved (for OS)
 * 
 *      Bit  53:        Reserved
 * 
 *      Bit  54:        Segment type
 * 
 *                          0:      16 bits
 *                          1:      32 bits
 * 
 *      Bit  55:        Granularity
 * 
 *                          0:      None
 *                          1:      Limit is multiplied by 4K
 * 
 *      Bits 56 - 63:   Base address (24-31)
 */
struct hal_gdt_entry
{
    uint16_t    limit;
    uint16_t    address_low;
    uint8_t     address_mid;
    uint16_t    flags;
    uint8_t     address_high;
}
__attribute__( ( packed ) );

struct hal_gdt_ptr
{
    uint16_t    limit;
    uint32_t    base;
}
__attribute__( ( packed ) );

void hal_gdt_init( void );
struct hal_gdt_entry * hal_gdt_get_descriptor( unsigned int i );
void hal_gdt_set_descriptor( unsigned int i );

#ifdef __cplusplus
}
#endif

#endif /* __HAL_GDT_H__ */
