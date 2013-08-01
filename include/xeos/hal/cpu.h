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
 * @header          cpu.h
 * @author          Jean-David Gadina
 * @copyright       (c) 2010-2013, Jean-David Gadina - www.xs-labs.com
 */

#ifndef __XEOS_HAL_CPU_H__
#define __XEOS_HAL_CPU_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <xeos/macros.h>
#include <stdbool.h>
#include <stdint.h>

/*!
 * @typedef         XEOS_HAL_CPUInfos_Feature
 * @abstract        CPU features
 * @constant        XEOS_HAL_CPUInfos_FeatureFPU            Onboard x87 FPU
 * @constant        XEOS_HAL_CPUInfos_FeatureVME            Virtual mode extensions (VIF)
 * @constant        XEOS_HAL_CPUInfos_FeatureDE             Debugging extensions (CR4 bit 3)
 * @constant        XEOS_HAL_CPUInfos_FeaturePSE            Page size extensions
 * @constant        XEOS_HAL_CPUInfos_FeatureTSC            Time Stamp Counter
 * @constant        XEOS_HAL_CPUInfos_FeatureMSR            Model-specific registers
 * @constant        XEOS_HAL_CPUInfos_FeaturePAE            Physical Address Extension
 * @constant        XEOS_HAL_CPUInfos_FeatureMCE            Machine Check Exception
 * @constant        XEOS_HAL_CPUInfos_FeatureCX8            CMPXCHG8 (compare-and-swap) instruction
 * @constant        XEOS_HAL_CPUInfos_FeatureAPIC           Onboard Advanced Programmable Interrupt Controller
 * @constant        XEOS_HAL_CPUInfos_FeatureSEP            SYSENTER and SYSEXIT instructions
 * @constant        XEOS_HAL_CPUInfos_FeatureMTRR           Memory Type Range Registers
 * @constant        XEOS_HAL_CPUInfos_FeaturePGE            Page Global Enable bit in CR4
 * @constant        XEOS_HAL_CPUInfos_FeatureMCA            Machine check architecture
 * @constant        XEOS_HAL_CPUInfos_FeatureCMOV           Conditional move and FCMOV instructions
 * @constant        XEOS_HAL_CPUInfos_FeaturePAT            Page Attribute Table
 * @constant        XEOS_HAL_CPUInfos_FeaturePSE36          36-bit page huge pages
 * @constant        XEOS_HAL_CPUInfos_FeaturePN             Processor Serial Number
 * @constant        XEOS_HAL_CPUInfos_FeatureCLFlush        CLFLUSH instruction (SSE2)
 * @constant        XEOS_HAL_CPUInfos_FeatureDTS            Debug store: save trace of executed jumps
 * @constant        XEOS_HAL_CPUInfos_FeatureACPI           Onboard thermal control MSRs for ACPI
 * @constant        XEOS_HAL_CPUInfos_FeatureMMX            MMX instructions
 * @constant        XEOS_HAL_CPUInfos_FeatureFXSR           FXSAVE, FXRESTOR instructions, CR4 bit 9
 * @constant        XEOS_HAL_CPUInfos_FeatureSSE            SSE instructions (a.k.a. Katmai New Instructions)
 * @constant        XEOS_HAL_CPUInfos_FeatureSSE2           SSE2 instructions
 * @constant        XEOS_HAL_CPUInfos_FeatureSS             CPU cache supports self-snoop
 * @constant        XEOS_HAL_CPUInfos_FeatureHT             Hyper-threading
 * @constant        XEOS_HAL_CPUInfos_FeatureTM             Thermal monitor automatically limits temperature
 * @constant        XEOS_HAL_CPUInfos_FeatureIA64           IA64 processor emulating x86
 * @constant        XEOS_HAL_CPUInfos_FeaturePBE            Pending Break Enable (PBE# pin) wakeup support
 * @constant        XEOS_HAL_CPUInfos_FeaturePNI            Prescott New Instructions (SSE3)
 * @constant        XEOS_HAL_CPUInfos_FeaturePCLMulQDQ      PCLMULQDQ support
 * @constant        XEOS_HAL_CPUInfos_FeatureDTES64         64-bit debug store (edx bit 21)
 * @constant        XEOS_HAL_CPUInfos_FeatureMonitor        MONITOR and MWAIT instructions (SSE3)
 * @constant        XEOS_HAL_CPUInfos_FeatureDSCPL          CPL qualified debug store
 * @constant        XEOS_HAL_CPUInfos_FeatureVMX            Virtual Machine eXtensions
 * @constant        XEOS_HAL_CPUInfos_FeatureSMX            Safer Mode Extensions (LaGrande)
 * @constant        XEOS_HAL_CPUInfos_FeatureEST            Enhanced SpeedStep
 * @constant        XEOS_HAL_CPUInfos_FeatureTM2            Thermal Monitor 2
 * @constant        XEOS_HAL_CPUInfos_FeatureSSSE3          Supplemental SSE3 instructions
 * @constant        XEOS_HAL_CPUInfos_FeatureCID            Context ID
 * @constant        XEOS_HAL_CPUInfos_FeatureFMA            Fused multiply-add (FMA3)
 * @constant        XEOS_HAL_CPUInfos_FeatureCX16           CMPXCHG16B instruction
 * @constant        XEOS_HAL_CPUInfos_FeatureXTPT           Can disable sending task priority messages
 * @constant        XEOS_HAL_CPUInfos_FeaturePDCM           Perfmon & debug capability
 * @constant        XEOS_HAL_CPUInfos_FeaturePCID           Process context identifiers (CR4 bit 17)
 * @constant        XEOS_HAL_CPUInfos_FeatureDCA            Direct cache access for DMA writes
 * @constant        XEOS_HAL_CPUInfos_FeatureSSE41          SSE4.1 instructions
 * @constant        XEOS_HAL_CPUInfos_FeatureSSE42          SSE4.2 instructions
 * @constant        XEOS_HAL_CPUInfos_FeatureX2APIC         x2APIC support
 * @constant        XEOS_HAL_CPUInfos_FeatureMOVBE          MOVBE instruction (big-endian, Intel Atom only)
 * @constant        XEOS_HAL_CPUInfos_FeaturePOPCNT         POPCNT instruction
 * @constant        XEOS_HAL_CPUInfos_FeatureTSCDeadLine    APIC supports one-shot operation using a TSC deadline value
 * @constant        XEOS_HAL_CPUInfos_FeatureAES            AES instruction set
 * @constant        XEOS_HAL_CPUInfos_FeatureXSave          XSAVE, XRESTOR, XSETBV, XGETBV
 * @constant        XEOS_HAL_CPUInfos_FeatureOSXSave        XSAVE enabled by OS
 * @constant        XEOS_HAL_CPUInfos_FeatureAVX            Advanced Vector Extensions
 * @constant        XEOS_HAL_CPUInfos_FeatureF16C           CVT16 instruction set (half-precision) FP support
 * @constant        XEOS_HAL_CPUInfos_FeatureRDRND          RDRAND (on-chip random number generator) support
 * @constant        XEOS_HAL_CPUInfos_FeatureHypervisor     Running on a hypervisor (always 0 on a real CPU)
 */
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

