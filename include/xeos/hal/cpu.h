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

#ifndef __XEOS_HAL_CPU_H__
#define __XEOS_HAL_CPU_H__
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <xeos/hal/idt.h>
#include <xeos/hal/gdt.h>
#include <stdbool.h>

typedef enum
{
    XEOS_HAL_CPUInfos_FeatureFPU            = 0x000,
    XEOS_HAL_CPUInfos_FeatureVME            = 0x001,
    XEOS_HAL_CPUInfos_FeatureDE             = 0x002,
    XEOS_HAL_CPUInfos_FeaturePSE            = 0x003,
    XEOS_HAL_CPUInfos_FeatureTSC            = 0x004,
    XEOS_HAL_CPUInfos_FeatureMSR            = 0x005,
    XEOS_HAL_CPUInfos_FeaturePAE            = 0x006,
    XEOS_HAL_CPUInfos_FeatureMCE            = 0x007,
    XEOS_HAL_CPUInfos_FeatureCX8            = 0x008,
    XEOS_HAL_CPUInfos_FeatureAPIC           = 0x009,
    XEOS_HAL_CPUInfos_FeatureSEP            = 0x00B,
    XEOS_HAL_CPUInfos_FeatureMTRR           = 0x00C,
    XEOS_HAL_CPUInfos_FeaturePGE            = 0x00D,
    XEOS_HAL_CPUInfos_FeatureMCA            = 0x00E,
    XEOS_HAL_CPUInfos_FeatureCMOV           = 0x00F,
    XEOS_HAL_CPUInfos_FeaturePAT            = 0x010,
    XEOS_HAL_CPUInfos_FeaturePSE36          = 0x011,
    XEOS_HAL_CPUInfos_FeaturePN             = 0x012,
    XEOS_HAL_CPUInfos_FeatureCLFlush        = 0x013,
    XEOS_HAL_CPUInfos_FeatureDTS            = 0x015,
    XEOS_HAL_CPUInfos_FeatureACPI           = 0x016,
    XEOS_HAL_CPUInfos_FeatureMMX            = 0x017,
    XEOS_HAL_CPUInfos_FeatureFXSR           = 0x018,
    XEOS_HAL_CPUInfos_FeatureSSE            = 0x019,
    XEOS_HAL_CPUInfos_FeatureSSE2           = 0x01A,
    XEOS_HAL_CPUInfos_FeatureSS             = 0x01B,
    XEOS_HAL_CPUInfos_FeatureHT             = 0x01C,
    XEOS_HAL_CPUInfos_FeatureTM             = 0x01D,
    XEOS_HAL_CPUInfos_FeatureIA64           = 0x01E,
    XEOS_HAL_CPUInfos_FeaturePBE            = 0x01F,
    
    XEOS_HAL_CPUInfos_FeaturePNI            = 0x100,
    XEOS_HAL_CPUInfos_FeaturePCLMulQDQ      = 0x101,
    XEOS_HAL_CPUInfos_FeatureDTES64         = 0x102,
    XEOS_HAL_CPUInfos_FeatureMonitor        = 0x103,
    XEOS_HAL_CPUInfos_FeatureDSCPL          = 0x104,
    XEOS_HAL_CPUInfos_FeatureVMX            = 0x105,
    XEOS_HAL_CPUInfos_FeatureSMX            = 0x106,
    XEOS_HAL_CPUInfos_FeatureEST            = 0x107,
    XEOS_HAL_CPUInfos_FeatureTM2            = 0x108,
    XEOS_HAL_CPUInfos_FeatureSSSE3          = 0x109,
    XEOS_HAL_CPUInfos_FeatureCID            = 0x10A,
    XEOS_HAL_CPUInfos_FeatureFMA            = 0x10C,
    XEOS_HAL_CPUInfos_FeatureCX16           = 0x10D,
    XEOS_HAL_CPUInfos_FeatureXTPT           = 0x10E,
    XEOS_HAL_CPUInfos_FeaturePDCM           = 0x10F,
    XEOS_HAL_CPUInfos_FeaturePCID           = 0x111,
    XEOS_HAL_CPUInfos_FeatureDCA            = 0x112,
    XEOS_HAL_CPUInfos_FeatureSSE41          = 0x113,
    XEOS_HAL_CPUInfos_FeatureSSE42          = 0x114,
    XEOS_HAL_CPUInfos_FeatureX2APIC         = 0x115,
    XEOS_HAL_CPUInfos_FeatureMOVBE          = 0x116,
    XEOS_HAL_CPUInfos_FeaturePOPCNT         = 0x117,
    XEOS_HAL_CPUInfos_FeatureTSCDeadLine    = 0x118,
    XEOS_HAL_CPUInfos_FeatureAES            = 0x119,
    XEOS_HAL_CPUInfos_FeatureXSave          = 0x11A,
    XEOS_HAL_CPUInfos_FeatureOSXSave        = 0x11B,
    XEOS_HAL_CPUInfos_FeatureAVX            = 0x11C,
    XEOS_HAL_CPUInfos_FeatureF16C           = 0x11D,
    XEOS_HAL_CPUInfos_FeatureRDRND          = 0x11E,
    XEOS_HAL_CPUInfos_FeatureHypervisor     = 0x11F
}
XEOS_HAL_CPUInfos_Feature;

void            XEOS_HAL_CPU_CPUID( uint32_t info, uint32_t * eax, uint32_t * ebx, uint32_t * ecx, uint32_t * edx );
bool            XEOS_HAL_CPU_HasFeature( XEOS_HAL_CPUInfos_Feature feature );
const char *    XEOS_HAL_CPU_GetVendorID( void );
const char *    XEOS_HAL_CPU_GetBrandName( void );
void            XEOS_HAL_CPU_Halt( void );
void            XEOS_HAL_CPU_EnableInterrupts( void );
void            XEOS_HAL_CPU_DisableInterrupts( void );
bool            XEOS_HAL_CPU_InterruptsEnabled( void );
void            XEOS_HAL_CPU_LoadIDT( void * p );
void            XEOS_HAL_CPU_LoadGDT( void * p );
void            XEOS_HAL_CPU_SoftwareInterrupt( uint8_t n );
uint64_t        XEOS_HAL_CPU_RDMSR( uint32_t id );
void            XEOS_HAL_CPU_WRMSR( uint32_t id, uint64_t value );
uint32_t        XEOS_HAL_CPU_ReadCR0( void );
uint32_t        XEOS_HAL_CPU_ReadCR1( void );
uint32_t        XEOS_HAL_CPU_ReadCR2( void );
uint32_t        XEOS_HAL_CPU_ReadCR3( void );
uint32_t        XEOS_HAL_CPU_ReadCR4( void );

#ifdef __cplusplus
}
#endif

#endif /* __XEOS_HAL_CPU_H__ */
