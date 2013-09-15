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
 * @file            __XEOS_GUI.c
 * @author          Jean-David Gadina
 * @copyright       (c) 2010-2013, Jean-David Gadina - www.xs-labs.com
 */

#include <xeos/gui.h>
#include <xeos/__private/gui.h>

XEOS_GUI_Color __XEOS_GUI_Color_Black                               = { 0x1B, 0x1E, 0x22 };
XEOS_GUI_Color __XEOS_GUI_Color_White                               = { 0xFF, 0xFF, 0xFF };
XEOS_GUI_Color __XEOS_GUI_Color_Gray                                = { 0x80, 0x80, 0x80 };
XEOS_GUI_Color __XEOS_GUI_Color_LightGray                           = { 0xCB, 0xCB, 0xCB };
XEOS_GUI_Color __XEOS_GUI_Color_Red                                 = { 0xAB, 0x48, 0x43 };
XEOS_GUI_Color __XEOS_GUI_Color_Green                               = { 0x7F, 0x99, 0x60 };
XEOS_GUI_Color __XEOS_GUI_Color_Blue                                = { 0x7A, 0x9E, 0xBF };
XEOS_GUI_Color __XEOS_GUI_Color_Magenta                             = { 0xB1, 0x97, 0xC9 };
XEOS_GUI_Color __XEOS_GUI_Color_Cyan                                = { 0x88, 0xBD, 0xBE };
XEOS_GUI_Color __XEOS_GUI_Color_Yellow                              = { 0xB3, 0xAB, 0x4A };
XEOS_GUI_Color __XEOS_GUI_Color_ScreenBackground                    = { 0x5F, 0x5E, 0x7A };
XEOS_GUI_Color __XEOS_GUI_Color_WindowBackground                    = { 0xDE, 0xDE, 0xDE };

const char * __XEOS_GUI_SystemBitmapFontName                        = "System";
uint32_t     __XEOS_GUI_SystemBitmapFontSize                        = 10;

