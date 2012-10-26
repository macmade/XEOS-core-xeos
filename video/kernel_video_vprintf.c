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

#include <stdint.h>
#include <stdlib.h>
#include "private/video.h"

void kernel_video_vprintf( char * format, va_list arg )
{
    unsigned int x;
    unsigned int y;
    int          va_int;
    unsigned int va_uint;
    double       va_double;
    char         va_char;
    char       * va_char_ptr;
    uintptr_t    va_uint_ptr;
    char         nbuf[ 32 ] = { 0 };
    
    if( !format || *( format ) == '\0' )
    {
        return;
    }
    
    while( *( format ) != '\0' )
    {
        switch( *( format ) )
        {
            case '%':
                
                format++;
                
                if( *( format ) == '\0' )
                {
                    kernel_video_putc( '%', false );
                    break;
                }
                
                switch( *( format ) )
                {
                    case 'd':
                    case 'i':
                        
                        va_int = va_arg( arg, int );
                        
                        kernel_video_itoa( va_int, nbuf, 10 );
                        kernel_video_print( nbuf );
                        break;
                    
                    case 'f':
                        
                        va_double = va_arg( arg, double );
                        
                        kernel_video_itoa( ( int )va_double, nbuf, 10 );
                        kernel_video_print( nbuf );
                        break;
                        
                    case 'x':
                    case 'X':
                        
                        va_uint = va_arg( arg, unsigned int );
                        
                        kernel_video_utoa( va_uint, nbuf, 16 );
                        kernel_video_print( "0x" );
                        kernel_video_print( nbuf );
                        break;
                        
                    case 'o':
                        
                        va_uint = va_arg( arg, unsigned int );
                        
                        kernel_video_utoa( va_uint, nbuf, 8 );
                        kernel_video_print( "0" );
                        kernel_video_print( nbuf );
                        break;
                        
                    case 'u':
                        
                        va_uint = va_arg( arg, unsigned int );
                        
                        kernel_video_utoa( va_uint, nbuf, 10 );
                        kernel_video_print( nbuf );
                        break;
                        
                    case 'c':
                        
                        va_char = ( char )va_arg( arg, int );
                        
                        kernel_video_putc( va_char, false );
                        break;
                        
                    case 's':
                        
                        va_char_ptr = va_arg( arg, char * );
                        
                        if( va_char_ptr == NULL )
                        {
                            kernel_video_print( "(NULL)" );
                            
                        }
                        else
                        {
                            kernel_video_print( va_char_ptr );
                        }
                        
                        break;
                        
                    case 'p':
                        
                        va_uint_ptr = va_arg( arg, uintptr_t );
                        
                        kernel_video_utoa( va_uint_ptr, nbuf, 16 );
                        kernel_video_print( "0x" );
                        kernel_video_print( nbuf );
                        break;
                        
                    case '%':
                        
                        kernel_video_putc( '%', false );
                        break;
                    
                    default:
                        
                        kernel_video_putc( '%', false );
                        kernel_video_putc( *( format ), false );
                        break;
                }
                
                break;
            
            default:
                
                kernel_video_putc( *( format ), false );
                break;
        }
        
        format++;
    }
    
    x = kernel_video_cursor_x();
    y = kernel_video_cursor_y();
    
    kernel_video_cursor_move( x, y );
}
