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

#ifndef __HAL_SMBIOS_H__
#define __HAL_SMBIOS_H__
#pragma once

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/* SMBIOS related constants */
#define HAL_SMBIOS_MEM_START                                                    0x000F0000
#define HAL_SMBIOS_MEM_END                                                      0x000FFFFF
#define HAL_SMBIOS_SIGNATURE                                                    "_SM_"
#define HAL_SMBIOS_DMI_SIGNATURE                                                "_DMI_"

/* SMBIOS structures identifiers */
#define HAL_SMBIOS_STRUCT_BIOS_INFORMATION                                      0   /* Required */
#define HAL_SMBIOS_STRUCT_SYSTEM_INFORMATION                                    1   /* Required */
#define HAL_SMBIOS_STRUCT_BASE_BOARD_INFORMATION                                2
#define HAL_SMBIOS_STRUCT_SYSTEM_ENCLOSURE                                      3   /* Required */
#define HAL_SMBIOS_STRUCT_PROCESSOR_INFORMATION                                 4   /* Required */
#define HAL_SMBIOS_STRUCT_MEMORY_CONTROLLER_INFORMATION                         5   /* Obsolete */
#define HAL_SMBIOS_STRUCT_MEMORY_MODULE_INFORMATION                             6   /* Obsolete */
#define HAL_SMBIOS_STRUCT_CACHE_INFORMATION                                     7   /* Required */
#define HAL_SMBIOS_STRUCT_PORT_CONNECTOR_INFORMATION                            8
#define HAL_SMBIOS_STRUCT_SYSTEM_SLOTS                                          9   /* Required */
#define HAL_SMBIOS_STRUCT_ON_BOARD_DEVICES_INFORMATION                          10  /* Obsolete */
#define HAL_SMBIOS_STRUCT_OEM_STRINGS                                           11
#define HAL_SMBIOS_STRUCT_SYSTEM_CONFIGURATION_OPTIONS                          12
#define HAL_SMBIOS_STRUCT_BIOS_LANGUAGE_INFORMATION                             13
#define HAL_SMBIOS_STRUCT_GROUP_ASSOCIATIONS                                    14
#define HAL_SMBIOS_STRUCT_SYSTEM_EVENT_LOG                                      15
#define HAL_SMBIOS_STRUCT_PHYSICAL_MEMORY_ARRAY                                 16   /* Required */
#define HAL_SMBIOS_STRUCT_MEMORY_DEVICE                                         17   /* Required */
#define HAL_SMBIOS_STRUCT_32_BIT_MEMORY_ERROR_INFORMATION                       18
#define HAL_SMBIOS_STRUCT_MEMORY_ARRAY_MAPPED_ADDRESS                           19   /* Required */
#define HAL_SMBIOS_STRUCT_MEMORY_DEVICE_MAPPED_ADDRESS                          20
#define HAL_SMBIOS_STRUCT_BUILT_IN_POINTING_DEVICE                              21
#define HAL_SMBIOS_STRUCT_PORTABLE_BATTERY                                      22
#define HAL_SMBIOS_STRUCT_SYSTEM_RESET                                          23
#define HAL_SMBIOS_STRUCT_HARDWARE_SECURITY                                     24
#define HAL_SMBIOS_STRUCT_SYSTEM_POWER_CONTROLS                                 25
#define HAL_SMBIOS_STRUCT_VOLTAGE_PROBE                                         26
#define HAL_SMBIOS_STRUCT_COOLING_DEVICE                                        27
#define HAL_SMBIOS_STRUCT_TEMPERATURE_PROBE                                     28
#define HAL_SMBIOS_STRUCT_ELECTRICAL_CURRENT_PROBE                              29
#define HAL_SMBIOS_STRUCT_OUT_OF_BAND_REMOTE_ACCESS                             30
#define HAL_SMBIOS_STRUCT_BOOT_INTEGRITY_SERVICES_ENTRY_POINT                   31
#define HAL_SMBIOS_STRUCT_SYSTEM_BOOT_INFORMATION                               32   /* Required */
#define HAL_SMBIOS_STRUCT_64_BIT_MEMORY_ERROR_INFORMATION                       33
#define HAL_SMBIOS_STRUCT_MANAGEMENT_DEVICE                                     34
#define HAL_SMBIOS_STRUCT_MANAGEMENT_DEVICE_COMPONENT                           35
#define HAL_SMBIOS_STRUCT_MANAGEMENT_DEVICE_THRESHOLD_DATA                      36
#define HAL_SMBIOS_STRUCT_MEMORY_CHANNEL                                        37
#define HAL_SMBIOS_STRUCT_IPMI_DEVICE_INFORMATION                               38
#define HAL_SMBIOS_STRUCT_SYSTEM_POWER_SUPPLY                                   39
#define HAL_SMBIOS_STRUCT_ADDITIONAL_INFORMATION                                40
#define HAL_SMBIOS_STRUCT_ONBOARD_DEVICES_EXTENDED_INFORMATION                  41
#define HAL_SMBIOS_STRUCT_INACTIVE                                              126
#define HAL_SMBIOS_STRUCT_END_OF_TABLE                                          127

