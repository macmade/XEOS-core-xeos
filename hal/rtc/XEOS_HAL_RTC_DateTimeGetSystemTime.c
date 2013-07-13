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
 * @file            XEOS_HAL_RTC_DateTimeGetSystemTime.c
 * @author          Jean-David Gadina
 * @copyright       (c) 2010-2012, Jean-David Gadina - www.xs-labs.com
 */

#include "xeos/hal/rtc.h"
#include "xeos/hal/__rtc.h"
#include <stdlib.h>
#include <string.h>

static struct __XEOS_HAL_RTC_DateTime __dateTime;

XEOS_HAL_RTC_DateTimeRef XEOS_HAL_RTC_DateTimeGetSystemTime( void )
{
    uint8_t seconds   [ 2 ];
    uint8_t minutes   [ 2 ];
    uint8_t hours     [ 2 ];
    uint8_t weekday   [ 2 ];
    uint8_t dayOfMonth[ 2 ];
    uint8_t month     [ 2 ];
    uint8_t year      [ 2 ];
    uint8_t century   [ 2 ];
    uint8_t statusB;
    
    memset( &__dateTime, 0, sizeof( struct __XEOS_HAL_RTC_DateTime ) );
    
    while( XEOS_HAL_RTC_UpdateInProgress() == true );
    
    seconds   [ 0 ] = __XEOS_HAL_RTC_ReadRegister( __XEOS_HAL_RTC_RegisterSeconds );
    minutes   [ 0 ] = __XEOS_HAL_RTC_ReadRegister( __XEOS_HAL_RTC_RegisterMinutes );
    hours     [ 0 ] = __XEOS_HAL_RTC_ReadRegister( __XEOS_HAL_RTC_RegisterHours );
    weekday   [ 0 ] = __XEOS_HAL_RTC_ReadRegister( __XEOS_HAL_RTC_RegisterWeekDay );
    dayOfMonth[ 0 ] = __XEOS_HAL_RTC_ReadRegister( __XEOS_HAL_RTC_RegisterDayOfMonth );
    month     [ 0 ] = __XEOS_HAL_RTC_ReadRegister( __XEOS_HAL_RTC_RegisterMonth );
    year      [ 0 ] = __XEOS_HAL_RTC_ReadRegister( __XEOS_HAL_RTC_RegisterYear );
    century   [ 0 ] = __XEOS_HAL_RTC_ReadRegister( __XEOS_HAL_RTC_RegisterCentury );
    
    do
    {
        seconds   [ 1 ] = __XEOS_HAL_RTC_ReadRegister( __XEOS_HAL_RTC_RegisterSeconds );
        minutes   [ 1 ] = __XEOS_HAL_RTC_ReadRegister( __XEOS_HAL_RTC_RegisterMinutes );
        hours     [ 1 ] = __XEOS_HAL_RTC_ReadRegister( __XEOS_HAL_RTC_RegisterHours );
        weekday   [ 1 ] = __XEOS_HAL_RTC_ReadRegister( __XEOS_HAL_RTC_RegisterWeekDay );
        dayOfMonth[ 1 ] = __XEOS_HAL_RTC_ReadRegister( __XEOS_HAL_RTC_RegisterDayOfMonth );
        month     [ 1 ] = __XEOS_HAL_RTC_ReadRegister( __XEOS_HAL_RTC_RegisterMonth );
        year      [ 1 ] = __XEOS_HAL_RTC_ReadRegister( __XEOS_HAL_RTC_RegisterYear );
        century   [ 1 ] = __XEOS_HAL_RTC_ReadRegister( __XEOS_HAL_RTC_RegisterCentury );
    }
    while
    (
            seconds   [ 0 ] != seconds   [ 1 ]
        &&  minutes   [ 0 ] != minutes   [ 1 ]
        &&  hours     [ 0 ] != hours     [ 1 ]
        &&  weekday   [ 0 ] != weekday   [ 1 ]
        &&  dayOfMonth[ 0 ] != dayOfMonth[ 1 ]
        &&  month     [ 0 ] != month     [ 1 ]
        &&  year      [ 0 ] != year      [ 1 ]
        &&  century   [ 0 ] != century   [ 1 ]
    );
    
    statusB = __XEOS_HAL_RTC_ReadRegister( __XEOS_HAL_RTC_RegisterStatusB );
    
    /* Convert BCD to binary values if necessary */
    if( ( statusB & 0x04 ) == 0 )
    {
        seconds   [ 0 ] = ( seconds   [ 0 ] & 0x0F ) + ( ( seconds   [ 0 ] / 16 ) * 10 );
        minutes   [ 0 ] = ( minutes   [ 0 ] & 0x0F ) + ( ( minutes   [ 0 ] / 16 ) * 10 );
        weekday   [ 0 ] = ( weekday   [ 0 ] & 0x0F ) + ( ( weekday   [ 0 ] / 16 ) * 10 );
        dayOfMonth[ 0 ] = ( dayOfMonth[ 0 ] & 0x0F ) + ( ( dayOfMonth[ 0 ] / 16 ) * 10 );
        month     [ 0 ] = ( month     [ 0 ] & 0x0F ) + ( ( month     [ 0 ] / 16 ) * 10 );
        year      [ 0 ] = ( year      [ 0 ] & 0x0F ) + ( ( year      [ 0 ] / 16 ) * 10 );
        century   [ 0 ] = ( century   [ 0 ] & 0x0F ) + ( ( century   [ 0 ] / 16 ) * 10 );
        hours     [ 0 ] = ( ( hours[ 0 ] & 0x0F ) + ( ( ( hours[ 0 ] & 0x70) / 16 ) * 10 ) ) | ( hours[ 0 ] & 0x80 );
    }
  
    /* Convert 12 hour clock to 24 hour clock if necessary */
    if( ( statusB & 0x02 ) == 0 && ( hours[ 0 ] & 0x80 ) != 0 )
    {
        hours[ 0 ] = ( ( hours[ 0 ] & 0x7F ) + 12 ) % 24;
    }
    
    __dateTime.seconds      = seconds   [ 0 ];
    __dateTime.minutes      = minutes   [ 0 ];
    __dateTime.weekday      = weekday   [ 0 ];
    __dateTime.dayOfMonth   = dayOfMonth[ 0 ];
    __dateTime.month        = month     [ 0 ];
    __dateTime.year         = year      [ 0 ];
    __dateTime.century      = century   [ 0 ];
    __dateTime.hours        = hours     [ 0 ];
    
    return &__dateTime;
}
