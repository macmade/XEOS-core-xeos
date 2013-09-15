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

#ifndef __XEOS___PRIVATE_GUI_H__
#define __XEOS___PRIVATE_GUI_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <xeos/gui.h>

struct __XEOS_GUI_BitmapFontGlyph
{
    uint32_t   width;
    uint32_t   __reserved;
    uint32_t * data;
};

struct __XEOS_GUI_BitmapFont
{
    const char                        * name;
    uint32_t                            size;
    uint32_t                            glyphHeight;
    uint32_t                            traits;
    uint32_t                            glyphCount;
    struct __XEOS_GUI_BitmapFontGlyph * glyphs;
};

extern const char * __XEOS_GUI_SystemBitmapFontName;
extern uint32_t     __XEOS_GUI_SystemBitmapFontSize;

extern struct __XEOS_GUI_BitmapFont * __XEOS_GUI_BitmapFonts;
extern size_t                         __XEOS_GUI_BitmapFontsCount;

extern XEOS_GUI_Color __XEOS_GUI_Color_Black;
extern XEOS_GUI_Color __XEOS_GUI_Color_White;
extern XEOS_GUI_Color __XEOS_GUI_Color_Gray;
extern XEOS_GUI_Color __XEOS_GUI_Color_LightGray;
extern XEOS_GUI_Color __XEOS_GUI_Color_Red;
extern XEOS_GUI_Color __XEOS_GUI_Color_Green;
extern XEOS_GUI_Color __XEOS_GUI_Color_Blue;
extern XEOS_GUI_Color __XEOS_GUI_Color_Magenta;
extern XEOS_GUI_Color __XEOS_GUI_Color_Cyan;
extern XEOS_GUI_Color __XEOS_GUI_Color_Yellow;
extern XEOS_GUI_Color __XEOS_GUI_Color_ScreenBackground;
extern XEOS_GUI_Color __XEOS_GUI_Color_WindowBackground;

#ifdef __cplusplus
}
#endif

#endif /* __XEOS___PRIVATE_GUI_H__ */
