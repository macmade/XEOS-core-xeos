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
 * @header          keboard.h
 * @author          Jean-David Gadina
 * @copyright       (c) 2010-2013, Jean-David Gadina - www.xs-labs.com
 */

#ifndef __XEOS_HAL_KEYBOARD_H__
#define __XEOS_HAL_KEYBOARD_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef enum
{
    XEOS_HAL_Keyboard_CommandSetLED                 = 0xED,
    XEOS_HAL_Keyboard_CommandEcho                   = 0xEE,
    XEOS_HAL_Keyboard_CommandScanCode               = 0xF0,
    XEOS_HAL_Keyboard_CommandSetRateAndDelay        = 0xF3,
    XEOS_HAL_Keyboard_CommandEnableScan             = 0xF4,
    XEOS_HAL_Keyboard_CommandDisableScan            = 0xF5,
    XEOS_HAL_Keyboard_CommandSetDefaultParameters   = 0xF6,
    XEOS_HAL_Keyboard_CommandResendLastByte         = 0xFE,
    XEOS_HAL_Keyboard_CommandReset                  = 0xFF
}
XEOS_HAL_Keyboard_Command;

typedef enum
{
    XEOS_HAL_Keyboard_ResponseACK                   = 0xFA,
    XEOS_HAL_Keyboard_ResponseResend                = 0xFE,
    XEOS_HAL_Keyboard_ResponseEcho                  = 0xEE,
    XEOS_HAL_Keyboard_ResponseSelfTestPassed        = 0xAA,
    XEOS_HAL_Keyboard_ResponseSelfTestFailed        = 0xFD
}
XEOS_HAL_Keyboard_Response;

typedef enum
{
    XEOS_HAL_Keyboard_LEDStateScrollLock            = 0x01,
    XEOS_HAL_Keyboard_LEDStateNumLock               = 0x02,
    XEOS_HAL_Keyboard_LEDStateCapsLock              = 0x04
}
XEOS_HAL_Keyboard_LEDState;

typedef enum
{
    XEOS_HAL_Keyboard_ScanCodeSetUnknown            = 0x00,
    XEOS_HAL_Keyboard_ScanCodeSet1                  = 0x01,
    XEOS_HAL_Keyboard_ScanCodeSet2                  = 0x02,
    XEOS_HAL_Keyboard_ScanCodeSet3                  = 0x03
}
XEOS_HAL_Keyboard_ScanCodeSet;

// IRQ1 needs to be disabled or masked
XEOS_HAL_Keyboard_Response      XEOS_HAL_Keyboard_SendCommand( XEOS_HAL_Keyboard_Command command );
XEOS_HAL_Keyboard_Response      XEOS_HAL_Keyboard_SendCommandWithData( XEOS_HAL_Keyboard_Command command, uint8_t data );
uint8_t                         XEOS_HAL_Keyboard_ReadData( void );

XEOS_HAL_Keyboard_Response      XEOS_HAL_Keyboard_SetLED( XEOS_HAL_Keyboard_LEDState state );
XEOS_HAL_Keyboard_Response      XEOS_HAL_Keyboard_Echo( void );
XEOS_HAL_Keyboard_Response      XEOS_HAL_Keyboard_SetScanCodeSet( XEOS_HAL_Keyboard_ScanCodeSet set );
XEOS_HAL_Keyboard_ScanCodeSet   XEOS_HAL_Keyboard_GetScanCodeSet( void );
XEOS_HAL_Keyboard_Response      XEOS_HAL_Keyboard_SetRateAndDelay( uint8_t value );
XEOS_HAL_Keyboard_Response      XEOS_HAL_Keyboard_EnableScan( void );
XEOS_HAL_Keyboard_Response      XEOS_HAL_Keyboard_DisableScan( void );
XEOS_HAL_Keyboard_Response      XEOS_HAL_Keyboard_SetDefaultParameters( void );
XEOS_HAL_Keyboard_Response      XEOS_HAL_Keyboard_ResendLastByte( void );
XEOS_HAL_Keyboard_Response      XEOS_HAL_Keyboard_Reset( void );

#ifdef __cplusplus
}
#endif

#endif /* __XEOS_HAL_KEYBOARD_H__ */