/* SMBIOS CPU types */
#define HAL_SMBIOS_CPU_TYPE_OTHER                                               0x01
#define HAL_SMBIOS_CPU_TYPE_UNKNOWN                                             0x02
#define HAL_SMBIOS_CPU_TYPE_CENTRAL                                             0x03
#define HAL_SMBIOS_CPU_TYPE_MATH                                                0x04
#define HAL_SMBIOS_CPU_TYPE_DSP                                                 0x05
#define HAL_SMBIOS_CPU_TYPE_VIDEO                                               0x06

/* SMBIOS CPU families */
#define HAL_SMBIOS_CPU_OTHER                                                    0x01
#define HAL_SMBIOS_CPU_UNKNOWN                                                  0x02
#define HAL_SMBIOS_CPU_8086                                                     0x03
#define HAL_SMBIOS_CPU_80286                                                    0x04
#define HAL_SMBIOS_CPU_INTEL386_PROCESSOR                                       0x05
#define HAL_SMBIOS_CPU_INTEL486_PROCESSOR                                       0x06
#define HAL_SMBIOS_CPU_8087                                                     0x07
#define HAL_SMBIOS_CPU_80287                                                    0x08
#define HAL_SMBIOS_CPU_80387                                                    0x09
#define HAL_SMBIOS_CPU_80487                                                    0x0A
#define HAL_SMBIOS_CPU_PENTIUM_PROCESSOR_FAMILY                                 0x0B
#define HAL_SMBIOS_CPU_PENTIUM_PRO_PROCESSOR                                    0x0C
#define HAL_SMBIOS_CPU_PENTIUM_II_PROCESSOR                                     0x0D
#define HAL_SMBIOS_CPU_PENTIUM_PROCESSOR_WITH_MMX_TECHNOLOGY                    0x0E
#define HAL_SMBIOS_CPU_CELERON_PROCESSOR                                        0x0F
#define HAL_SMBIOS_CPU_PENTIUM_II_XEON_PROCESSOR                                0x10
#define HAL_SMBIOS_CPU_PENTIUM_III_PROCESSOR                                    0x11
#define HAL_SMBIOS_CPU_M1_FAMILY                                                0x12
#define HAL_SMBIOS_CPU_M2_FAMILY                                                0x13
#define HAL_SMBIOS_CPU_INTEL_CELERON_M_PROCESSOR                                0x14
#define HAL_SMBIOS_CPU_INTEL_PENTIUM_4_HT_PROCESSOR                             0x15
#define HAL_SMBIOS_CPU_AMD_DURON_PROCESSOR_FAMILY                               0x18
#define HAL_SMBIOS_CPU_K5_FAMILY                                                0x19
#define HAL_SMBIOS_CPU_K6_FAMILY                                                0x1A
#define HAL_SMBIOS_CPU_K6_2                                                     0x1B
#define HAL_SMBIOS_CPU_K6_3                                                     0x1C
#define HAL_SMBIOS_CPU_AMD_ATHLON_PROCESSOR_FAMILY                              0x1D
#define HAL_SMBIOS_CPU_AMD29000_FAMILY                                          0x1E
#define HAL_SMBIOS_CPU_K6_2_PLUS                                                0x1F
#define HAL_SMBIOS_CPU_POWER_PC_FAMILY                                          0x20
#define HAL_SMBIOS_CPU_POWER_PC_601                                             0x21
#define HAL_SMBIOS_CPU_POWER_PC_603                                             0x22
#define HAL_SMBIOS_CPU_POWER_PC_603_PLUS                                        0x23
#define HAL_SMBIOS_CPU_POWER_PC_604                                             0x24
#define HAL_SMBIOS_CPU_POWER_PC_620                                             0x25
#define HAL_SMBIOS_CPU_POWER_PC_X704                                            0x26
#define HAL_SMBIOS_CPU_POWER_PC_750                                             0x27
#define HAL_SMBIOS_CPU_INTEL_CORE_DUO_PROCESSOR                                 0x28
#define HAL_SMBIOS_CPU_INTEL_CORE_DUO_MOBILE_PROCESSOR                          0x29
#define HAL_SMBIOS_CPU_INTEL_CORE_SOLO_MOBILE_PROCESSOR                         0x2A
#define HAL_SMBIOS_CPU_ALPHA_FAMILY3                                            0x30
#define HAL_SMBIOS_CPU_ALPHA_21064                                              0x31
#define HAL_SMBIOS_CPU_ALPHA_21066                                              0x32
#define HAL_SMBIOS_CPU_ALPHA_21164                                              0x33
#define HAL_SMBIOS_CPU_ALPHA_21164PC                                            0x34
#define HAL_SMBIOS_CPU_ALPHA_21164A                                             0x35
#define HAL_SMBIOS_CPU_ALPHA_21264                                              0x36
#define HAL_SMBIOS_CPU_ALPHA_21364                                              0x37
#define HAL_SMBIOS_CPU_MIPS_FAMILY                                              0x40
#define HAL_SMBIOS_CPU_MIPS_R4000                                               0x41
#define HAL_SMBIOS_CPU_MIPS_R4200                                               0x42
#define HAL_SMBIOS_CPU_MIPS_R4400                                               0x43
#define HAL_SMBIOS_CPU_MIPS_R4600                                               0x44
#define HAL_SMBIOS_CPU_MIPS_R10000                                              0x45
#define HAL_SMBIOS_CPU_SPARC_FAMILY                                             0x50
#define HAL_SMBIOS_CPU_SUPERSPARC                                               0x51
#define HAL_SMBIOS_CPU_MICROSPARC_II                                            0x52
#define HAL_SMBIOS_CPU_MICROSPARC_IIEP                                          0x53
#define HAL_SMBIOS_CPU_ULTRASPARC                                               0x54
#define HAL_SMBIOS_CPU_ULTRASPARC_II                                            0x55
#define HAL_SMBIOS_CPU_ULTRASPARC_II_I                                          0x56
#define HAL_SMBIOS_CPU_ULTRASPARC_III                                           0x57
#define HAL_SMBIOS_CPU_ULTRASPARC_III_I                                         0x58
#define HAL_SMBIOS_CPU_68040_FAMILY                                             0x60
#define HAL_SMBIOS_CPU_68XXX                                                    0x61
#define HAL_SMBIOS_CPU_68000                                                    0x62
#define HAL_SMBIOS_CPU_68010                                                    0x63
#define HAL_SMBIOS_CPU_68020                                                    0x64
#define HAL_SMBIOS_CPU_68030                                                    0x65
#define HAL_SMBIOS_CPU_HOBBIT_FAMILY                                            0x70
#define HAL_SMBIOS_CPU_CRUSOE_TM5000_FAMILY                                     0x78
#define HAL_SMBIOS_CPU_CRUSOE_TM3000_FAMILY                                     0x79
#define HAL_SMBIOS_CPU_EFFICEON_TM8000_FAMILY                                   0x7A
#define HAL_SMBIOS_CPU_WEITEK                                                   0x80
#define HAL_SMBIOS_CPU_ITANIUM_PROCESSOR                                        0x82
#define HAL_SMBIOS_CPU_AMD_ATHLON_64_PROCESSOR_FAMILY                           0x83
#define HAL_SMBIOS_CPU_AMD_OPTERON_PROCESSOR_FAMILY                             0x84
#define HAL_SMBIOS_CPU_AMD_SEMPRON_PROCESSOR_FAMILY                             0x85
#define HAL_SMBIOS_CPU_AMD_TURION_64_MOBILE_TECHNOLOGY                          0x86
#define HAL_SMBIOS_CPU_DUAL_CORE_AMD_OPTERON_PROCESSOR_FAMILY                   0x87
#define HAL_SMBIOS_CPU_AMD_ATHLON_64_X2_DUAL_CORE_PROCESSOR_FAMILY              0x88
#define HAL_SMBIOS_CPU_AMD_TURION_64_X2_MOBILE_TECHNOLOGY                       0x89
#define HAL_SMBIOS_CPU_QUAD_CORE_AMD_OPTERON_PROCESSOR_FAMILY                   0x8A
#define HAL_SMBIOS_CPU_THIRD_GENERATION_AMD_OPTERON_PROCESSOR_FAMILY            0x8B
#define HAL_SMBIOS_CPU_AMD_PHENOM_FX_QUAD_CORE_PROCESSOR_FAMILY                 0x8C
#define HAL_SMBIOS_CPU_AMD_PHENOM_X4_QUAD_CORE_PROCESSOR_FAMILY                 0x8D
#define HAL_SMBIOS_CPU_AMD_PHENOM_X2_DUAL_CORE_PROCESSOR_FAMILY                 0x8E
#define HAL_SMBIOS_CPU_AMD_ATHLON_X2_DUAL_CORE_PROCESSOR_FAMILY                 0x8F
#define HAL_SMBIOS_CPU_PA_RISC_FAMILY                                           0x90
#define HAL_SMBIOS_CPU_PA_RISC_8500                                             0x91
#define HAL_SMBIOS_CPU_PA_RISC_8000                                             0x92
#define HAL_SMBIOS_CPU_PA_RISC_7300LC                                           0x93
#define HAL_SMBIOS_CPU_PA_RISC_7200                                             0x94
#define HAL_SMBIOS_CPU_PA_RISC_7100LC                                           0x95
#define HAL_SMBIOS_CPU_PA_RISC_7100                                             0x96
#define HAL_SMBIOS_CPU_V30_FAMILY                                               0xA0
#define HAL_SMBIOS_CPU_QUAD_CORE_INTEL_XEON_PROCESSOR_3200_SERIES               0xA1
#define HAL_SMBIOS_CPU_DUAL_CORE_INTEL_XEON_PROCESSOR_3000_SERIES               0xA2
#define HAL_SMBIOS_CPU_QUAD_CORE_INTEL_XEON_PROCESSOR_5300_SERIES               0xA3
#define HAL_SMBIOS_CPU_DUAL_CORE_INTEL_XEON_PROCESSOR_5100_SERIES               0xA4
#define HAL_SMBIOS_CPU_DUAL_CORE_INTEL_XEON_PROCESSOR_5000_SERIES               0xA5
#define HAL_SMBIOS_CPU_DUAL_CORE_INTEL_XEON_PROCESSOR_LV                        0xA6
#define HAL_SMBIOS_CPU_DUAL_CORE_INTEL_XEON_PROCESSOR_ULV                       0xA7
#define HAL_SMBIOS_CPU_DUAL_CORE_INTEL_XEON_PROCESSOR_7100_SERIES               0xA8
#define HAL_SMBIOS_CPU_QUAD_CORE_INTEL_XEON_PROCESSOR_5400_SERIES               0xA9
#define HAL_SMBIOS_CPU_QUAD_CORE_INTEL_XEON_PROCESSOR                           0xAA
#define HAL_SMBIOS_CPU_DUAL_CORE_INTEL_XEON_PROCESSOR_5200_SERIES               0xAB
#define HAL_SMBIOS_CPU_DUAL_CORE_INTEL_XEON_PROCESSOR_7200_SERIES               0xAC
#define HAL_SMBIOS_CPU_QUAD_CORE_INTEL_XEON_PROCESSOR_7300_SERIES               0xAD
#define HAL_SMBIOS_CPU_QUAD_CORE_INTEL_XEON_PROCESSOR_7400_SERIES               0xAE
#define HAL_SMBIOS_CPU_MULTI_CORE_INTEL_XEON_PROCESSOR_7400_SERIES              0xAF
#define HAL_SMBIOS_CPU_PENTIUM_III_XEON_PROCESSOR                               0xB0
#define HAL_SMBIOS_CPU_PENTIUM_III_PROCESSOR_WITH_INTEL_SPEEDSTEP_TECHNOLOGY    0xB1
#define HAL_SMBIOS_CPU_PENTIUM_4_PROCESSOR                                      0xB2
#define HAL_SMBIOS_CPU_INTEL_XEON                                               0xB3
#define HAL_SMBIOS_CPU_AS400_FAMILY                                             0xB4
#define HAL_SMBIOS_CPU_INTEL_XEON_PROCESSOR_MP                                  0xB5
#define HAL_SMBIOS_CPU_AMD_ATHLON_XP_PROCESSOR_FAMILY                           0xB6
#define HAL_SMBIOS_CPU_AMD_ATHLON_MP_PROCESSOR_FAMILY                           0xB7
#define HAL_SMBIOS_CPU_INTEL_ITANIUM_2_PROCESSOR                                0xB8
#define HAL_SMBIOS_CPU_INTEL_PENTIUM_M_PROCESSOR                                0xB9
#define HAL_SMBIOS_CPU_INTEL_CELERON_D_PROCESSOR                                0xBA
#define HAL_SMBIOS_CPU_INTEL_PENTIUM_D_PROCESSOR                                0xBB
#define HAL_SMBIOS_CPU_INTEL_PENTIUM_PROCESSOR_EXTREME_EDITION                  0xBC
#define HAL_SMBIOS_CPU_INTEL_CORE_SOLO_PROCESSOR                                0xBD
#define HAL_SMBIOS_CPU_INTEL_CORE2_DUO_PROCESSOR                                0xBF
#define HAL_SMBIOS_CPU_INTEL_CORE2_SOLO_PROCESSOR                               0xC0
#define HAL_SMBIOS_CPU_INTEL_CORE2_EXTREME_PROCESSOR                            0xC1
#define HAL_SMBIOS_CPU_INTEL_CORE2_QUAD_PROCESSOR                               0xC2
#define HAL_SMBIOS_CPU_INTEL_CORE2_EXTREME_MOBILE_PROCESSOR                     0xC3
#define HAL_SMBIOS_CPU_INTEL_CORE2_DUO_MOBILE_PROCESSOR                         0xC4
#define HAL_SMBIOS_CPU_INTEL_CORE2_SOLO_MOBILE_PROCESSOR                        0xC5
#define HAL_SMBIOS_CPU_INTEL_CORE_I7_PROCESSOR                                  0xC6
#define HAL_SMBIOS_CPU_DUAL_CORE_INTEL_CELERON_PROCESSOR                        0xC7
#define HAL_SMBIOS_CPU_IBM390_FAMILY                                            0xC8
#define HAL_SMBIOS_CPU_G4                                                       0xC9
#define HAL_SMBIOS_CPU_G5                                                       0xCA
#define HAL_SMBIOS_CPU_ESA_390_G6                                               0xCB
#define HAL_SMBIOS_CPU_Z_ARCHITECTUR_BASE                                       0xCC
#define HAL_SMBIOS_CPU_VIA_C7_M_PROCESSOR_FAMILY                                0xD2
#define HAL_SMBIOS_CPU_VIA_C7_D_PROCESSOR_FAMILY                                0xD3
#define HAL_SMBIOS_CPU_VIA_C7_PROCESSOR_FAMILY                                  0xD4
#define HAL_SMBIOS_CPU_VIA_EDEN_PROCESSOR_FAMILY                                0xD5
#define HAL_SMBIOS_CPU_MULTI_CORE_INTEL_XEON_PROCESSOR                          0xD6
#define HAL_SMBIOS_CPU_DUAL_CORE_INTEL_XEON_PROCESSOR_3XXX_SERIES               0xD7
#define HAL_SMBIOS_CPU_QUAD_CORE_INTEL_XEON_PROCESSOR_3XXX_SERIES               0xD8
#define HAL_SMBIOS_CPU_DUAL_CORE_INTEL_XEON_PROCESSOR_5XXX_SERIES               0xDA
#define HAL_SMBIOS_CPU_QUAD_CORE_INTEL_XEON_PROCESSOR_5XXX_SERIES               0xDB
#define HAL_SMBIOS_CPU_DUAL_CORE_INTEL_XEON_PROCESSOR_7XXX_SERIES               0xDD
#define HAL_SMBIOS_CPU_QUAD_CORE_INTEL_XEON_PROCESSOR_7XXX_SERIES               0xDE
#define HAL_SMBIOS_CPU_MULTI_CORE_INTEL_XEON_PROCESSOR_7XXX_SERIES              0xDF
#define HAL_SMBIOS_CPU_EMBEDDED_AMD_OPTERON_QUAD_CORE_PROCESSOR_FAMILY          0xE6
#define HAL_SMBIOS_CPU_AMD_PHENOM_TRIPLE_CORE_PROCESSOR_FAMILY                  0xE7
#define HAL_SMBIOS_CPU_AMD_TURION_ULTRA_DUAL_CORE_MOBILE_PROCESSOR_FAMILY       0xE8
#define HAL_SMBIOS_CPU_AMD_TURION_DUAL_CORE_MOBILE_PROCESSOR_FAMILY             0xE9
#define HAL_SMBIOS_CPU_AMD_ATHLON_DUAL_CORE_PROCESSOR_FAMILY                    0xEA
#define HAL_SMBIOS_CPU_AMD_SEMPRON_SI_PROCESSOR_FAMILY                          0xEB
#define HAL_SMBIOS_CPU_I860                                                     0xFA
#define HAL_SMBIOS_CPU_I960                                                     0xFB
#define HAL_SMBIOS_CPU_SH_3                                                     0x104
#define HAL_SMBIOS_CPU_SH_4                                                     0x105
#define HAL_SMBIOS_CPU_ARM                                                      0x118
#define HAL_SMBIOS_CPU_STRONGARM                                                0x119
#define HAL_SMBIOS_CPU_6X86                                                     0x12C
#define HAL_SMBIOS_CPU_MEDIAGX                                                  0x12D
#define HAL_SMBIOS_CPU_MII                                                      0x12E
#define HAL_SMBIOS_CPU_WINCHIP                                                  0x140
#define HAL_SMBIOS_CPU_DSP                                                      0x15E
#define HAL_SMBIOS_CPU_VIDEO_PROCESSOR                                          0x1F4