#ifdef __clang__
#pragma pack( 1 )
#endif

#ifdef __LP64__

/*!
 * @typedef         XEOS_HAL_CPU_Registers
 * @abstract        x86-64 registers
 * @discussion      Structure representing the x86-64 registers. For i386, the
 *                  same typedef is available, but with a different layout.
 * @var             rax             RAX register
 * @var             rbx             RBX register
 * @var             rcx             RCX register
 * @var             rdx             RDX register
 * @var             rdi             RDI register
 * @var             rsi             RSI register
 * @var             r8              R8 register
 * @var             r9              R9 register
 * @var             r10             R10 register
 * @var             r11             R11 register
 * @var             r12             R12 register
 * @var             r13             R13 register
 * @var             r14             R14 register
 * @var             r15             R15 register
 * @var             rsp             R16 register
 * @var             rbp             R17 register
 */
typedef struct
{
    uint64_t rax;
    uint64_t rbx;
    uint64_t rcx;
    uint64_t rdx;
    uint64_t rsi;
    uint64_t rdi;
    uint64_t r8;
    uint64_t r9;
    uint64_t r10;
    uint64_t r11;
    uint64_t r12;
    uint64_t r13;
    uint64_t r14;
    uint64_t r15;
    uint64_t rsp;
    uint64_t rbp;
}
XEOS_HAL_CPU_Registers;

