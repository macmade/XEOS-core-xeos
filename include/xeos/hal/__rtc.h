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
 * @header          __rtc.h
 * @author          Jean-David Gadina
 * @copyright       (c) 2010-2012, Jean-David Gadina - www.xs-labs.com
 */

#ifndef __XEOS_HAL___RTC_H__
#define __XEOS_HAL___RTC_H__
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <xeos/macros.h>
#include <stdint.h>

/*!
 * @struct          __XEOS_HAL_RTC_DateTime
 * @abstract        Date/Time RTC values
 * @var             seconds         The number of seconds
 * @var             minutes         The number of minutes
 * @var             hours           The number of hours
 * @var             weekday         The weekday
 * @var             dayOfMonth      The day of the month
 * @var             month           The month number
 * @var             year            The year number
 * @var             century         The century number
 */
struct __XEOS_HAL_RTC_DateTime
{
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    uint8_t weekday;
    uint8_t dayOfMonth;
    uint8_t month;
    uint8_t year;
    uint8_t century;
};

/*!
 * @enum        __XEOS_HAL_RTC_Register
 * @abstract    RTC registers
 * @constant    __XEOS_HAL_RTC_RegisterSeconds      Seconds register
 * @constant    __XEOS_HAL_RTC_RegisterMinutes      Minutes register
 * @constant    __XEOS_HAL_RTC_RegisterHours        Hours register
 * @constant    __XEOS_HAL_RTC_RegisterWeekDay      Weekday register
 * @constant    __XEOS_HAL_RTC_RegisterDayOfMonth   Day of the month register
 * @constant    __XEOS_HAL_RTC_RegisterMonth        Month register
 * @constant    __XEOS_HAL_RTC_RegisterYear         Year register
 * @constant    __XEOS_HAL_RTC_RegisterCentury      Century register
 * @constant    __XEOS_HAL_RTC_RegisterStatusA      Status A register
 * @constant    __XEOS_HAL_RTC_RegisterStatusB      Status B register
 */
typedef enum
{
    __XEOS_HAL_RTC_RegisterSeconds      = 0x00,
    __XEOS_HAL_RTC_RegisterMinutes      = 0x02,
    __XEOS_HAL_RTC_RegisterHours        = 0x04,
    __XEOS_HAL_RTC_RegisterWeekDay      = 0x06,
    __XEOS_HAL_RTC_RegisterDayOfMonth   = 0x07,
    __XEOS_HAL_RTC_RegisterMonth        = 0x08,
    __XEOS_HAL_RTC_RegisterYear         = 0x09,
    __XEOS_HAL_RTC_RegisterCentury      = 0x32,
    __XEOS_HAL_RTC_RegisterStatusA      = 0x0A,
    __XEOS_HAL_RTC_RegisterStatusB      = 0x0B
}
__XEOS_HAL_RTC_Register;

/*!
 * @function        __XEOS_HAL_RTC_ReadRegister
 * @abstract        Reads the content of a RTC register
 * @param           r               The RTC register to read
 * @result          The content of the register
 */
uint8_t __XEOS_HAL_RTC_ReadRegister( __XEOS_HAL_RTC_Register r );

#ifdef __cplusplus
}
#endif

#endif /* __XEOS_HAL___RTC_H__ */