/**
 * SMBIOS Structure Table Entry Point
 * 
 * On non-EFI systems, the SMBIOS Entry Point structure, described below, can be
 * located by application software by searching for the anchor-string on
 * paragraph (16-byte) boundaries within the physical memory address range
 * 000F0000h to 000FFFFFh. This entry point encapsulates an intermediate anchor
 * string that is used by some existing DMI browsers.
 * 
 * The structure is the following:
 *      
 *      00h:        Anchor String (4 BYTEs)
 *                  _SM_, specified as four ASCII characters (5F 53 4D 5F).
 *      
 *      04h:        Entry Point Structure Checksum (BYTE)
 *                  Checksum of the Entry Point Structure (EPS). This value,
 *                  when added to all other bytes in the EPS, will result in the
 *                  value 00h (using 8-bit addition calculations). Values in the
 *                  EPS are summed starting at offset 00h, for Entry Point
 *                  Length bytes.
 *      
 *      05h:        Entry Point Length (BYTE)
 *                  Length of the Entry Point Structure, starting with the
 *                  Anchor String field, in bytes, currently 1Fh.
 *      
 *      06h:        SMBIOS Major Version (BYTE)
 *                  Identifies the major version of this specification
 *                  implemented in the table structures, e.g. the value will be
 *                  0Ah for revision 10.22 and 02h for revision 2.1.
 *      
 *      07h:        SMBIOS Minor Version (BYTE)
 *                  Identifies the minor version of this specification
 *                  implemented in the table structures, e.g. the value will be
 *                  16h for revision 10.22 and 01h for revision 2.1.
 *      
 *      08h:        Maximum Structure Size (WORD)
 *                  Size of the largest SMBIOS structure, in bytes, and
 *                  encompasses the structure’s formatted area and text strings.
 *                  This is the value returned as StructureSize from the
 *                  Plug-and-Play Get SMBIOS Information function.
 *      
 *      0Ah:        Entry Point Revision (BYTE)
 *                  Identifies the EPS revision implemented in this structure
 *                  and identifies the formatting of offsets 0Bh to 0Fh, one of:
 *                  00h	Entry Point is based on SMBIOS 2.1 definition; formatted
 *                  area is reserved and set to all 00h. 01h-FFh Reserved for
 *                  assignment via this specification
 *      
 *      0Bh - 0Fh:  Formatted Area (5 BYTEs)
 *                  The value present in the Entry Point Revision field defines
 *                  the interpretation to be placed upon these 5 bytes.
 *      
 *      10h:        Intermediate anchor string (5 BYTEs)
 *                  _DMI_, specified as five ASCII characters (5F 44 4D 49 5F).
 *                  Note: This field is paragraph-aligned, to allow legacy DMI
 *                  browsers to find this entry point within the SMBIOS Entry
 *                  Point Structure.
 *      
 *      15h:        Intermediate Checksum (BYTE)
 *                  Checksum of Intermediate Entry Point Structure (IEPS). This
 *                  value, when added to all other bytes in the IEPS, will
 *                  result in the value 00h (using 8-bit addition calculations).
 *                  Values in the IEPS are summed starting at offset 10h,
 *                  for 0Fh bytes.
 *      
 *      16h:        Structure Table Length (WORD)
 *                  Total length of SMBIOS Structure Table, pointed to by the
 *                  Structure Table Address, in bytes.
 *      
 *      18h:        Structure Table Address (DWORD)
 *                  The 32-bit physical starting address of the read-only SMBIOS
 *                  Structure Table, that can start at any 32-bit address.
 *                  This area contains all of the SMBIOS structures fully packed
 *                  together. These structures can then be parsed to produce
 *                  exactly the same format as that returned from a Get SMBIOS
 *                  Structure function call.
 *      
 *      1Ch:        Number of SMBIOS Structures (WORD)
 *                  Total number of structures present in the SMBIOS Structure
 *                  Table. This is the value returned as NumStructures from the
 *                  Get SMBIOS Information function.
 *      
 *      1Eh:        SMBIOS BCD Revision (BYTE)
 *                  Indicates compliance with a revision of this specification.
 *                  It is a BCD value where the upper nibble indicates the major
 *                  version and the lower nibble the minor version. For revision
 *                  2.1, the returned value is 21h. If the value is 00h, only
 *                  the Major and Minor Versions in offsets 6 and 7 of the
 *                  Entry Point Structure provide the version information.
 */
