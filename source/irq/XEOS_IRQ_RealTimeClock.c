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
 * @file            XEOS_IRQ_RealTimeClock.c
 * @author          Jean-David Gadina
 * @copyright       (c) 2010-2013, Jean-David Gadina - www.xs-labs.com
 */

#include <xeos/irq.h>
#include <xeos/__private/irq.h>
#include <xeos/hal/io.h>
#include <xeos/hal/cmos.h>
#include <xeos/hal/rtc.h>
#include <xeos/__private/system.h>
#include <time.h>

#define XEOS_IRQ_RTC_FREQUENCY    1024

static int  __count  = 0;
static bool __inited = false;

void XEOS_IRQ_RealTimeClock( XEOS_HAL_PIC_IRQ irq, XEOS_HAL_CPU_Registers * registers )
{
    ( void )irq;
    ( void )registers;
    
    if( __inited == false )
    {
        {
            XEOS_HAL_RTC_DateTimeRef dateTime;
            struct tm                time;
            
            __count     = 0;
            __inited    = true;
            
            dateTime    = XEOS_HAL_RTC_DateTimeGetSystemTime();
            
            XEOS_HAL_RTC_DateTimeGetTM( dateTime, &time );
            
            __XEOS_System_Milliseconds = 0;
            __XEOS_System_Timestamp    = mktime( &time );
        }
    }
    else
    {
        if( __count == XEOS_IRQ_RTC_FREQUENCY )
        {
            __count                     = 0;
            __XEOS_System_Milliseconds  = 0;
            
            __XEOS_System_Timestamp++;
        }
        else
        {
            __count++;
            
            __XEOS_System_Milliseconds = ( ( double )__count / ( double )XEOS_IRQ_RTC_FREQUENCY ) * ( double )1000;
        }
    }
    
    /*
     * When IRQ 8 is triggered, the Status Register C will contain a bitmask
     * telling which kind of RTC interrupt just happened.
     * It can be a periodic interrupt, an update ended interrupt, or an alarm
     * interrupt.
     * The Status Register C must be read after IRQ 8. Otherwise, the
     * interrupt won't happen again.
     */
    XEOS_HAL_IO_PortOut( XEOS_HAL_CMOS_RegisterAddress, 0x0C );
    XEOS_HAL_IO_PortIn( XEOS_HAL_CMOS_RegisterData );
}
