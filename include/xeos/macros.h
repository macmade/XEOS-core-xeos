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
 * @header          macros.h
 * @author          Jean-David Gadina
 * @copyright       (c) 2010-2013, Jean-David Gadina - www.xs-labs.com
 */

#ifndef __XEOS_MACROS_H__
#define __XEOS_MACROS_H__
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @def         XEOS_WEAK_ATTRIBUTE
 * @brief       Standardization of the weak compiler attribute
 * @details     Not all compiler support this attribute, so it may be defined
 *              to nothing.
 */
#if defined( __GNUC__ ) && ( ( __GNUC__ >= 4 ) || ( ( __GNUC__ == 3 ) && ( __GNUC_MINOR__ >= 1 ) ) )
    #define XEOS_WEAK_ATTRIBUTE __attribute__( ( weak ) )
#else
    #define XEOS_WEAK_ATTRIBUTE
#endif

/*!
 * @def         XEOS_WEAK_IMPORT_ATTRIBUTE
 * @brief       Standardization of the weak import compiler attribute
 * @details     Not all compiler support this attribute, so it may be defined
 *              to nothing.
 */
#if defined( __GNUC__ ) && ( ( __GNUC__ >= 4 ) || ( ( __GNUC__ == 3 ) && ( __GNUC_MINOR__ >= 1 ) ) )
    #define XEOS_WEAK_IMPORT_ATTRIBUTE __attribute__( ( weak_import ) )
#elif defined(__MWERKS__) && ( __MWERKS__ >= 0x3205 )
    #define XEOS_WEAK_IMPORT_ATTRIBUTE __attribute__( ( weak_import ) )
#else
    #define XEOS_WEAK_IMPORT_ATTRIBUTE
#endif

/*!
 * @def         XEOS_DEPRECATED_ATTRIBUTE
 * @brief       Standardization of the deprecated compiler attribute
 * @details     Not all compiler support this attribute, so it may be defined
 *              to nothing.
 */
#if defined( __GNUC__ ) && ( ( __GNUC__ >= 4 ) || ( ( __GNUC__ == 3 ) && ( __GNUC_MINOR__ >= 1 ) ) )
    #define XEOS_DEPRECATED_ATTRIBUTE __attribute__( ( deprecated ) )
#else
    #define XEOS_DEPRECATED_ATTRIBUTE
#endif

/*!
 * @def         XEOS_UNAVAILABLE_ATTRIBUTE
 * @brief       Standardization of the unavailable compiler attribute
 * @details     Not all compiler support this attribute, so it may be defined
 *              to nothing.
 */
#if defined( __GNUC__ ) && ( ( __GNUC__ >= 4 ) || ( ( __GNUC__ == 3 ) && ( __GNUC_MINOR__ >= 1 ) ) )
    #define XEOS_UNAVAILABLE_ATTRIBUTE __attribute__( ( unavailable ) )
#else
    #define XEOS_UNAVAILABLE_ATTRIBUTE
#endif

/*!
 * @def         XEOS_FORMAT_ATTRIBUTE
 * @brief       Standardization of the format compiler attribute
 * @details     Not all compiler support this attribute, so it may be defined
 *              to nothing.
 */
#if defined( __GNUC__ ) && ( ( __GNUC__ >= 4 ) || ( ( __GNUC__ == 3 ) && ( __GNUC_MINOR__ >= 1 ) ) )
    #define XEOS_FORMAT_ATTRIBUTE( f, s, v ) __attribute__( ( format( f, s, v ) ) )
#else
    #define XEOS_FORMAT_ATTRIBUTE( f, s, v )
#endif

/*!
 * @def         XEOS_CONST_ATTRIBUTE
 * @brief       Standardization of the const compiler attribute
 * @details     Not all compiler support this attribute, so it may be defined
 *              to nothing.
 */
#if defined( __GNUC__ ) && ( ( __GNUC__ >= 4 ) || ( ( __GNUC__ == 3 ) && ( __GNUC_MINOR__ >= 1 ) ) )
    #define XEOS_CONST_ATTRIBUTE __attribute__( ( const ) )
#else
    #define XEOS_CONST_ATTRIBUTE
#endif

/*!
 * @def         XEOS_NORETURN_ATTRIBUTE
 * @brief       Standardization of the noreturn compiler attribute
 * @details     Not all compiler support this attribute, so it may be defined
 *              to nothing.
 */
#if defined( __GNUC__ ) && ( ( __GNUC__ >= 4 ) || ( ( __GNUC__ == 3 ) && ( __GNUC_MINOR__ >= 1 ) ) )
    #define XEOS_NORETURN_ATTRIBUTE __attribute__( ( noreturn ) )
#else
    #define XEOS_NORETURN_ATTRIBUTE
#endif

#ifdef __cplusplus
}
#endif

#endif /* __XEOS_MACROS_H__ */