typedef struct
{
    uint8_t  anchor[ 4 ];
    uint8_t  checksum;
    uint8_t  length;
    uint8_t  version_major;
    uint8_t  version_minor;
    uint16_t max_structure_size;
    uint8_t  revision;
    uint8_t  formatted_area[ 5 ];
    uint8_t  intermediate_anchor[ 5 ];
    uint8_t  intermediate_checksum;
    uint16_t structure_table_length;
    uint32_t structure_table_address;
    uint16_t structures_count;
    uint8_t  bcd_revision;
}
__attribute__( ( packed ) ) hal_smbios_table_entry;

typedef struct
{
    uint8_t      type;
    uint8_t      length;
    uint16_t     handle;
    uintptr_t    address;
}
__attribute__( ( packed ) ) hal_smbios_structure_header;

typedef struct
{
    bool characteristics;
    bool isa;
    bool mca;
    bool eisa;
    bool pci;
    bool pcmcia;
    bool plug_and_play;
    bool apm;
    bool upgradeable;
    bool shadowing;
    bool vl_vesa;
    bool escd;
    bool boot_cd;
    bool boot_select;
    bool rom_socketed;
    bool boot_pcmcia;
    bool edd;
    bool service_floppy_nec9800_japan;
    bool service_floppy_toshiba_japan;
    bool service_floppy_525_360kb;
    bool service_floppy_525_1200kb;
    bool service_floppy_35_720kb;
    bool service_floppy_35_2880kb;
    bool service_print_screen;
    bool service_keyboard;
    bool service_serial;
    bool service_printer;
    bool service_video_cga_mono;
    bool nec_pc98;
    bool acpi;
    bool usb_legacy;
    bool agp;
    bool i20;
    bool ls120;
    bool boot_atapi_zip_drive;
    bool boot_1394;
    bool smart_battery;
}
__attribute__( ( packed ) ) hal_smbios_bios_characteristics;