#else

/*!
 * @typedef         XEOS_HAL_CPU_Registers
 * @abstract        i386 registers
 * @discussion      Structure representing the i386 registers. For x86-64, the
 *                  same typedef is available, but with a different layout.
 * @var             eax             EAX register
 * @var             ebx             EBX register
 * @var             ecx             ECX register
 * @var             edx             EDX register
 * @var             edi             EDI register
 * @var             esi             ESI register
 * @var             esp             E16 register
 * @var             ebp             E17 register
 */
typedef struct
{
    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;
    uint32_t esi;
    uint32_t edi;
    uint32_t esp;
    uint32_t ebp;
}
XEOS_HAL_CPU_Registers;

#endif

#ifdef __clang__
#pragma pack()
#endif

/*!
 * @function        XEOS_HAL_CPU_CPUID
 * @abstract        CPU identification (cpuid instruction)
 * @param           info            The info to request
 * @param           eax             On return, the content of the EAX register
 * @param           ebx             On return, the content of the EBX register
 * @param           ecx             On return, the content of the ECX register
 * @param           edx             On return, the content of the EDX register
 */
void XEOS_HAL_CPU_CPUID( uint32_t info, uint32_t * eax, uint32_t * ebx, uint32_t * ecx, uint32_t * edx );

/*!
 * @function        XEOS_HAL_CPU_HasFeature
 * @abstract        Checks if the CPU supports a feature
 * @param           feature         The CPU feature to check
 * @result          True if the feature is supported, otherwise false
 */
bool XEOS_HAL_CPU_HasFeature( XEOS_HAL_CPUInfos_Feature feature );

/*!
 * @function        XEOS_HAL_CPU_GetVendorID
 * @abstract        Gets the CPU vendor ID string
 * @result          The CPU vendor ID string
 */
const char * XEOS_HAL_CPU_GetVendorID( void );

/*!
 * @function        XEOS_HAL_CPU_GetBrandName
 * @abstract        Gets the CPU brand name string
 * @result          The CPU brand name string
 */
const char * XEOS_HAL_CPU_GetBrandName( void );

/*!
 * @function        XEOS_HAL_CPU_Halt
 * @abstract        Halts the CPU
 */
void XEOS_HAL_CPU_Halt( void );

/*!
 * @function        XEOS_HAL_CPU_EnableInterrupts
 * @abstract        Enables all interrupts
 */
void XEOS_HAL_CPU_EnableInterrupts( void );

/*!
 * @function        XEOS_HAL_CPU_DisableInterrupts
 * @abstract        Disables all interrupts
 */
void XEOS_HAL_CPU_DisableInterrupts( void );

/*!
 * @function        XEOS_HAL_CPU_InterruptsEnabled
 * @abstract        Checks if the interrupts are enabled
 * @result          True if the interrupts are enabled, otherwise false
 */
bool XEOS_HAL_CPU_InterruptsEnabled( void );

/*!
 * @function        XEOS_HAL_CPU_LoadIDT
 * @abstract        Loads the Interrupt Descriptor Table (IDT) pointer
 * @param           p           The IDT pointer
 */
void XEOS_HAL_CPU_LoadIDT( void * p );

/*!
 * @function        XEOS_HAL_CPU_LoadGDT
 * @abstract        Loads the Global Descriptor Table (GDT) pointer
 * @param           p           The GDT pointer
 */
void XEOS_HAL_CPU_LoadGDT( void * p );

/*!
 * @function        XEOS_HAL_CPU_SoftwareInterrupt
 * @abstract        Generates a software interrupt
 * @param           n           The interrupt number
 */
void XEOS_HAL_CPU_SoftwareInterrupt( uint8_t n );

/*!
 * @function        XEOS_HAL_CPU_RDMSR
 * @abstract        Gets the content of a Model Specific Register (MSR)
 * @param           id              The MSR ID
 * @result          The MSR value
 */
uint64_t XEOS_HAL_CPU_RDMSR( uint32_t id );