static struct __XEOS_GUI_BitmapFont __XEOS_GUI_BitmapFontsArray[]   =
{
    /***************************************************************************
     * System font - Normal - 10
     **************************************************************************/
    {
        "System",
        10,
        12,
        XEOS_GUI_BitmapFontTraitsNormal,
        127,
        ( struct __XEOS_GUI_BitmapFontGlyph [] ){
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+0000 */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+0001 */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+0002 */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+0003 */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+0004 */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+0005 */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+0006 */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+0007 */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+0008 */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+0009 */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+000A */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+000B */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+000C */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+000D */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+000E */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+000F */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+0010 */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+0011 */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+0012 */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+0013 */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+0014 */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+0015 */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+0016 */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+0017 */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+0018 */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+0019 */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+001A */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+001B */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+001C */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+001D */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+001E */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+001F */
            
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 } },    /* U+0020 - ( ) */
            { 3, 0, ( uint32_t [] ){ 0x0000, 0x017E, 0x0000 } },                                            /* U+0021 - (!) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0016, 0x000E, 0x0000, 0x0016, 0x000E, 0x0000 } },            /* U+0022 - (") */
            { 8, 0, ( uint32_t [] ){ 0x0000, 0x0048, 0x01C8, 0x007E, 0x01C8, 0x007E, 0x0048, 0x0000 } },    /* U+0023 - (#) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x008C, 0x0112, 0x03FF, 0x0122, 0x00C4, 0x0000 } },            /* U+0024 - ($) */
            { 8, 0, ( uint32_t [] ){ 0x0000, 0x018C, 0x0052, 0x002C, 0x00D0, 0x0128, 0x00C6, 0x0000 } },    /* U+0025 - (%) */
            { 8, 0, ( uint32_t [] ){ 0x0000, 0x00EC, 0x0112, 0x0122, 0x0144, 0x0080, 0x0140, 0x0000 } },    /* U+0026 - (&) */
            { 4, 0, ( uint32_t [] ){ 0x0000, 0x0016, 0x000E, 0x0000 } },                                    /* U+0027 - (') */
            { 6, 0, ( uint32_t [] ){ 0x0000, 0x00F0, 0x030C, 0x0402, 0x0801, 0x0000 } },                    /* U+0028 - (() */
            { 6, 0, ( uint32_t [] ){ 0x0000, 0x0801, 0x0402, 0x030C, 0x00F0, 0x0000 } },                    /* U+0029 - ()) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0024, 0x0018, 0x007E, 0x0018, 0x0024, 0x0000 } },            /* U+002A - (*) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0040, 0x0040, 0x01F0, 0x0040, 0x0040, 0x0000 } },            /* U+002B - (+) */
            { 4, 0, ( uint32_t [] ){ 0x0000, 0x0580, 0x0380, 0x0000 } },                                    /* U+002C - (,) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0040, 0x0040, 0x0040, 0x0040, 0x0040, 0x0000 } },            /* U+002D - (-) */
            { 4, 0, ( uint32_t [] ){ 0x0000, 0x0180, 0x0180, 0x0000 } },                                    /* U+002E - (.) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0300, 0x00C0, 0x0020, 0x0018, 0x0006, 0x0000 } },            /* U+002F - (/) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x00FC, 0x0122, 0x0112, 0x010A, 0x00FC, 0x0000 } },            /* U+0030 - (0) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0108, 0x0104, 0x01FE, 0x0100, 0x0100, 0x0000 } },            /* U+0031 - (1) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0184, 0x0142, 0x0122, 0x0112, 0x010C, 0x0000 } },            /* U+0032 - (2) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0084, 0x0102, 0x0112, 0x0112, 0x00EC, 0x0000 } },            /* U+0033 - (3) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0030, 0x0028, 0x0024, 0x01FE, 0x0020, 0x0000 } },            /* U+0034 - (4) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x013E, 0x0112, 0x0112, 0x0112, 0x00E2, 0x0000 } },            /* U+0035 - (5) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x00F8, 0x0114, 0x0112, 0x0112, 0x00E0, 0x0000 } },            /* U+0036 - (6) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0006, 0x0002, 0x01C2, 0x0032, 0x000E, 0x0000 } },            /* U+0037 - (7) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x00EC, 0x0112, 0x0112, 0x0112, 0x00EC, 0x0000 } },            /* U+0038 - (8) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x001C, 0x0122, 0x0122, 0x00A2, 0x007C, 0x0000 } },            /* U+0039 - (9) */
            { 4, 0, ( uint32_t [] ){ 0x0000, 0x0198, 0x0198, 0x0000 } },                                    /* U+003A - (:) */
            { 4, 0, ( uint32_t [] ){ 0x0000, 0x0598, 0x0398, 0x0000 } },                                    /* U+003B - (;) */
            { 8, 0, ( uint32_t [] ){ 0x0000, 0x0040, 0x0040, 0x00A0, 0x00A0, 0x0110, 0x0110, 0x0000 } },    /* U+003C - (<) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x00A0, 0x00A0, 0x00A0, 0x00A0, 0x00A0, 0x0000 } },            /* U+003D - (=) */
            { 8, 0, ( uint32_t [] ){ 0x0000, 0x0110, 0x0110, 0x00A0, 0x00A0, 0x0040, 0x0040, 0x0000 } },    /* U+003E - (>) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0004, 0x0002, 0x0162, 0x0012, 0x000C, 0x0000 } },            /* U+003F - (?) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0078, 0x0084, 0x0132, 0x014A, 0x017C, 0x0000 } },            /* U+0040 - (@) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x01C0, 0x0070, 0x004E, 0x0070, 0x01C0, 0x0000 } },            /* U+0041 - (A) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x01FE, 0x0112, 0x0112, 0x0112, 0x00EC, 0x0000 } },            /* U+0042 - (B) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x00FC, 0x0102, 0x0102, 0x0102, 0x0084, 0x0000 } },            /* U+0043 - (C) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x01FE, 0x0102, 0x0102, 0x0084, 0x0078, 0x0000 } },            /* U+0044 - (D) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x01FE, 0x0112, 0x0112, 0x0112, 0x0102, 0x0000 } },            /* U+0045 - (E) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x01FE, 0x0012, 0x0012, 0x0012, 0x0002, 0x0000 } },            /* U+0046 - (F) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x00FC, 0x0102, 0x0102, 0x0122, 0x00E4, 0x0000 } },            /* U+0047 - (G) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x01FE, 0x0010, 0x0010, 0x0010, 0x01FE, 0x0000 } },            /* U+0048 - (H) */
            { 5, 0, ( uint32_t [] ){ 0x0000, 0x0102, 0x01FE, 0x0102, 0x0000 } },                            /* U+0049 - (I) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x00C0, 0x0102, 0x0102, 0x0102, 0x00FE, 0x0000 } },            /* U+004A - (J) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x01FE, 0x0030, 0x0048, 0x0084, 0x0102, 0x0000 } },            /* U+004B - (K) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x01FE, 0x0100, 0x0100, 0x0100, 0x0100, 0x0000 } },            /* U+004C - (L) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x01FE, 0x000C, 0x0010, 0x000C, 0x01FE, 0x0000 } },            /* U+004D - (M) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x01FE, 0x000C, 0x0030, 0x00C0, 0x01FE, 0x0000 } },            /* U+004E - (N) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x00FC, 0x0102, 0x0102, 0x0102, 0x00FC, 0x0000 } },            /* U+004F - (O) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x01FE, 0x0022, 0x0022, 0x0022, 0x001C, 0x0000 } },            /* U+0050 - (P) */
            { 8, 0, ( uint32_t [] ){ 0x0000, 0x00FC, 0x0102, 0x0102, 0x0302, 0x04FC, 0x0400, 0x0000 } },    /* U+0051 - (Q) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x01FE, 0x0022, 0x0062, 0x00A2, 0x011C, 0x0000 } },            /* U+0052 - (R) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x008C, 0x0112, 0x0112, 0x0112, 0x00E4, 0x0000 } },            /* U+0053 - (S) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0002, 0x0002, 0x01FE, 0x0002, 0x0002, 0x0000 } },            /* U+0054 - (T) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x00FE, 0x0100, 0x0100, 0x0100, 0x00FE, 0x0000 } },            /* U+0055 - (U) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x001E, 0x0060, 0x0180, 0x0060, 0x001E, 0x0000 } },            /* U+0056 - (V) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x003E, 0x01C0, 0x0038, 0x01C0, 0x003E, 0x0000 } },            /* U+0057 - (W) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0186, 0x0048, 0x0030, 0x0048, 0x0186, 0x0000 } },            /* U+0058 - (X) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0006, 0x0018, 0x01E0, 0x0018, 0x0006, 0x0000 } },            /* U+0059 - (Y) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0182, 0x0142, 0x0132, 0x010A, 0x0106, 0x0000 } },            /* U+005A - (Z) */
            { 5, 0, ( uint32_t [] ){ 0x0000, 0x0FFE, 0x0802, 0x0802, 0x0000 } },                            /* U+005B - ([) */
            { 6, 0, ( uint32_t [] ){ 0x0000, 0x0006, 0x0018, 0x0060, 0x0180, 0x0000 } },                    /* U+005C - (\) */
            { 5, 0, ( uint32_t [] ){ 0x0000, 0x0802, 0x0802, 0x0FFE, 0x0000 } },                            /* U+005D - (]) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0020, 0x0018, 0x0006, 0x0018, 0x0020, 0x0000 } },            /* U+005E - (^) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0200, 0x0200, 0x0200, 0x0200, 0x0200, 0x0000 } },            /* U+005F - (_) */
            { 4, 0, ( uint32_t [] ){ 0x0000, 0x0004, 0x0008, 0x0000 } },                                    /* U+0060 - (`) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x00F0, 0x0108, 0x0108, 0x0088, 0x01F8, 0x0000 } },            /* U+0061 - (a) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x01FE, 0x0110, 0x0108, 0x0108, 0x00F0, 0x0000 } },            /* U+0062 - (b) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x00F0, 0x0108, 0x0108, 0x0108, 0x0090, 0x0000 } },            /* U+0063 - (c) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x00F0, 0x0108, 0x0108, 0x0088, 0x01FE, 0x0000 } },            /* U+0064 - (d) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x00F0, 0x0128, 0x0128, 0x0128, 0x00B0, 0x0000 } },            /* U+0065 - (e) */
            { 6, 0, ( uint32_t [] ){ 0x0000, 0x0008, 0x01FC, 0x000A, 0x000A, 0x0000 } },                    /* U+0066 - (f) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x00F0, 0x0508, 0x0508, 0x0488, 0x03F8, 0x0000 } },            /* U+0067 - (g) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x01FE, 0x0010, 0x0008, 0x0008, 0x01F0, 0x0000 } },            /* U+0068 - (h) */
            { 5, 0, ( uint32_t [] ){ 0x0000, 0x0008, 0x01FA, 0x0100, 0x0000 } },                            /* U+0069 - (i) */
            { 6, 0, ( uint32_t [] ){ 0x0000, 0x0400, 0x0408, 0x0408, 0x03FA, 0x0000 } },                    /* U+006A - (j) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x01FE, 0x0020, 0x0050, 0x0088, 0x0100, 0x0000 } },            /* U+006B - (k) */
            { 4, 0, ( uint32_t [] ){ 0x0000, 0x01FE, 0x0100, 0x0000 } },                                    /* U+006C - (l) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x01F8, 0x0008, 0x01F0, 0x0008, 0x01F0, 0x0000 } },            /* U+006D - (m) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x01F8, 0x0010, 0x0008, 0x0008, 0x01F0, 0x0000 } },            /* U+006E - (n) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x00F0, 0x0108, 0x0108, 0x0108, 0x00F0, 0x0000 } },            /* U+006F - (o) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x07F8, 0x0110, 0x0108, 0x0108, 0x00F0, 0x0000 } },            /* U+0070 - (p) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x00F0, 0x0108, 0x0108, 0x0088, 0x07F8, 0x0000 } },            /* U+0071 - (q) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0108, 0x01F8, 0x0110, 0x0008, 0x0008, 0x0000 } },            /* U+0072 - (r) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0090, 0x0128, 0x0128, 0x0148, 0x0090, 0x0000 } },            /* U+0073 - (s) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0008, 0x00FE, 0x0108, 0x0108, 0x0080, 0x0000 } },            /* U+0074 - (t) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x00F8, 0x0100, 0x0100, 0x0080, 0x01F8, 0x0000 } },            /* U+0075 - (u) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0018, 0x0060, 0x0180, 0x0060, 0x0018, 0x0000 } },            /* U+0076 - (v) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0078, 0x0180, 0x0060, 0x0180, 0x0078, 0x0000 } },            /* U+0077 - (w) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0108, 0x0090, 0x0060, 0x0090, 0x0108, 0x0000 } },            /* U+0078 - (x) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0418, 0x0260, 0x0180, 0x0060, 0x0018, 0x0000 } },            /* U+0079 - (y) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0188, 0x0148, 0x0128, 0x0118, 0x0108, 0x0000 } },            /* U+007A - (z) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0040, 0x0040, 0x07BC, 0x0802, 0x0802, 0x0000 } },            /* U+007B - ({) */
            { 3, 0, ( uint32_t [] ){ 0x0000, 0x03FF, 0x0000 } },                                            /* U+007C - (|) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0802, 0x0802, 0x07BC, 0x0040, 0x0040, 0x0000 } },            /* U+007D - (}) */
            { 8, 0, ( uint32_t [] ){ 0x0000, 0x0020, 0x0010, 0x0010, 0x0020, 0x0020, 0x0010, 0x0000 } },    /* U+007E - (~) */
            