typedef struct
{
    hal_smbios_structure_header header;
    char * vendor;
    char * version;
    char * date;
    uintptr_t address;
    unsigned int rom_size;
    unsigned int release_major;
    unsigned int release_minor;
    hal_smbios_bios_characteristics * characteristics;
    unsigned int embedded_controller_firmware_major;
    unsigned int embedded_controller_firmware_minor;
}
__attribute__( ( packed ) ) hal_smbios_bios_infos;

/**
 * A UUID is an identifier that is designed to be unique across both time and
 * space, and requires no central registration process. The UUID is 128 bits
 * long. Its format is described in RFC 4122, but the actual field contents are
 * opaque and not significant to the SMBIOS specification, which is only
 * concerned with the byte order.
 * 
 * Although RFC 4122 recommends network byte order for all fields, the PC
 * industry (including the ACPI, UEFI, and Microsoft specifications) has
 * consistently used little-endian byte encoding for the first three fields:
 * time_low, time_mid, time_hi_and_version. The same encoding, also known as
 * wire format, should also be used for the SMBIOS representation of the UUID.
 * 
 * The UUID {00112233-4455-6677-8899-AABBCCDDEEFF} would thus be represented
 * as 33 22 11 00 55 44 77 66 88 99 AA BB CC DD EE FF.
 * 
 * If the value is all FFh, the ID is not currently present in the system, but
 * can be set. If the value is all 00h, the ID is not present in the system.
 */
