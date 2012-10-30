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

#ifndef __XEOS_VIDEO_H__
#define __XEOS_VIDEO_H__
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>
#include <stdbool.h>

#define XEOS_VIDEO_MEM    0xB8000
#define XEOS_VIDEO_COLS   80
#define XEOS_VIDEO_ROWS   25

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

void XEOS_Video_Clear( void );
void XEOS_Video_SetBG( XEOS_Video_Color color );
void XEOS_Video_SetFG( XEOS_Video_Color color );
void XEOS_Video_MoveCursor( unsigned int x, unsigned int y );
unsigned int XEOS_Video_X( void );
unsigned int XEOS_Video_Y( void );
void XEOS_Video_Prompt( char * s );
void XEOS_Video_Promptf( char * format, ... );
void XEOS_Video_Print( char * s );
void XEOS_Video_Printf( char * format, ... );
void XEOS_Video_VPrintf( char * format, va_list arg );
void XEOS_Video_Putc( unsigned char c, bool updateCursor );
void XEOS_Video_Scroll( unsigned int n );
void XEOS_Video_StringReverse( char s[] );
void XEOS_Video_Itoa( int n, char s[], int radix );
void XEOS_Video_Utoa( unsigned int n, char s[], int radix );

extern unsigned char    __XEOS_Video_Attribute;
extern unsigned int     __XEOS_Video_X;
extern unsigned int     __XEOS_Video_Y;
extern char           * __XEOS_Video_Prompt;
extern char             __XEOS_Video_HexChars[ 16 ];

#ifdef __cplusplus
}
#endif

#endif /* __XEOS_VIDEO_H__ */
