/*******************************************************************************
 * XEOS - X86 Experimental Operating System
 * 
 * Copyright (c) 2010-2012, Jean-David Gadina - www.xs-labs.com
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
 * @file            __XEOS_Video_ProcessFormatString.c
 * @author          Jean-David Gadina
 * @copyright       (c) 2010-2012, Jean-David Gadina - www.xs-labs.com
 */

#include "xeos/video.h"
#include "xeos/__video.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum
{
    __XEOS_Video_VPrintf_Flag_SignNormal                = 0x00,
    __XEOS_Video_VPrintf_Flag_SignNone                  = 0x01,
    __XEOS_Video_VPrintf_Flag_SignAlways                = 0x02
}
__XEOS_Video_VPrintf_Flag_Sign;

typedef enum
{
    __XEOS_Video_VPrintf_Flag_IntegerLengthNormal       = 0x00,
    __XEOS_Video_VPrintf_Flag_IntegerLength16           = 0x01,
    __XEOS_Video_VPrintf_Flag_IntegerLength32           = 0x02,
    __XEOS_Video_VPrintf_Flag_IntegerLength64           = 0x03
}
__XEOS_Video_VPrintf_Flag_IntegerLength;

typedef enum
{
    __XEOS_Video_VPrintf_Flag_IntegerTypeNormal         = 0x00,
    __XEOS_Video_VPrintf_Flag_IntegerTypeOctal          = 0x01,
    __XEOS_Video_VPrintf_Flag_IntegerTypeHexadecimal    = 0x02,
    __XEOS_Video_VPrintf_Flag_IntegerTypePointer        = 0x04,
    __XEOS_Video_VPrintf_Flag_IntegerTypeUnsigned       = 0x08,
    __XEOS_Video_VPrintf_Flag_IntegerTypeUppercase      = 0x10
}
__XEOS_Video_VPrintf_Flag_IntegerType;