typedef struct
{
    uint32_t time_low;
    uint16_t time_mid;
    uint16_t time_hi_and_version;
    uint8_t clock_seq_hi_and_reserved;
    uint8_t clock_seq_low;
    uint8_t node[ 6 ];
}
__attribute__( ( packed ) ) hal_smbios_uuid;

/**
 * The information in this structure defines attributes of the overall system
 * and is intended to be associated with the Component ID group of the system's
 * MIF. An SMBIOS implementation is associated with a single system instance
 * and contains one and only one System Information (Type 1) structure.
 */
typedef struct
{
    hal_smbios_structure_header header;
    char  * manufacturer;
    char  * product_name;
    char  * version;
    char  * serial_number;
    hal_smbios_uuid uuid;
    uint8_t wake_up_type;
    char  * sku_number;
    char  * family;
}
__attribute__( ( packed ) ) hal_smbios_system_infos;

typedef struct
{
    hal_smbios_structure_header header;
}
__attribute__( ( packed ) ) hal_smbios_system_enclosure;

typedef struct
{
    hal_smbios_structure_header header;
    char * socket;
    uint8_t type;
    uint8_t family;
    char * manufacturer;
    uint64_t id;
    char * version;
    float voltage;
    uint16_t external_clock;
    uint16_t max_speed;
    uint16_t speed;
    uint8_t status;
    uint8_t upgrade;
    uint16_t cache_l1_handle;
    uint16_t cache_l2_handle;
    uint16_t cache_l3_handle;
    char * serial_number;
    char * asset_tag;
    char * part_number;
    uint8_t core_count;
    uint8_t core_enabled;
    uint8_t thread_count;
    uint16_t characteristics;
    uint16_t family2;
}
__attribute__( ( packed ) ) hal_smbios_processor_infos;

