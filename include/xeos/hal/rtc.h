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
 * @header          rtc.h
 * @author          Jean-David Gadina
 * @copyright       (c) 2010-2013, Jean-David Gadina - www.xs-labs.com
 */

#ifndef __XEOS_HAL_RTC_H__
#define __XEOS_HAL_RTC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <time.h>

/*!
 * @typedef         XEOS_HAL_RTC_DateTimeRef
 * @abstract        Opaque type for the RTC time object
 */
typedef struct __XEOS_HAL_RTC_DateTime * XEOS_HAL_RTC_DateTimeRef;

/*!
 * @function        XEOS_HAL_RTC_UpdateInProgress
 * @abstract        Checks if a RTC update is in progress
 * @result          True if a RTC update is in progress, otherwise false
 */
bool XEOS_HAL_RTC_UpdateInProgress( void );

/*!
 * @function        XEOS_HAL_RTC_DateTimeSetSystemTime
 * @abstract        Sets the RTC time (writes values back to CMOS)
 * @result          The RTC time object
 */
XEOS_HAL_RTC_DateTimeRef XEOS_HAL_RTC_DateTimeGetSystemTime( void );

/*!
 * @function        XEOS_HAL_RTC_DateTimeGetTM
 * @abstract        Converts RTC time to a tm struct (time.h)
 * @param           time            The RTC time object
 * @param           t               A pointer to a valid tm structure that will be filled
 */
void XEOS_HAL_RTC_DateTimeGetTM( XEOS_HAL_RTC_DateTimeRef time, struct tm * t );

/*!
 * @function        XEOS_HAL_RTC_DateTimeGetSeconds
 * @abstract        Gets the number of seconds
 * @param           time            The RTC time object
 * @result          The number of seconds
 */
uint8_t XEOS_HAL_RTC_DateTimeGetSeconds( XEOS_HAL_RTC_DateTimeRef time );

/*!
 * @function        XEOS_HAL_RTC_DateTimeGetMinutes
 * @abstract        Gets the number of minutes
 * @param           time            The RTC time object
 * @result          The number of minutes
 */
uint8_t XEOS_HAL_RTC_DateTimeGetMinutes( XEOS_HAL_RTC_DateTimeRef time );

/*!
 * @function        XEOS_HAL_RTC_DateTimeGetHours
 * @abstract        Gets the number of hours
 * @param           time            The RTC time object
 * @result          The number of hours
 */
uint8_t XEOS_HAL_RTC_DateTimeGetHours( XEOS_HAL_RTC_DateTimeRef time );

/*!
 * @function        XEOS_HAL_RTC_DateTimeGetWeekday
 * @abstract        Gets the weekday
 * @param           time            The RTC time object
 * @result          The weekday
 */
uint8_t XEOS_HAL_RTC_DateTimeGetWeekday( XEOS_HAL_RTC_DateTimeRef time );

/*!
 * @function        XEOS_HAL_RTC_DateTimeGetDayOfMonth
 * @abstract        Gets the day of month
 * @param           time            The RTC time object
 * @result          The day of month
 */
uint8_t XEOS_HAL_RTC_DateTimeGetDayOfMonth( XEOS_HAL_RTC_DateTimeRef time );

/*!
 * @function        XEOS_HAL_RTC_DateTimeGetMonth
 * @abstract        Gets the month number
 * @param           time            The RTC time object
 * @result          The month number
 */
uint8_t XEOS_HAL_RTC_DateTimeGetMonth( XEOS_HAL_RTC_DateTimeRef time );

/*!
 * @function        XEOS_HAL_RTC_DateTimeGetYear
 * @abstract        Gets the year number
 * @param           time            The RTC time object
 * @result          The year number
 */
uint8_t XEOS_HAL_RTC_DateTimeGetYear( XEOS_HAL_RTC_DateTimeRef time );

/*!
 * @function        XEOS_HAL_RTC_DateTimeGetCentury
 * @abstract        Gets the century number
 * @param           time            The RTC time object
 * @result          The century number
 */
