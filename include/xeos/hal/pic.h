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
 * @header          pic.h
 * @author          Jean-David Gadina
 * @copyright       (c) 2010-2012, Jean-David Gadina <macmade@eosgarden.com>
 */

#ifndef __XEOS_HAL_PIC_H__
#define __XEOS_HAL_PIC_H__
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/*!
 * @enum        XEOS_HAL_PIC_Controller
 * @abstract    Programmable Interrupt Controller
 * @constant    XEOS_HAL_PIC_Controller1    Master PIC
 * @constant    XEOS_HAL_PIC_Controller2    Slave PIC
 */
typedef enum
{
    XEOS_HAL_PIC_Controller1        = 0x00,
    XEOS_HAL_PIC_Controller2        = 0x01
}
XEOS_HAL_PIC_Controller;

/*!
 * @enum        XEOS_HAL_PIC_Register
 * @abstract    PIC register
 * @constant    XEOS_HAL_PIC_RegisterCommand    PIC command register
 * @constant    XEOS_HAL_PIC_RegisterStatus     PIC status register
 * @constant    XEOS_HAL_PIC_RegisterData       PIC data register
 */
typedef enum
{
    XEOS_HAL_PIC_RegisterCommand    = 0x00,
    XEOS_HAL_PIC_RegisterStatus     = 0x01,
    XEOS_HAL_PIC_RegisterData       = 0x02,
}
XEOS_HAL_PIC_Register;

/*!
 * @enum        XEOS_HAL_PIC_ICW1
 * @abstract    PIC Initialization Command Word (ICW) 1
 * @constant    XEOS_HAL_PIC_ICW1None   No value
 * @constant    XEOS_HAL_PIC_ICW1IC4    PIC expects to recieve IC4 during initialization
 * @constant    XEOS_HAL_PIC_ICW1SNGL   Only one PIC in system
 * @constant    XEOS_HAL_PIC_ICW1ADI    CALL address interval is 4
 * @constant    XEOS_HAL_PIC_ICW1LTIM   Operate in Level Triggered Mode
 * @constant    XEOS_HAL_PIC_ICW1Init   PIC needs to be initialized
 */
typedef enum
{
    XEOS_HAL_PIC_ICW1None           = 0x00,
    XEOS_HAL_PIC_ICW1IC4            = 0x01,
    XEOS_HAL_PIC_ICW1SNGL           = 0x02,
    XEOS_HAL_PIC_ICW1ADI            = 0x04,
    XEOS_HAL_PIC_ICW1LTIM           = 0x08,
    XEOS_HAL_PIC_ICW1Init           = 0x10
}
XEOS_HAL_PIC_ICW1;

/*!
 * @enum        XEOS_HAL_PIC_ICW4
 * @abstract    PIC Initialization Command Word (ICW) 4
 * @constant    XEOS_HAL_PIC_ICW4None   No value
 * @constant    XEOS_HAL_PIC_ICW4UPM    80x86 mode
 * @constant    XEOS_HAL_PIC_ICW4AEOI   Performs EOI (End Of Interrupt) on the last interrupt acknowledge pulse
 * @constant    XEOS_HAL_PIC_ICW4MS     Selects buffer master
 * @constant    XEOS_HAL_PIC_ICW4BUF    Operates in buffered mode
 * @constant    XEOS_HAL_PIC_ICW4SFNM   Special fully nested mode
 */
typedef enum
{
    XEOS_HAL_PIC_ICW4None           = 0x00,
    XEOS_HAL_PIC_ICW4UPM            = 0x01,
    XEOS_HAL_PIC_ICW4AEOI           = 0x02,
    XEOS_HAL_PIC_ICW4MS             = 0x04,
    XEOS_HAL_PIC_ICW4BUF            = 0x08,
    XEOS_HAL_PIC_ICW4SFNM           = 0x10
}
XEOS_HAL_PIC_ICW4;

/*!
 * @function        XEOS_HAL_PIC_Remap
 * @abstract        Remaps the PIC (Programmable Interrupt Controller)
 * @param           masterBase      The base IRQ number for the master controller
 * @param           slaveBase       The base IRQ number for the slave controller
 */
void XEOS_HAL_PIC_Remap( uint8_t masterBase, uint8_t slaveBase );

/*!
 * @function        XEOS_HAL_PIC_GetRegister
 * @abstract        Gets the register number for a PIC register
 * @param           c               The PIC
 * @param           r               The PIC register
 * @result          The register number
 */
uint8_t XEOS_HAL_PIC_GetRegister( XEOS_HAL_PIC_Controller c, XEOS_HAL_PIC_Register r );

/*!
 * @function        XEOS_HAL_PIC_SendCommand
 * @abstract        Sends a command to a PIC
 * @param           c               The PIC
 * @param           command         The command to send
 */
void XEOS_HAL_PIC_SendCommand( XEOS_HAL_PIC_Controller c, uint8_t command );

/*!
 * @function        XEOS_HAL_PIC_ReadData
 * @abstract        Reads data from a PIC
 * @param           c               The PIC
 * @result          The data read
 */
uint8_t XEOS_HAL_PIC_ReadData( XEOS_HAL_PIC_Controller c );

/*!
 * @function        XEOS_HAL_PIC_SendData
 * @abstract        Sends data to a PIC
 * @param           c               The PIC
 * @param           data            The data to send
 */
void XEOS_HAL_PIC_SendData( XEOS_HAL_PIC_Controller c, uint8_t data );

#ifdef __cplusplus
}
#endif

#endif /* __XEOS_HAL_PIC_H__ */
