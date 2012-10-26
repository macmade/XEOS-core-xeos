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

#include <stdbool.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Location of the video memory */
#define XEOS_VIDEO_MEM    0xB8000

/* BIOS screen dimensions */
#define XEOS_VIDEO_COLS   80
#define XEOS_VIDEO_ROWS   25

/* BIOS colors */
typedef enum
{
    XEOS_VIDEO_COLOR_BLACK        = 0x00,
    XEOS_VIDEO_COLOR_BLUE         = 0x01,
    XEOS_VIDEO_COLOR_GREEN        = 0x02,
    XEOS_VIDEO_COLOR_CYAN         = 0x03,
    XEOS_VIDEO_COLOR_RED          = 0x04,
    XEOS_VIDEO_COLOR_MAGENTA      = 0x05,
    XEOS_VIDEO_COLOR_BROWN        = 0x06,
    XEOS_VIDEO_COLOR_LIGHTGRAY    = 0x07,
    XEOS_VIDEO_COLOR_DARKGRAY     = 0x08,
    XEOS_VIDEO_COLOR_LIGHTBLUE    = 0x09,
    XEOS_VIDEO_COLOR_LIGHTGREEN   = 0x0A,
    XEOS_VIDEO_COLOR_LIGHTCYAN    = 0x0B,
    XEOS_VIDEO_COLOR_LIGHTRED     = 0x0C,
    XEOS_VIDEO_COLOR_LIGHTMAGENTA = 0x0D,
    XEOS_VIDEO_COLOR_LIGHTBROWN   = 0x0E,
    XEOS_VIDEO_COLOR_WHITE        = 0x0F
}
xeos_video_color;

void xeos_video_clear( void );
void xeos_video_set_bg( xeos_video_color color );
void xeos_video_set_fg( xeos_video_color color );
void xeos_video_cursor_move( unsigned int x, unsigned int y );
unsigned int xeos_video_cursor_x( void );
unsigned int xeos_video_cursor_y( void );
void xeos_video_prompt( char * s );
void xeos_video_promptf( char * format, ... );
void xeos_video_print( char * s );
void xeos_video_printf( char * format, ... );
void xeos_video_vprintf( char * format, va_list arg );
void xeos_video_putc( char c, bool update_cursor );
void xeos_video_scroll( unsigned int n );
void xeos_video_str_reverse( char s[] );
void xeos_video_itoa( int n, char s[], int radix );
void xeos_video_utoa( unsigned int n, char s[], int radix );

#ifdef __cplusplus
}
#endif

#endif /* __XEOS_VIDEO_H__ */