uint8_t XEOS_HAL_RTC_DateTimeGetCentury( XEOS_HAL_RTC_DateTimeRef time );

/*!
 * @function        XEOS_HAL_RTC_DateTimeSetSeconds
 * @abstract        Sets the number of seconds
 * @param           time            The RTC time object
 * @param           value           The number of seconds
 */
void XEOS_HAL_RTC_DateTimeSetSeconds( XEOS_HAL_RTC_DateTimeRef time, uint8_t value );

/*!
 * @function        XEOS_HAL_RTC_DateTimeSetMinutes
 * @abstract        Sets the number of minutes
 * @param           time            The RTC time object
 * @param           value           The number of minutes
 */
void XEOS_HAL_RTC_DateTimeSetMinutes( XEOS_HAL_RTC_DateTimeRef time, uint8_t value );

/*!
 * @function        XEOS_HAL_RTC_DateTimeSetHours
 * @abstract        Sets the number of hours
 * @param           time            The RTC time object
 * @param           value           The number of hours
 */
void XEOS_HAL_RTC_DateTimeSetHours( XEOS_HAL_RTC_DateTimeRef time, uint8_t value );

/*!
 * @function        XEOS_HAL_RTC_DateTimeSetWeekday
 * @abstract        Sets the weekday
 * @param           time            The RTC time object
 * @param           value           The weekday
 */
void XEOS_HAL_RTC_DateTimeSetWeekday( XEOS_HAL_RTC_DateTimeRef time, uint8_t value );

/*!
 * @function        XEOS_HAL_RTC_DateTimeSetDayOfMonth
 * @abstract        Sets the day of month
 * @param           time            The RTC time object
 * @param           value           The day of month
 */
void XEOS_HAL_RTC_DateTimeSetDayOfMonth( XEOS_HAL_RTC_DateTimeRef time, uint8_t value );

/*!
 * @function        XEOS_HAL_RTC_DateTimeSetMonth
 * @abstract        Sets the month number
 * @param           time            The RTC time object
 * @param           value           The month number
 */
void XEOS_HAL_RTC_DateTimeSetMonth( XEOS_HAL_RTC_DateTimeRef time, uint8_t value );

/*!
 * @function        XEOS_HAL_RTC_DateTimeSetYear
 * @abstract        Sets the year number
 * @param           time            The RTC time object
 * @param           value           The year number
 */
void XEOS_HAL_RTC_DateTimeSetYear( XEOS_HAL_RTC_DateTimeRef time, uint8_t value );

/*!
 * @function        XEOS_HAL_RTC_DateTimeSetCentury
 * @abstract        Sets the century number
 * @param           time            The RTC time object
 * @param           value           The century number
 */
void XEOS_HAL_RTC_DateTimeSetCentury( XEOS_HAL_RTC_DateTimeRef time, uint8_t value );

/*!
 * @function        XEOS_HAL_RTC_EnablePeriodicInterrupts
 * @abstract        Enables RTC periodic interrupts (IRQ8)
 */
void XEOS_HAL_RTC_EnablePeriodicInterrupts( void );

/*!
 * @function        XEOS_HAL_RTC_DisablePeriodicInterrupts
 * @abstract        Disables RTC periodic interrupts (IRQ8)
 */
void XEOS_HAL_RTC_DisablePeriodicInterrupts( void );

/*!
 * @function        XEOS_HAL_RTC_GetRate
 * @abstract        Gets the RTC rate
 * @result          The RTC rate divider
 */
uint8_t XEOS_HAL_RTC_GetRate( void );

/*!
 * @function        XEOS_HAL_RTC_SetRate
 * @abstract        Sets the RTC rate
 * @param           rate            The RTC rate divider
 */
void XEOS_HAL_RTC_SetRate( uint8_t rate );

#ifdef __cplusplus
}
#endif

#endif /* __XEOS_HAL_RTC_H__ */
