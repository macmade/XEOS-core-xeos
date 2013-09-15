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
 * @header          gui.h
 * @author          Jean-David Gadina
 * @copyright       (c) 2010-2013, Jean-David Gadina - www.xs-labs.com
 */

#ifndef __XEOS_GUI_H__
#define __XEOS_GUI_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <system/macros.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>
#include <system/types/size_t.h>

typedef struct
{
    uint32_t x;
    uint32_t y;
}
XEOS_GUI_Point;

typedef struct
{
    uint32_t width;
    uint32_t height;
}
XEOS_GUI_Size;

typedef struct
{
    XEOS_GUI_Point origin;
    XEOS_GUI_Size  size;
}
XEOS_GUI_Rect;

typedef struct
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
}
XEOS_GUI_Color;

typedef enum
{
    XEOS_GUI_PredefinedColorBlack               = 0x00,
    XEOS_GUI_PredefinedColorWhite               = 0x01,
    XEOS_GUI_PredefinedColorGray                = 0x02,
    XEOS_GUI_PredefinedColorLightGray           = 0x03,
    XEOS_GUI_PredefinedColorRed                 = 0x04,
    XEOS_GUI_PredefinedColorGreen               = 0x05,
    XEOS_GUI_PredefinedColorBlue                = 0x06,
    XEOS_GUI_PredefinedColorMagenta             = 0x07,
    XEOS_GUI_PredefinedColorCyan                = 0x08,
    XEOS_GUI_PredefinedColorYellow              = 0x09,
    XEOS_GUI_PredefinedColorScreenBackground    = 0x0A, 
    XEOS_GUI_PredefinedColorWindowBackground    = 0x0B
}
XEOS_GUI_PredefinedColor;

typedef enum
{
    XEOS_GUI_BitmapFontTraitsNormal             = 0x00,
    XEOS_GUI_BitmapFontTraitsMonospace          = 0x01
}
XEOS_GUI_BitmapFontTraits;

typedef struct __XEOS_GUI_BitmapFont      * XEOS_GUI_BitmapFontRef;
typedef struct __XEOS_GUI_BitmapFontGlyph * XEOS_GUI_BitmapFontGlyphRef;

XEOS_GUI_Point  XEOS_GUI_MakePoint( uint32_t x, uint32_t y );
XEOS_GUI_Size   XEOS_GUI_MakeSize( uint32_t width, uint32_t height );
XEOS_GUI_Rect   XEOS_GUI_MakeRect( uint32_t x, uint32_t y, uint32_t width, uint32_t height );

XEOS_GUI_Color  XEOS_GUI_GetPredefinedColor( XEOS_GUI_PredefinedColor colorStyle );
void            XEOS_GUI_SetPredefinedColor( XEOS_GUI_PredefinedColor colorStyle, XEOS_GUI_Color color );

XEOS_GUI_BitmapFontRef      XEOS_GUI_BitmapFontGetBitmapFont( const char * name, uint32_t size, uint32_t traits );
XEOS_GUI_BitmapFontRef      XEOS_GUI_BitmapFontGetSystemBitmapFont( void );
XEOS_GUI_BitmapFontRef      XEOS_GUI_BitmapFontGetMonospaceSystemBitmapFont( void );
uint32_t                    XEOS_GUI_BitmapFontGetSystemBitmapFontSize( void );

const char                * XEOS_GUI_BitmapFontGetName( XEOS_GUI_BitmapFontRef font );
uint32_t                    XEOS_GUI_BitmapFontGetSize( XEOS_GUI_BitmapFontRef font );
uint32_t                    XEOS_GUI_BitmapFontGetTraits( XEOS_GUI_BitmapFontRef font );
size_t                      XEOS_GUI_BitmapFontGetGlyphCount( XEOS_GUI_BitmapFontRef font );
uint32_t                    XEOS_GUI_BitmapFontGetGlyphHeight( XEOS_GUI_BitmapFontRef font );
XEOS_GUI_BitmapFontGlyphRef XEOS_GUI_BitmapFontGetGlyphAtIndex( XEOS_GUI_BitmapFontRef font, uint32_t index );

uint32_t    XEOS_GUI_BitmapFontGlyphGetWidth( XEOS_GUI_BitmapFontGlyphRef glyph );
void      * XEOS_GUI_BitmapFontGlyphGetData( XEOS_GUI_BitmapFontGlyphRef glyph );

void            XEOS_GUI_ClearScreen( void );
XEOS_GUI_Point  XEOS_GUI_GetCursorPosition( void );
void            XEOS_GUI_SetCursorPosition( XEOS_GUI_Point point );

int     XEOS_GUI_Prompt( const char * s );
int     XEOS_Video_Promptf( const char * format, ... ) FORMAT_ATTRIBUTE( printf, 1, 2 );
int     XEOS_Video_Print( const char * s );
int     XEOS_Video_Printf( const char * format, ... ) FORMAT_ATTRIBUTE( printf, 1, 2 );
int     XEOS_Video_VPrintf( const char * format, va_list arg );
void    XEOS_Video_Putc( char c, bool updateCursor );
void    XEOS_Video_Scroll( uint32_t lines );

#ifdef __cplusplus
}
#endif

#endif /* __XEOS_GUI_H__ */
