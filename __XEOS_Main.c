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
 * @file            XEOS_Main.c
 * @author          Jean-David Gadina
 * @copyright       (c) 2010-2012, Jean-David Gadina - www.xs-labs.com
 */

#include "xeos/video.h"
#include <stdlib.h>
#include <string.h>

void __XEOS_Main_PrintCopyright( void );
void __XEOS_Main_PromptWithStatus( const char * message, const char * status, XEOS_Video_Color statusColor );
void __XEOS_Main_PrintInfoLine( const char * format, ... ) XEOS_FORMAT_ATTRIBUTE( printf, 1, 2 );
int  __XEOS_Main_PrintExternalInfoLine( const char * s, ... ) XEOS_FORMAT_ATTRIBUTE( printf, 1, 2 );
void __XEOS_Main_Prompt( const char * message );
void __XEOS_Main_PromptSuccess( const char * successMessage );
void __XEOS_Main_PromptFailure( const char * failureMessage );

static bool         __externalInfoLine      = false;
static const char * __lastPromptMessage     = NULL;
static const char * __copyrightNL           = "\n";
static const char * __copyrightPipe         = "\xBA";
static const char * __copyrightHRTop        = "\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD"
                                              "\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD"
                                              "\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD"
                                              "\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD"
                                              "\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB";
static const char * __copyrightLine1Left    = "                \x04";
static const char * __copyrightLine1        = " XEOS - x86 Experimental Operating System ";
static const char * __copyrightLine1Right   = "\x04                 ";
static const char * __copyrightLine2        = "                                                                             ";
static const char * __copyrightLine3        = "      Copyright (c) 2010-2012 Jean-David Gadina - www.xs-labs.com            ";
static const char * __copyrightLine4        = "                       All rights (& wrongs) reserved                        ";
static const char * __copyrightHRBottom     = "\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD"
                                              "\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD"
                                              "\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD"
                                              "\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD"
                                              "\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC";

void __XEOS_Main_PrintCopyright( void )
{
    XEOS_Video_Print( __copyrightHRTop );
    XEOS_Video_Print( __copyrightNL );
    
    XEOS_Video_Print( __copyrightPipe );
    XEOS_Video_Print( __copyrightLine1Left );
    XEOS_Video_SetFG( XEOS_Video_ColorBrownLight );
    XEOS_Video_Print( __copyrightLine1 );
    XEOS_Video_SetFG( XEOS_Video_ColorWhite );
    XEOS_Video_Print( __copyrightLine1Right );
    XEOS_Video_Print( __copyrightPipe );
    XEOS_Video_Print( __copyrightNL );
    
    XEOS_Video_Print( __copyrightPipe );
    XEOS_Video_SetFG( XEOS_Video_ColorGrayLight );
    XEOS_Video_Print( __copyrightLine2 );
    XEOS_Video_SetFG( XEOS_Video_ColorWhite );
    XEOS_Video_Print( __copyrightPipe );
    XEOS_Video_Print( __copyrightNL );
    
    XEOS_Video_Print( __copyrightPipe );
    XEOS_Video_SetFG( XEOS_Video_ColorGrayLight );
    XEOS_Video_Print( __copyrightLine3 );
    XEOS_Video_SetFG( XEOS_Video_ColorWhite );
    XEOS_Video_Print( __copyrightPipe );
    XEOS_Video_Print( __copyrightNL );
    
    XEOS_Video_Print( __copyrightPipe );
    XEOS_Video_SetFG( XEOS_Video_ColorGrayLight );
    XEOS_Video_Print( __copyrightLine4 );
    XEOS_Video_SetFG( XEOS_Video_ColorWhite );
    XEOS_Video_Print( __copyrightPipe );
    XEOS_Video_Print( __copyrightNL );
    
    XEOS_Video_Print( __copyrightHRBottom );
    XEOS_Video_Print( __copyrightNL );
}