            { 0, 0, ( uint32_t [] ){ 0x00 } }                                                               /* U+007F */
        }
    },
    
    /***************************************************************************
     * System font - Monospace - 10
     **************************************************************************/
    {
        "System",
        10,
        12,
        XEOS_GUI_BitmapFontTraitsMonospace,
        127,
        ( struct __XEOS_GUI_BitmapFontGlyph [] ){
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+0000 */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+0001 */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+0002 */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+0003 */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+0004 */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+0005 */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+0006 */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+0007 */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+0008 */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+0009 */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+000A */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+000B */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+000C */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+000D */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+000E */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+000F */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+0010 */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+0011 */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+0012 */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+0013 */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+0014 */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+0015 */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+0016 */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+0017 */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+0018 */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+0019 */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+001A */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+001B */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+001C */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+001D */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+001E */
            { 0, 0, ( uint32_t [] ){ 0x0000 } },                                                            /* U+001F */
            
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 } },            /* U+0020 - ( ) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0000, 0x0000, 0x017E, 0x0000, 0x0000, 0x0000 } },            /* U+0021 - (!) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0016, 0x000E, 0x0000, 0x0016, 0x000E, 0x0000 } },            /* U+0022 - (") */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0048, 0x01C8, 0x007E, 0x01C8, 0x007E, 0x0048 } },            /* U+0023 - (#) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x008C, 0x0112, 0x03FF, 0x0122, 0x00C4, 0x0000 } },            /* U+0024 - ($) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x018C, 0x0052, 0x002C, 0x00D0, 0x0128, 0x00C6 } },            /* U+0025 - (%) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x00EC, 0x0112, 0x0122, 0x0144, 0x0080, 0x0140 } },            /* U+0026 - (&) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0000, 0x0000, 0x0016, 0x000E, 0x0000, 0x0000 } },            /* U+0027 - (') */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0000, 0x00F0, 0x030C, 0x0402, 0x0801, 0x0000 } },            /* U+0028 - (() */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0000, 0x0801, 0x0402, 0x030C, 0x00F0, 0x0000 } },            /* U+0029 - ()) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0024, 0x0018, 0x007E, 0x0018, 0x0024, 0x0000 } },            /* U+002A - (*) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0040, 0x0040, 0x01F0, 0x0040, 0x0040, 0x0000 } },            /* U+002B - (+) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0000, 0x0000, 0x0580, 0x0380, 0x0000, 0x0000 } },            /* U+002C - (,) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0040, 0x0040, 0x0040, 0x0040, 0x0040, 0x0000 } },            /* U+002D - (-) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0000, 0x0000, 0x0180, 0x0180, 0x0000, 0x0000 } },            /* U+002E - (.) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0300, 0x00C0, 0x0020, 0x0018, 0x0006, 0x0000 } },            /* U+002F - (/) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x00FC, 0x0122, 0x0112, 0x010A, 0x00FC, 0x0000 } },            /* U+0030 - (0) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0108, 0x0104, 0x01FE, 0x0100, 0x0100, 0x0000 } },            /* U+0031 - (1) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0184, 0x0142, 0x0122, 0x0112, 0x010C, 0x0000 } },            /* U+0032 - (2) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0084, 0x0102, 0x0112, 0x0112, 0x00EC, 0x0000 } },            /* U+0033 - (3) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0030, 0x0028, 0x0024, 0x01FE, 0x0020, 0x0000 } },            /* U+0034 - (4) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x013E, 0x0112, 0x0112, 0x0112, 0x00E2, 0x0000 } },            /* U+0035 - (5) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x00F8, 0x0114, 0x0112, 0x0112, 0x00E0, 0x0000 } },            /* U+0036 - (6) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0006, 0x0002, 0x01C2, 0x0032, 0x000E, 0x0000 } },            /* U+0037 - (7) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x00EC, 0x0112, 0x0112, 0x0112, 0x00EC, 0x0000 } },            /* U+0038 - (8) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x001C, 0x0122, 0x0122, 0x00A2, 0x007C, 0x0000 } },            /* U+0039 - (9) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0000, 0x0000, 0x0198, 0x0198, 0x0000, 0x0000 } },            /* U+003A - (:) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0000, 0x0000, 0x0598, 0x0398, 0x0000, 0x0000 } },            /* U+003B - (;) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0040, 0x0040, 0x00A0, 0x00A0, 0x0110, 0x0110 } },            /* U+003C - (<) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x00A0, 0x00A0, 0x00A0, 0x00A0, 0x00A0, 0x0000 } },            /* U+003D - (=) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0110, 0x0110, 0x00A0, 0x00A0, 0x0040, 0x0040 } },            /* U+003E - (>) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0004, 0x0002, 0x0162, 0x0012, 0x000C, 0x0000 } },            /* U+003F - (?) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0078, 0x0084, 0x0132, 0x014A, 0x017C, 0x0000 } },            /* U+0040 - (@) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x01C0, 0x0070, 0x004E, 0x0070, 0x01C0, 0x0000 } },            /* U+0041 - (A) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x01FE, 0x0112, 0x0112, 0x0112, 0x00EC, 0x0000 } },            /* U+0042 - (B) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x00FC, 0x0102, 0x0102, 0x0102, 0x0084, 0x0000 } },            /* U+0043 - (C) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x01FE, 0x0102, 0x0102, 0x0084, 0x0078, 0x0000 } },            /* U+0044 - (D) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x01FE, 0x0112, 0x0112, 0x0112, 0x0102, 0x0000 } },            /* U+0045 - (E) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x01FE, 0x0012, 0x0012, 0x0012, 0x0002, 0x0000 } },            /* U+0046 - (F) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x00FC, 0x0102, 0x0102, 0x0122, 0x00E4, 0x0000 } },            /* U+0047 - (G) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x01FE, 0x0010, 0x0010, 0x0010, 0x01FE, 0x0000 } },            /* U+0048 - (H) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0000, 0x0102, 0x01FE, 0x0102, 0x0000, 0x0000 } },            /* U+0049 - (I) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x00C0, 0x0102, 0x0102, 0x0102, 0x00FE, 0x0000 } },            /* U+004A - (J) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x01FE, 0x0030, 0x0048, 0x0084, 0x0102, 0x0000 } },            /* U+004B - (K) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x01FE, 0x0100, 0x0100, 0x0100, 0x0100, 0x0000 } },            /* U+004C - (L) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x01FE, 0x000C, 0x0010, 0x000C, 0x01FE, 0x0000 } },            /* U+004D - (M) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x01FE, 0x000C, 0x0030, 0x00C0, 0x01FE, 0x0000 } },            /* U+004E - (N) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x00FC, 0x0102, 0x0102, 0x0102, 0x00FC, 0x0000 } },            /* U+004F - (O) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x01FE, 0x0022, 0x0022, 0x0022, 0x001C, 0x0000 } },            /* U+0050 - (P) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x00FC, 0x0102, 0x0102, 0x0302, 0x04FC, 0x0400 } },            /* U+0051 - (Q) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x01FE, 0x0022, 0x0062, 0x00A2, 0x011C, 0x0000 } },            /* U+0052 - (R) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x008C, 0x0112, 0x0112, 0x0112, 0x00E4, 0x0000 } },            /* U+0053 - (S) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0002, 0x0002, 0x01FE, 0x0002, 0x0002, 0x0000 } },            /* U+0054 - (T) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x00FE, 0x0100, 0x0100, 0x0100, 0x00FE, 0x0000 } },            /* U+0055 - (U) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x001E, 0x0060, 0x0180, 0x0060, 0x001E, 0x0000 } },            /* U+0056 - (V) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x003E, 0x01C0, 0x0038, 0x01C0, 0x003E, 0x0000 } },            /* U+0057 - (W) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0186, 0x0048, 0x0030, 0x0048, 0x0186, 0x0000 } },            /* U+0058 - (X) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0006, 0x0018, 0x01E0, 0x0018, 0x0006, 0x0000 } },            /* U+0059 - (Y) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0182, 0x0142, 0x0132, 0x010A, 0x0106, 0x0000 } },            /* U+005A - (Z) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0000, 0x0FFE, 0x0802, 0x0802, 0x0000, 0x0000 } },            /* U+005B - ([) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0000, 0x0006, 0x0018, 0x0060, 0x0180, 0x0000 } },            /* U+005C - (\) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0000, 0x0802, 0x0802, 0x0FFE, 0x0000, 0x0000 } },            /* U+005D - (]) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0020, 0x0018, 0x0006, 0x0018, 0x0020, 0x0000 } },            /* U+005E - (^) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0200, 0x0200, 0x0200, 0x0200, 0x0200, 0x0000 } },            /* U+005F - (_) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0000, 0x0000, 0x0004, 0x0008, 0x0000, 0x0000 } },            /* U+0060 - (`) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x00F0, 0x0108, 0x0108, 0x0088, 0x01F8, 0x0000 } },            /* U+0061 - (a) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x01FE, 0x0110, 0x0108, 0x0108, 0x00F0, 0x0000 } },            /* U+0062 - (b) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x00F0, 0x0108, 0x0108, 0x0108, 0x0090, 0x0000 } },            /* U+0063 - (c) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x00F0, 0x0108, 0x0108, 0x0088, 0x01FE, 0x0000 } },            /* U+0064 - (d) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x00F0, 0x0128, 0x0128, 0x0128, 0x00B0, 0x0000 } },            /* U+0065 - (e) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0000, 0x0008, 0x01FC, 0x000A, 0x000A, 0x0000 } },            /* U+0066 - (f) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x00F0, 0x0508, 0x0508, 0x0488, 0x03F8, 0x0000 } },            /* U+0067 - (g) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x01FE, 0x0010, 0x0008, 0x0008, 0x01F0, 0x0000 } },            /* U+0068 - (h) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0000, 0x0008, 0x01FA, 0x0100, 0x0000, 0x0000 } },            /* U+0069 - (i) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0000, 0x0400, 0x0408, 0x0408, 0x03FA, 0x0000 } },            /* U+006A - (j) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x01FE, 0x0020, 0x0050, 0x0088, 0x0100, 0x0000 } },            /* U+006B - (k) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0000, 0x0000, 0x01FE, 0x0100, 0x0000, 0x0000 } },            /* U+006C - (l) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x01F8, 0x0008, 0x01F0, 0x0008, 0x01F0, 0x0000 } },            /* U+006D - (m) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x01F8, 0x0010, 0x0008, 0x0008, 0x01F0, 0x0000 } },            /* U+006E - (n) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x00F0, 0x0108, 0x0108, 0x0108, 0x00F0, 0x0000 } },            /* U+006F - (o) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x07F8, 0x0110, 0x0108, 0x0108, 0x00F0, 0x0000 } },            /* U+0070 - (p) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x00F0, 0x0108, 0x0108, 0x0088, 0x07F8, 0x0000 } },            /* U+0071 - (q) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0108, 0x01F8, 0x0110, 0x0008, 0x0008, 0x0000 } },            /* U+0072 - (r) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0090, 0x0128, 0x0128, 0x0148, 0x0090, 0x0000 } },            /* U+0073 - (s) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0008, 0x00FE, 0x0108, 0x0108, 0x0080, 0x0000 } },            /* U+0074 - (t) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x00F8, 0x0100, 0x0100, 0x0080, 0x01F8, 0x0000 } },            /* U+0075 - (u) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0018, 0x0060, 0x0180, 0x0060, 0x0018, 0x0000 } },            /* U+0076 - (v) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0078, 0x0180, 0x0060, 0x0180, 0x0078, 0x0000 } },            /* U+0077 - (w) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0108, 0x0090, 0x0060, 0x0090, 0x0108, 0x0000 } },            /* U+0078 - (x) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0418, 0x0260, 0x0180, 0x0060, 0x0018, 0x0000 } },            /* U+0079 - (y) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0188, 0x0148, 0x0128, 0x0118, 0x0108, 0x0000 } },            /* U+007A - (z) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0040, 0x0040, 0x07BC, 0x0802, 0x0802, 0x0000 } },            /* U+007B - ({) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0000, 0x0000, 0x03FF, 0x0000, 0x0000, 0x0000 } },            /* U+007C - (|) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0802, 0x0802, 0x07BC, 0x0040, 0x0040, 0x0000 } },            /* U+007D - (}) */
            { 7, 0, ( uint32_t [] ){ 0x0000, 0x0020, 0x0010, 0x0010, 0x0020, 0x0020, 0x0010 } },            /* U+007E - (~) */
            
            { 0, 0, ( uint32_t [] ){ 0x00 } }                                                               /* U+007F */
        }
    }
};

struct __XEOS_GUI_BitmapFont * __XEOS_GUI_BitmapFonts        = __XEOS_GUI_BitmapFontsArray;
size_t                         __XEOS_GUI_BitmapFontsCount   = sizeof( __XEOS_GUI_BitmapFontsArray );
