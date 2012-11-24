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
 * @header          video.h
 * @author          Jean-David Gadina
 * @copyright       (c) 2010-2012, Jean-David Gadina <macmade@eosgarden.com>
 */

#ifndef __XEOS_VIDEO_H__
#define __XEOS_VIDEO_H__
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <xeos/macros.h>
#include <stdarg.h>
#include <stdbool.h>

/*!
 * @define      XEOS_VIDEO_MEM
 * @abstract    The video buffer location
 */
#define XEOS_VIDEO_MEM    0xB8000

/*!
 * @define      XEOS_VIDEO_COLS
 * @abstract    The number of video columns
 */
#define XEOS_VIDEO_COLS   80

/*!
 * @define      XEOS_VIDEO_ROWS
 * @abstract    The number of video rows
 */
#define XEOS_VIDEO_ROWS   25

/*!
 * @typedef     XEOS_Video_Color
 * @abstract    Video colors
 * @constant    XEOS_Video_ColorBlack           Black
 * @constant    XEOS_Video_ColorBlue            Dark blue
 * @constant    XEOS_Video_ColorGreen           Dark green
 * @constant    XEOS_Video_ColorCyan            Dark cyan
 * @constant    XEOS_Video_ColorRed             Dark red
 * @constant    XEOS_Video_ColorMagenta         Dark magenta
 * @constant    XEOS_Video_ColorBrown           Dark brown
 * @constant    XEOS_Video_ColorGrayLight       Light gray
 * @constant    XEOS_Video_ColorGray            Dark gray
 * @constant    XEOS_Video_ColorBlueLight       Light blue
 * @constant    XEOS_Video_ColorGreenLight      Light green
 * @constant    XEOS_Video_ColorCyanLight       Light cyan
 * @constant    XEOS_Video_ColorRedLight        Light red
 * @constant    XEOS_Video_ColorMagentaLight    Light magenta
 * @constant    XEOS_Video_ColorBrownLight      Light brown
 * @constant    XEOS_Video_ColorWhite           White
 */
typedef enum
{
    XEOS_Video_ColorBlack           = 0x00,
    XEOS_Video_ColorBlue            = 0x01,
    XEOS_Video_ColorGreen           = 0x02,
    XEOS_Video_ColorCyan            = 0x03,
    XEOS_Video_ColorRed             = 0x04,
    XEOS_Video_ColorMagenta         = 0x05,
    XEOS_Video_ColorBrown           = 0x06,
    XEOS_Video_ColorGrayLight       = 0x07,
    XEOS_Video_ColorGray            = 0x08,
    XEOS_Video_ColorBlueLight       = 0x09,
    XEOS_Video_ColorGreenLight      = 0x0A,
    XEOS_Video_ColorCyanLight       = 0x0B,
    XEOS_Video_ColorRedLight        = 0x0C,
    XEOS_Video_ColorMagentaLight    = 0x0D,
    XEOS_Video_ColorBrownLight      = 0x0E,
    XEOS_Video_ColorWhite           = 0x0F
}
XEOS_Video_Color;

/*!
 * @function    XEOS_Video_Clear
 * @abstract    Clears the screem
 */
void XEOS_Video_Clear( void );

/*!
 * @function    XEOS_Video_SetBG
 * @abstract    Sets the screen background color
 * @param       color       The background color
 */
void XEOS_Video_SetBG( XEOS_Video_Color color );

/*!
 * @function    XEOS_Video_SetFG
 * @abstract    Sets the screen foreground color
 * @param       color       The foregournd color
 */
void XEOS_Video_SetFG( XEOS_Video_Color color );

/*!
 * @function    XEOS_Video_MoveCursor
 * @abstract    Moves the hardware cursor
 * @param       x           The X position
 * @param       y           The Y position
 */
void XEOS_Video_MoveCursor( unsigned int x, unsigned int y );

/*!
 * @function    XEOS_Video_X
 * @abstract    Gets the hardware cursor's X position
 * @result      The X position
 */
unsigned int XEOS_Video_X( void );

/*!
 * @function    XEOS_Video_Y
 * @abstract    Gets the hardware cursor's X position
 * @result      The Y position
 */
unsigned int XEOS_Video_Y( void );

/*!
 * @function    XEOS_Video_Prompt
 * @abstract    Displays a message with the standard prompt
 * @param       s           The message
 * @result      The number of character printed
 */
int XEOS_Video_Prompt( const char * s );

/*!
 * @function    XEOS_Video_Promptf
 * @abstract    Displays a formatted message with the standard prompt
 * @param       format      The message format
 * @result      The number of character printed
 */
int XEOS_Video_Promptf( const char * format, ... );

/*!
 * @function    XEOS_Video_Print
 * @abstract    Displays a message
 * @param       s           The message
 * @result      The number of character printed
 */
int XEOS_Video_Print( const char * s );

/*!
 * @function    XEOS_Video_Printf
 * @abstract    Displays a formatted message
 * @param       format      The message format
 * @result      The number of character printed
 */
int XEOS_Video_Printf( const char * format, ... );

/*!
 * @function    XEOS_Video_VPrintf
 * @abstract    Displays a formatted message
 * @param       format      The message format
 * @param       arg         The arguments for the format
 * @result      The number of character printed
 */
int XEOS_Video_VPrintf( const char * format, va_list arg );

/*!
 * @function    XEOS_Video_Putc
 * @abstract    Displays a single character
 * @param       c               The character to display
 * @param       updateCursor    If set, updates the hardware cursor
 */
void XEOS_Video_Putc( char c, bool updateCursor );

/*!
 * @function    XEOS_Video_Scroll
 * @abstract    Scrolls the screen
 * @param       n           The number of lines to scroll
 */
void XEOS_Video_Scroll( unsigned int n );

#ifdef __cplusplus
}
#endif

#endif /* __XEOS_VIDEO_H__ */