void __XEOS_Main_PromptWithStatus( const char * message, const char * status, XEOS_Video_Color statusColor )
{
    size_t       prompLength;
    size_t       messageLength;
    size_t       statusLength;
    size_t       i;
    unsigned int x;
    unsigned int cols;
    
    if( message != NULL && __lastPromptMessage != NULL )
    {
        XEOS_Video_Print( "\n" );
        
        __lastPromptMessage = NULL;
    }
    
    prompLength     = XEOS_Video_GetPromptLength();
    messageLength   = ( message == NULL ) ? strlen( __lastPromptMessage ) + 1 : strlen( message ) + 1;
    statusLength    = strlen( status )  + 4;
    
    if( message != NULL )
    {
        XEOS_Video_PrintPrompt();
        XEOS_Video_Print( message );
        XEOS_Video_Print( " " );
    }
    
    x    = XEOS_Video_X();
    cols = 80;
    
    if( x + statusLength > cols - 1 )
    {
        XEOS_Video_Print( "\n" );
        
        if( statusLength + prompLength < cols )
        {
            for( i = 0; i < ( ( cols - 1 ) - statusLength ); i++ )
            {
                XEOS_Video_Print( " " );
            }
        }
        else
        {
            for( i = 0; i < prompLength; i++ )
            {
                XEOS_Video_Print( " " );
            }
        }
    }
    else
    {
        for( i = 0; i < ( cols - 1 ) - ( x + statusLength ); i++ )
        {
            XEOS_Video_Print( " " );
        }
    }
    
    XEOS_Video_Print( "[ " );
    XEOS_Video_SetFG( statusColor );
    XEOS_Video_Print( status );
    XEOS_Video_SetFG( XEOS_Video_ColorWhite );
    XEOS_Video_Print( " ]\n" );
}

void __XEOS_Main_PrintInfoLine( const char * format, ... )
{
    size_t  i;
    va_list args;
    
    if( format == NULL )
    {
        return;
    }
    
    for( i = 0; i < XEOS_Video_GetPromptLength() + 2; i++ )
    {
        XEOS_Video_Print( " " );
    }
    
    va_start( args, format );
    XEOS_Video_Print( "\x1A " );
    XEOS_Video_SetFG( XEOS_Video_ColorGrayLight );
    XEOS_Video_VPrintf( format, args );
    XEOS_Video_SetFG( XEOS_Video_ColorWhite );
    XEOS_Video_Print( "\n" );
    va_end( args );
}

int __XEOS_Main_PrintExternalInfoLine( const char * s, ... )
{
    int     n;
    size_t  i;
    va_list args;
    
    n = 0;
    
    if( __externalInfoLine == false )
    {
        if( XEOS_Video_X() != 0 )
        {
            XEOS_Video_Print( "\n" );
            n++;
        }
        
        for( i = 0; i < XEOS_Video_GetPromptLength() + 2; i++ )
        {
            XEOS_Video_Print( " " );
            n++;
        }
    
        XEOS_Video_Print( "\x1A " );
        
        n += 2;
    }
    
    XEOS_Video_SetFG( XEOS_Video_ColorGrayLight );
    va_start( args, s );
    n += XEOS_Video_VPrintf( s, args );
    va_end( args );
    XEOS_Video_SetFG( XEOS_Video_ColorWhite );
    
    __externalInfoLine = ( strchr( s, '\n' ) == NULL ) ? true : false;
    
    return n;
}

void __XEOS_Main_Prompt( const char * message )
{
    if( message == NULL )
    {
        return;
    }
    
    if( message != NULL && __lastPromptMessage != NULL )
    {
        XEOS_Video_Print( "\n" );
        
        __lastPromptMessage = NULL;
    }
    
    XEOS_Video_PrintPrompt();
    XEOS_Video_Print( message );
    XEOS_Video_Print( " " );
    
    __lastPromptMessage = message;
}

void __XEOS_Main_PromptSuccess( const char * successMessage )
{
    successMessage = ( successMessage == NULL ) ? "OK" : successMessage;
    
    __XEOS_Main_PromptWithStatus( NULL, successMessage, XEOS_Video_ColorGreenLight );
    
    __lastPromptMessage = NULL;
}

void __XEOS_Main_PromptFailure( const char * failureMessage )
{
    failureMessage = ( failureMessage == NULL ) ? "FAIL" : failureMessage;
    
    __XEOS_Main_PromptWithStatus( NULL, failureMessage, XEOS_Video_ColorRedLight );
    
    __lastPromptMessage = NULL;
}