typedef struct
{
    hal_smbios_structure_header header;
}
__attribute__( ( packed ) ) hal_smbios_cache_infos;

typedef struct
{
    hal_smbios_structure_header header;
}
__attribute__( ( packed ) ) hal_smbios_system_slots;

typedef struct
{
    hal_smbios_structure_header header;
}
__attribute__( ( packed ) ) hal_smbios_physical_memory_array;

typedef struct
{
    hal_smbios_structure_header header;
}
__attribute__( ( packed ) ) hal_smbios_memory_device;

typedef struct
{
    hal_smbios_structure_header header;
}
__attribute__( ( packed ) ) hal_smbios_memory_mapped_address;

typedef struct
{
    hal_smbios_structure_header header;
}
__attribute__( ( packed ) ) hal_smbios_system_boot_infos;

typedef struct
{
    hal_smbios_bios_infos            * bios_infos;
    hal_smbios_system_infos          * system_infos;
    hal_smbios_system_enclosure      * system_enclosure;
    hal_smbios_processor_infos       * processor_infos;
    hal_smbios_cache_infos           * cache_infos;
    hal_smbios_system_slots          * system_slots;
    hal_smbios_physical_memory_array * physical_memory_array;
    hal_smbios_memory_device         * memory_device ;
    hal_smbios_memory_mapped_address * memory_mapped_address;
    hal_smbios_system_boot_infos     * system_boot_infos;
}
__attribute__( ( packed ) ) hal_smbios_infos;

hal_smbios_table_entry * hal_smbios_find_entry( void );
bool hal_smbios_verifiy_checksum( hal_smbios_table_entry * entry );
bool hal_smbios_verifiy_intermediate_checksum( hal_smbios_table_entry * entry );
void * hal_smbios_get_infos( hal_smbios_table_entry * entry, uint8_t type );
char * hal_smbios_processor_type_string( uint8_t number );
char * hal_smbios_processor_family_string( uint8_t number );
char * hal_smbios_uuid_string( hal_smbios_uuid * uuid );

#ifdef __cplusplus
}
#endif

#endif /* __HAL_SMBIOS_H__ */