/*!
 * @function        XEOS_HAL_CPU_WRMSR
 * @abstract        Writes a value into a Model Specifi Register (MSR)
 * @param           id              The MSR ID
 * @param           value           The value to write
 */
void XEOS_HAL_CPU_WRMSR( uint32_t id, uint64_t value );

/*!
 * @function        XEOS_HAL_CPU_GetCR0
 * @abstract        Gets the content of the Control Register 0 (CR0)
 * @result          The content of CR0
 */
uint32_t XEOS_HAL_CPU_GetCR0( void );

/*!
 * @function        XEOS_HAL_CPU_GetCR1
 * @abstract        Gets the content of the Control Register 1 (CR1)
 * @result          The content of CR1
 */
uint32_t XEOS_HAL_CPU_GetCR1( void );

/*!
 * @function        XEOS_HAL_CPU_GetCR2
 * @abstract        Gets the content of the Control Register 2 (CR2)
 * @result          The content of CR2
 */
uint32_t XEOS_HAL_CPU_GetCR2( void );

/*!
 * @function        XEOS_HAL_CPU_GetCR3
 * @abstract        Gets the content of the Control Register 3 (CR3)
 * @result          The content of CR3
 */
uint32_t XEOS_HAL_CPU_GetCR3( void );

/*!
 * @function        XEOS_HAL_CPU_GetCR4
 * @abstract        Gets the content of the Control Register 4 (CR4)
 * @result          The content of CR4
 */
uint32_t XEOS_HAL_CPU_GetCR4( void );

/*!
 * @function        XEOS_HAL_CPU_SetCR0
 * @abstract        Sets the content of the Control Register 0 (CR0)
 * @param           value           The content of CR0
 */
void XEOS_HAL_CPU_SetCR0( uint32_t value );

/*!
 * @function        XEOS_HAL_CPU_SetCR1
 * @abstract        Sets the content of the Control Register 1 (CR1)
 * @param           value           The content of CR1
 */
void XEOS_HAL_CPU_SetCR1( uint32_t value );

/*!
 * @function        XEOS_HAL_CPU_SetCR2
 * @abstract        Sets the content of the Control Register 2 (CR2)
 * @param           value           The content of CR2
 */
void XEOS_HAL_CPU_SetCR2( uint32_t value );

/*!
 * @function        XEOS_HAL_CPU_SetCR3
 * @abstract        Sets the content of the Control Register 3 (CR3)
 * @param           value           The content of CR3
 */
void XEOS_HAL_CPU_SetCR3( uint32_t value );

/*!
 * @function        XEOS_HAL_CPU_SetCR4
 * @abstract        Sets the content of the Control Register 4 (CR4)
 * @param           value           The content of CR4
 */
void XEOS_HAL_CPU_SetCR4( uint32_t value );

/*!
 * @function        XEOS_HAL_CPU_EnablePaging
 * @abstract        Enables paging
 */
void XEOS_HAL_CPU_EnablePaging( void );

/*!
 * @function        XEOS_HAL_CPU_DisablePaging
 * @abstract        Disables paging
 */
void XEOS_HAL_CPU_DisablePaging( void );

/*!
 * @function        XEOS_HAL_CPU_PagingEnabled
 * @abstract        Checks if paging is enabled
 * @result          True if paging is enabled, otherwise false
 */
bool XEOS_HAL_CPU_PagingEnabled( void );

/*!
 * @function        XEOS_HAL_CPU_EnablePAE
 * @abstract        Enables PAE (Physical Address Extension)
 */
void XEOS_HAL_CPU_EnablePAE( void );

/*!
 * @function        XEOS_HAL_CPU_DisablePAE
 * @abstract        Disables PAE (Physical Address Extension)
 */
void XEOS_HAL_CPU_DisablePAE( void );

/*!
 * @function        XEOS_HAL_CPU_PAEEnabled
 * @abstract        Checks if PAE (Physical Address Extension)
 * @result          True if PAE is enabled, otherwise false
 */
bool XEOS_HAL_CPU_PAEEnabled( void );

#ifdef __cplusplus
}
#endif

#endif /* __XEOS_HAL_CPU_H__ */