int __XEOS_Video_ProcessFormatString( const char * format, va_list ap, void ( * characterHandler )( char ) )
{
    int count;
    
    ( void )characterHandler;
    
    count = 0;
    
    while( *( format ) != 0 )
    {
        if( *( format ) != '%' )
        {
            if( characterHandler != NULL )
            {
                characterHandler( *( format ) );
            }
            
            count++;
            format++;
            continue;
        }
        
        format++;
        
        if( *( format ) == '%' )
        {
            if( characterHandler != NULL )
            {
                characterHandler( *( format ) );
            }
            
            count++;
            format++;
            continue;
        }
        
        {
            bool                                    end;
            size_t                                  len;
            int                                     minimumWidth;
            int                                     precision;
            char                                    pad;
            bool                                    sharp;
            bool                                    align;
            __XEOS_Video_VPrintf_Flag_Sign          sign;
            __XEOS_Video_VPrintf_Flag_IntegerLength intLength;
            unsigned int                            intType;
            
            end             = false;
            minimumWidth    = 0;
            precision       = 1;
            pad             = ' ';
            sharp           = false;
            align           = false;
            sign            = __XEOS_Video_VPrintf_Flag_SignNormal;
            intLength       = __XEOS_Video_VPrintf_Flag_IntegerLengthNormal;
            intType         = __XEOS_Video_VPrintf_Flag_IntegerTypeNormal;
            
            do
            {
                switch( *( format ) )
                {
                    case 'n':
                        
                        {
                            int * p;
                            
                            p       = va_arg( ap, int * );
                            *( p )  = count;
                        }
                        
                        format++;
                        
                        break;
                        
                    case '-':
                        
                        align = true;
                        
                        format++;
                        
                        break;
                        
                    case '+':
                        
                        sign = __XEOS_Video_VPrintf_Flag_SignAlways;
                        
                        format++;
                        
                        break;
                        
                    case ' ':
                        
                        sign = __XEOS_Video_VPrintf_Flag_SignNone;
                        
                        format++;
                        
                        break;
                        
                    case '0':
                        
                        pad = '0';
                        
                        format++;
                        
                        break;
                        
                    case '#':
                        
                        sharp = true;
                        
                        format++;
                        
                        break;
                        
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                        
                        minimumWidth = atoi( format );
                        
                        while( isdigit( *( format ) ) )
                        {
                            format++;
                        }
                        
                        break;
                        
                    case '*':
                        
                        minimumWidth = va_arg( ap, int );
                        
                        format++;
                        
                        break;
                        
                    case '.':
                        
                        format++;
                        
                        if( *( format ) == '*' )
                        {
                            precision = va_arg( ap, int );
                            
                            format++;
                        }
                        else if( isdigit( *( format ) ) )
                        {
                            precision = atoi( format );
                            
                            while( isdigit( *( format ) ) )
                            {
                                format++;
                            }
                        }
                        else
                        {
                            precision = 0;
                        }
                        
                        break;
                        
                    case 'h':
                        
                        intLength = __XEOS_Video_VPrintf_Flag_IntegerLength16;
                        
                        format++;
                        
                        break;
                        
                    case 'l':
                        
                        if( intLength == __XEOS_Video_VPrintf_Flag_IntegerLength32 || intLength == __XEOS_Video_VPrintf_Flag_IntegerLength64 )
                        {
                            intLength = __XEOS_Video_VPrintf_Flag_IntegerLength64;
                        }
                        else
                        {
                            #ifdef __LP64__
                            intLength = __XEOS_Video_VPrintf_Flag_IntegerLength64;
                            #else
                            intLength = __XEOS_Video_VPrintf_Flag_IntegerLength32;
                            #endif
                        }
                        
                        format++;
                        
                        break;
                        
                    case 'L':
                        
                        break;
                        
                    case 'c':
                        
                        {
                            char c;
                            
                            c = ( char )va_arg( ap, int );
                            
                            if( align == false )
                            {
                                for( ; minimumWidth > 1; minimumWidth-- )
                                {
                                    if( characterHandler != NULL )
                                    {
                                        characterHandler( pad );
                                    }
                                    
                                    count++;
                                }
                            }
                            
                            if( characterHandler != NULL )
                            {
                                characterHandler( c );
                            }
                            
                            count++;
                            
                            if( align == true )
                            {
                                for( ; minimumWidth > 1; minimumWidth-- )
                                {
                                    if( characterHandler != NULL )
                                    {
                                        characterHandler( pad );
                                    }
                                    
                                    count++;
                                }
                            }
                        }
                        
                        format++;
                        
                        end = true;
                        
                        break;
                    
                    case 's':
                        
                        {
                            char * s;
                            
                            s   = va_arg( ap, char * );
                            len = strlen( s );
                            
                            if( s == NULL )
                            {
                                s = "(null)";
                            }
                            
                            if( align == false  && len < ( size_t )minimumWidth )
                            {
                                while( len++ < ( size_t )minimumWidth )
                                {
                                    if( characterHandler != NULL )
                                    {
                                        characterHandler( pad );
                                    }
                                    
                                    count++;
                                }
                            }
                            
                            while( *( s ) != 0 )
                            {
                                if( characterHandler != NULL )
                                {
                                    characterHandler( *( s++ ) );
                                }
                                
                                count++;
                            }
                            
                            if( align == true && len < ( size_t )minimumWidth )
                            {
                                while( len++ < ( size_t )minimumWidth )
                                {
                                    if( characterHandler != NULL )
                                    {
                                        characterHandler( pad );
                                    }
                                    
                                    count++;
                                }
                            }
                        }
                        
                        format++;
                        
                        end = true;
                        
                        break;
                    
                    #ifdef __clang__
                        #pragma clang diagnostic push
                        #pragma clang diagnostic ignored "-Wimplicit-fallthrough"
                    #endif
                    
                    case 'o':   intType |= __XEOS_Video_VPrintf_Flag_IntegerTypeOctal;
                    case 'p':   intType |= __XEOS_Video_VPrintf_Flag_IntegerTypePointer;
                    case 'X':   intType |= __XEOS_Video_VPrintf_Flag_IntegerTypeUppercase;
                    case 'x':   intType |= __XEOS_Video_VPrintf_Flag_IntegerTypeHexadecimal;    
                    case 'u':   intType |= __XEOS_Video_VPrintf_Flag_IntegerTypeUnsigned;
                    case 'd':
                    case 'i':
                    
                    #ifdef __clang__
                        #pragma clang diagnostic pop
                    #endif
                        
                        {
                            uint64_t        n;
                            bool            positive;
                            unsigned int    radix;
                            unsigned int    digits;
                            unsigned int    mod;
                            
                            n           = 0;
                            positive    = false;
                            radix       = 10;
                            digits      = 0;
                            mod         = 0;
                            
                            if( ( intType & __XEOS_Video_VPrintf_Flag_IntegerTypeOctal ) != 0 )
                            {
                                intType = __XEOS_Video_VPrintf_Flag_IntegerTypeOctal;
                            }
                            else if( ( intType & __XEOS_Video_VPrintf_Flag_IntegerTypePointer ) != 0 )
                            {
                                intType = __XEOS_Video_VPrintf_Flag_IntegerTypePointer;
                            }
                            else if( ( intType & __XEOS_Video_VPrintf_Flag_IntegerTypeHexadecimal ) != 0 )
                            {
                                if( ( intType & __XEOS_Video_VPrintf_Flag_IntegerTypeUppercase ) != 0 )
                                {
                                    intType = __XEOS_Video_VPrintf_Flag_IntegerTypeHexadecimal | __XEOS_Video_VPrintf_Flag_IntegerTypeUppercase;
                                }
                                else
                                {
                                    intType = __XEOS_Video_VPrintf_Flag_IntegerTypeHexadecimal;
                                }
                            }
                            
                            if( intLength == __XEOS_Video_VPrintf_Flag_IntegerLength64 )
                            {
                                n = ( uint64_t )va_arg( ap, long long );
                            }
                            else if( intLength == __XEOS_Video_VPrintf_Flag_IntegerLength16 )
                            {
                                n  = ( uint64_t )( ( short )va_arg( ap, int ) );
                                n &= 0xFFFF;
                            }
                            else if( ( intType & __XEOS_Video_VPrintf_Flag_IntegerTypePointer ) != 0 )
                            {
                                n = ( uint64_t )va_arg( ap, void * );
                                
                                #ifndef __LP64__
                                n &= 0xFFFFFFFF;
                                #endif
                                
                                intType = __XEOS_Video_VPrintf_Flag_IntegerTypeHexadecimal | __XEOS_Video_VPrintf_Flag_IntegerTypeUppercase;
                                sharp   = true;
                            }
                            else
                            {
                                n  = ( uint64_t )va_arg( ap, int );
                                n &= 0xFFFFFFFF;
                            }
                            
                            if( ( sign & __XEOS_Video_VPrintf_Flag_SignNone ) == 0 )
                            {
                                if( ( intType & __XEOS_Video_VPrintf_Flag_IntegerTypeNormal ) != 0 )
                                {
                                    positive = ( int64_t )n >= 0;
                                }
                                else
                                {
                                    positive = true;
                                }
                                
                                if( positive == false )
                                {
                                    if( characterHandler != NULL )
                                    {
                                        characterHandler( '-' );
                                    }
                                    
                                    count++;
                                    
                                    n = ( uint64_t )( -( int64_t )n );
                                }
                                else if( ( sign & __XEOS_Video_VPrintf_Flag_SignAlways ) != 0 )
                                {
                                    if( characterHandler != NULL )
                                    {
                                        characterHandler( '+' );
                                    }
                                    
                                    count++;
                                }
                            }
                            
                            if( ( intType & __XEOS_Video_VPrintf_Flag_IntegerTypeOctal ) != 0 )
                            {
                                radix = 8;
                                
                                if( sharp == true && n != 0 )
                                {
                                    if( characterHandler != NULL )
                                    {
                                        characterHandler( '0' );
                                    }
                                    
                                    count++;
                                }
                            }
                            else if( ( intType & __XEOS_Video_VPrintf_Flag_IntegerTypeHexadecimal ) != 0 )
                            {
                                radix = 16;
                                
                                if( sharp == true )
                                {
                                    if( characterHandler != NULL )
                                    {
                                        characterHandler( '0' );
                                        characterHandler( 'x' );
                                    }
                                    
                                    count++;
                                    count++;
                                }
                            }
                            else
                            {
                                radix = 10;
                            }
                            
                            {
                                char * s1;
                                char * s2;
                                char   buf[ 30 ];
                                
                                memset( buf, 0, 30 );
                                
                                s1 = buf;
                                s2 = buf;
                                
                                do
                                {
                                    if( digits > 0 )
                                    {
                                        memmove( s1 + 1, s1, digits * sizeof( char ) );
                                    }
                                    
                                    mod = n % radix;
                                    
                                    if( mod < 10 )
                                    {
                                        *( s1 ) = '0' + ( char )mod;
                                        
                                        s2++;
                                    }
                                    else if( ( intType & __XEOS_Video_VPrintf_Flag_IntegerTypeUppercase ) != 0 )
                                    {
                                        *( s1 ) = 'A' + ( char )( mod - 10 );
                                        
                                        s2++;
                                    }
                                    else
                                    {
                                        *( s1 ) = 'a' + ( char )( mod - 10 );
                                        
                                        s2++;
                                    }
                                    
                                    n = n / radix;
                                    
                                    digits++;
                                }
                                while( n > 0 );
                                
                                if( ( int )digits < minimumWidth )
                                {
                                    minimumWidth -= digits;
                                    
                                    if( align )
                                    {
                                        for( ; minimumWidth > 0; minimumWidth--)
                                        {
                                            *( s2 )++ = ( char )pad;
                                        }
                                    }
                                    else
                                    {
                                        memmove( s1 + ( ( unsigned int )minimumWidth * sizeof( char ) ), s1, digits * sizeof( char ) );
                                        memset( s1, pad, ( unsigned int )minimumWidth * sizeof( char ) );
                                        
                                        s2 += minimumWidth;
                                    }
                                }
                                
                                s1 = buf;
                                
                                while( *( s1 ) != 0 )
                                {
                                    if( characterHandler != NULL )
                                    {
                                        characterHandler( *( s1 ) );
                                    }
                                    
                                    count++;
                                    s1++;
                                }
                            }
                        }
                        
                        format++;
                        
                        end = true;
                        
                        break;
                        
                    case 'f':
                    case 'F':
                    case 'a':
                    case 'A':
                    case 'g':
                    case 'G':
                    case 'e':
                    case 'E':
                        
                        va_arg( ap, double );
                        
                        format++;
                        
                        end = true;
                        
                        break;
                        
                    default:
                        
                        format++;
                        
                        end = true;
                        
                        break;
                }
            }
            while( end == false );
        }
    }
    
    return count;
}
