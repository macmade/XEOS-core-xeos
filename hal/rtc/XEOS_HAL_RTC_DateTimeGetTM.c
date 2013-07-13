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
 * @file            XEOS_HAL_RTC_DateTimeGetTM.c
 * @author          Jean-David Gadina
 * @copyright       (c) 2010-2012, Jean-David Gadina - www.xs-labs.com
 */

#include "xeos/hal/rtc.h"
#include "xeos/hal/__rtc.h"
#include "xeos/hal/io.h"
#include "xeos/hal/cmos.h"
#include <time.h>

void XEOS_HAL_RTC_DateTimeGetTM( XEOS_HAL_RTC_DateTimeRef time, struct tm * t )
{
    uint8_t     seconds;
    uint8_t     minutes;
    uint8_t     hours;
    uint8_t     weekday;
    uint8_t     dayOfMonth;
    uint8_t     month;
    uint8_t     year;
    uint8_t     century;
    uint16_t    fullYear;
    bool        leap;
    
    seconds     = XEOS_HAL_RTC_DateTimeGetSeconds( time );
    minutes     = XEOS_HAL_RTC_DateTimeGetMinutes( time );
    hours       = XEOS_HAL_RTC_DateTimeGetHours( time );
    weekday     = XEOS_HAL_RTC_DateTimeGetDayOfMonth( time );
    dayOfMonth  = XEOS_HAL_RTC_DateTimeGetDayOfMonth( time );
    month       = XEOS_HAL_RTC_DateTimeGetMonth( time );
    year        = XEOS_HAL_RTC_DateTimeGetYear( time );
    century     = XEOS_HAL_RTC_DateTimeGetCentury( time );
    
    if( century == 0 )
    {
        century = 19;
    }
    
    fullYear = ( century * 100 ) + year;
    
    t->tm_sec     = seconds;
    t->tm_min     = minutes;
    t->tm_hour    = hours;
    t->tm_wday    = weekday;
    t->tm_mday    = dayOfMonth;
    t->tm_mon     = ( month > 0 ) ? month - 1 : 0;
    t->tm_year    = ( fullYear > 1900 ) ? fullYear - 1900 : 0;
    t->tm_isdst   = 0;
    
    if( month == 1 )
    {
        t->tm_yday = dayOfMonth;
    }
    else if( month == 2 )
    {
        t->tm_yday = dayOfMonth + 31;
    }
    else
    {
        if( ( fullYear % 4 ) != 0 )
        {
            leap = false;
        }
        else if( ( fullYear % 100 ) != 0 )
        {
            leap = true;
        }
        else if( ( fullYear % 400 ) != 0 )
        {
            leap = false;
        }
        else
        {
            leap = true;
        }
        
        t->tm_yday = 31 + ( ( leap == true ) ? 29 : 28 );
        
        if( month == 3 )
        {
            t->tm_yday += dayOfMonth;
        }
        else if( month == 4 )
        {
            t->tm_yday += dayOfMonth + 31;
        }
        else if( month == 5 )
        {
            t->tm_yday += dayOfMonth + 31 + 30;
        }
        else if( month == 6 )
        {
            t->tm_yday += dayOfMonth + 31 + 30 + 31;
        }
        else if( month == 7 )
        {
            t->tm_yday += dayOfMonth + 31 + 30 + 31 + 30;
        }
        else if( month == 8 )
        {
            t->tm_yday += dayOfMonth + 31 + 30 + 31 + 30 + 31;
        }
        else if( month == 9 )
        {
            t->tm_yday += dayOfMonth + 31 + 30 + 31 + 30 + 31 + 31;
        }
        else if( month == 10 )
        {
            t->tm_yday += dayOfMonth + 31 + 30 + 31 + 30 + 31 + 31 + 30;
        }
        else if( month == 11 )
        {
            t->tm_yday += dayOfMonth + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31;
        }
        else if( month == 12 )
        {
            t->tm_yday += dayOfMonth + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30;
        }
    }
}

