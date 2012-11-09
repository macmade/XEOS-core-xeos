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
 * @file            XEOS_Video_VPrintf.c
 * @author          Jean-David Gadina
 * @copyright       (c) 2010-2012, Jean-David Gadina <macmade@eosgarden.com>
 */

#include "xeos/video.h"
#include "xeos/__video.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void XEOS_Video_VPrintf( char * format, va_list arg )
{
    unsigned int x;
    unsigned int y;
    int          va_int;
    unsigned int va_uint;
    double       va_double;
    char         va_char;
    char       * va_char_ptr;
    uintptr_t    va_uint_ptr;
    char         nbuf[ 32 ];
    
    memset( nbuf, 0, 32 );
    
    if( format == NULL || *( format ) == 0 )
    {
        return;
    }
    
    ( void )arg;
    
    while( *( format ) != 0 )
    {
        switch( *( format ) )
        {
            case '%':
                
                format++;
                
                if( *( format ) == 0 )
                {
                    XEOS_Video_Putc( '%', false );
                    break;
                }
                
                switch( *( format ) )
                {
                    case 'd':
                    case 'i':
                        
                        va_int = va_arg( arg, int );
                        
                        XEOS_Video_Itoa( va_int, nbuf, 10 );
                        XEOS_Video_Print( nbuf );
                        break;
                    
                    case 'f':
                        
                        va_double = va_arg( arg, double );
                        
                        XEOS_Video_Itoa( ( int )va_double, nbuf, 10 );
                        XEOS_Video_Print( nbuf );
                        break;
                        
                    case 'x':
                    case 'X':
                        
                        va_uint = va_arg( arg, unsigned int );
                        
                        XEOS_Video_Utoa( va_uint, nbuf, 16 );
                        XEOS_Video_Print( "0x" );
                        XEOS_Video_Print( nbuf );
                        break;
                        
                    case 'o':
                        
                        va_uint = va_arg( arg, unsigned int );
                        
                        XEOS_Video_Utoa( va_uint, nbuf, 8 );
                        XEOS_Video_Print( "0" );
                        XEOS_Video_Print( nbuf );
                        break;
                        
                    case 'u':
                        
                        va_uint = va_arg( arg, unsigned int );
                        
                        XEOS_Video_Utoa( va_uint, nbuf, 10 );
                        XEOS_Video_Print( nbuf );
                        break;
                        
                    case 'c':
                        
                        va_char = ( char )va_arg( arg, int );
                        
                        XEOS_Video_Putc( ( unsigned char )va_char, false );
                        break;
                        
                    case 's':
                        
                        va_char_ptr = va_arg( arg, char * );
                        
                        if( va_char_ptr == NULL )
                        {
                            XEOS_Video_Print( "(NULL)" );
                            
                        }
                        else
                        {
                            XEOS_Video_Print( va_char_ptr );
                        }
                        
                        break;
                        
                    case 'p':
                        
                        va_uint_ptr = va_arg( arg, uintptr_t );
                        
                        XEOS_Video_Utoa( ( unsigned int )va_uint_ptr, nbuf, 16 );
                        XEOS_Video_Print( "0x" );
                        XEOS_Video_Print( nbuf );
                        break;
                        
                    case '%':
                        
                        XEOS_Video_Putc( '%', false );
                        break;
                    
                    default:
                        
                        XEOS_Video_Putc( '%', false );
                        XEOS_Video_Putc( ( unsigned char )( *( format ) ), false );
                        break;
                }
                
                break;
            
            default:
                
                XEOS_Video_Putc( ( unsigned char )( *( format ) ), false );
                break;
        }
        
        format++;
    }
    
    x = XEOS_Video_X();
    y = XEOS_Video_Y();
    
    XEOS_Video_MoveCursor( x, y );
}
