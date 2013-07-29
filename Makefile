#-------------------------------------------------------------------------------
# Copyright (c) 2010-2012, Jean-David Gadina - www.xs-labs.com
# All rights reserved.
# 
# XEOS Software License - Version 1.0 - December 21, 2012
# 
# Permission is hereby granted, free of charge, to any person or organisation
# obtaining a copy of the software and accompanying documentation covered by
# this license (the "Software") to deal in the Software, with or without
# modification, without restriction, including without limitation the rights
# to use, execute, display, copy, reproduce, transmit, publish, distribute,
# modify, merge, prepare derivative works of the Software, and to permit
# third-parties to whom the Software is furnished to do so, all subject to the
# following conditions:
# 
#       1.  Redistributions of source code, in whole or in part, must retain the
#           above copyright notice and this entire statement, including the
#           above license grant, this restriction and the following disclaimer.
# 
#       2.  Redistributions in binary form must reproduce the above copyright
#           notice and this entire statement, including the above license grant,
#           this restriction and the following disclaimer in the documentation
#           and/or other materials provided with the distribution, unless the
#           Software is distributed by the copyright owner as a library.
#           A "library" means a collection of software functions and/or data
#           prepared so as to be conveniently linked with application programs
#           (which use some of those functions and data) to form executables.
# 
#       3.  The Software, or any substancial portion of the Software shall not
#           be combined, included, derived, or linked (statically or
#           dynamically) with software or libraries licensed under the terms
#           of any GNU software license, including, but not limited to, the GNU
#           General Public License (GNU/GPL) or the GNU Lesser General Public
#           License (GNU/LGPL).
# 
#       4.  All advertising materials mentioning features or use of this
#           software must display an acknowledgement stating that the product
#           includes software developed by the copyright owner.
# 
#       5.  Neither the name of the copyright owner nor the names of its
#           contributors may be used to endorse or promote products derived from
#           this software without specific prior written permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT OWNER AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE, TITLE AND NON-INFRINGEMENT ARE DISCLAIMED.
# 
# IN NO EVENT SHALL THE COPYRIGHT OWNER, CONTRIBUTORS OR ANYONE DISTRIBUTING
# THE SOFTWARE BE LIABLE FOR ANY CLAIM, DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
# OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN ACTION OF CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
# NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF OR IN CONNECTION WITH
# THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE, EVEN IF ADVISED
# OF THE POSSIBILITY OF SUCH DAMAGE.
#-------------------------------------------------------------------------------

# $Id$

include ../../../Makefile-Config.mk

#-------------------------------------------------------------------------------
# Display
#-------------------------------------------------------------------------------

PROMPT              := "    ["$(COLOR_GREEN)" XEOS "$(COLOR_NONE)"]> ["$(COLOR_GREEN)" SRC  "$(COLOR_NONE)"]> ["$(COLOR_GREEN)" CORE "$(COLOR_NONE)"]> ["$(COLOR_GREEN)" KERN "$(COLOR_NONE)"]> *** "

#-------------------------------------------------------------------------------
# Paths
#-------------------------------------------------------------------------------

DIR_SRC_HAL             := $(PATH_SRC_CORE_KERNEL)hal/
DIR_SRC_HAL_CPU         := $(DIR_SRC_HAL)cpu/
DIR_SRC_HAL_IO          := $(DIR_SRC_HAL)io/
DIR_SRC_HAL_RTC         := $(DIR_SRC_HAL)rtc/
DIR_SRC_HAL_CMOS        := $(DIR_SRC_HAL)cmos/
DIR_SRC_HAL_IDT         := $(DIR_SRC_HAL)idt/
DIR_SRC_HAL_NMI         := $(DIR_SRC_HAL)nmi/
DIR_SRC_HAL_GDT         := $(DIR_SRC_HAL)gdt/
DIR_SRC_HAL_PIC         := $(DIR_SRC_HAL)pic/
DIR_SRC_HAL_PIT         := $(DIR_SRC_HAL)pit/
DIR_SRC_HAL_PS2         := $(DIR_SRC_HAL)ps2/
DIR_SRC_HAL_KEYBOARD    := $(DIR_SRC_HAL)keyboard/
DIR_SRC_ASM_RT          := $(PATH_SRC_CORE_KERNEL)asm/rt/
DIR_SRC_ISR             := $(PATH_SRC_CORE_KERNEL)isr/
DIR_SRC_IRQ             := $(PATH_SRC_CORE_KERNEL)irq/
DIR_SRC_SYSTEM          := $(PATH_SRC_CORE_KERNEL)system/
DIR_SRC_SYSCALL         := $(PATH_SRC_CORE_KERNEL)syscall/
DIR_SRC_VIDEO           := $(PATH_SRC_CORE_KERNEL)video/
DIR_SRC_INFO            := $(PATH_SRC_CORE_KERNEL)info/
DIR_SRC_VM              := $(PATH_SRC_CORE_KERNEL)vm/
DIR_SRC_PROC            := $(PATH_SRC_CORE_KERNEL)proc/
DIR_SRC_MEM             := $(PATH_SRC_CORE_KERNEL)mem/
DIR_SRC_INC             := $(PATH_SRC_CORE_KERNEL)include/

#-------------------------------------------------------------------------------
# Search paths
#-------------------------------------------------------------------------------

# Define the search paths for source files
vpath %$(EXT_ASM_32)    $(PATH_SRC_CORE_KERNEL)
vpath %$(EXT_ASM_64)    $(PATH_SRC_CORE_KERNEL)
vpath %$(EXT_ASM_32)    $(DIR_SRC_ASM_RT)
vpath %$(EXT_ASM_64)    $(DIR_SRC_ASM_RT)
vpath %$(EXT_C)         $(PATH_SRC_CORE_KERNEL)
vpath %$(EXT_C)         $(DIR_SRC_HAL)
vpath %$(EXT_C)         $(DIR_SRC_HAL_IO)
vpath %$(EXT_C)         $(DIR_SRC_HAL_RTC)
vpath %$(EXT_C)         $(DIR_SRC_HAL_CMOS)
vpath %$(EXT_C)         $(DIR_SRC_HAL_CPU)
vpath %$(EXT_C)         $(DIR_SRC_HAL_IDT)
vpath %$(EXT_C)         $(DIR_SRC_HAL_NMI)
vpath %$(EXT_C)         $(DIR_SRC_HAL_GDT)
vpath %$(EXT_C)         $(DIR_SRC_HAL_PIC)
vpath %$(EXT_C)         $(DIR_SRC_HAL_PIT)
vpath %$(EXT_C)         $(DIR_SRC_HAL_PS2)
vpath %$(EXT_C)         $(DIR_SRC_HAL_KEYBOARD)
vpath %$(EXT_C)         $(DIR_SRC_ISR)
vpath %$(EXT_C)         $(DIR_SRC_IRQ)
vpath %$(EXT_C)         $(DIR_SRC_SYSTEM)
vpath %$(EXT_C)         $(DIR_SRC_SYSCALL)
vpath %$(EXT_C)         $(DIR_SRC_VIDEO)
vpath %$(EXT_C)         $(DIR_SRC_INFO)
vpath %$(EXT_C)         $(DIR_SRC_VM)
vpath %$(EXT_C)         $(DIR_SRC_PROC)
vpath %$(EXT_C)         $(DIR_SRC_MEM)
vpath %$(EXT_H)         $(DIR_SRC_INC)

#-------------------------------------------------------------------------------
# File suffixes
#-------------------------------------------------------------------------------

# Adds the suffixes used in this file
.SUFFIXES:  $(EXT_ASM_32)   \
            $(EXT_ASM_64)   \
            $(EXT_C)        \
            $(EXT_H)        \
            $(EXT_OBJ)      \
            $(EXT_BIN)

#-------------------------------------------------------------------------------
# Files
#-------------------------------------------------------------------------------

_FILES_ASM_OBJ_BUILD            = $(call XEOS_FUNC_S_OBJ,$(PATH_BUILD_32_CORE_OBJ_KERNEL),$(PATH_SRC_CORE_KERNEL))
_FILES_ASM_OBJ_BUILD_RT         = $(call XEOS_FUNC_S_OBJ,$(PATH_BUILD_32_CORE_OBJ_KERNEL),$(DIR_SRC_ASM_RT))

_FILES_C_OBJ_BUILD              = $(call XEOS_FUNC_C_OBJ,$(PATH_BUILD_32_CORE_OBJ_KERNEL),$(PATH_SRC_CORE_KERNEL))
_FILES_C_OBJ_BUILD_HAL          = $(call XEOS_FUNC_C_OBJ,$(PATH_BUILD_32_CORE_OBJ_KERNEL),$(DIR_SRC_HAL))
_FILES_C_OBJ_BUILD_HAL_CPU      = $(call XEOS_FUNC_C_OBJ,$(PATH_BUILD_32_CORE_OBJ_KERNEL),$(DIR_SRC_HAL_CPU))
_FILES_C_OBJ_BUILD_HAL_IO       = $(call XEOS_FUNC_C_OBJ,$(PATH_BUILD_32_CORE_OBJ_KERNEL),$(DIR_SRC_HAL_IO))
_FILES_C_OBJ_BUILD_HAL_RTC      = $(call XEOS_FUNC_C_OBJ,$(PATH_BUILD_32_CORE_OBJ_KERNEL),$(DIR_SRC_HAL_RTC))
_FILES_C_OBJ_BUILD_HAL_CMOS     = $(call XEOS_FUNC_C_OBJ,$(PATH_BUILD_32_CORE_OBJ_KERNEL),$(DIR_SRC_HAL_CMOS))
_FILES_C_OBJ_BUILD_HAL_IDT      = $(call XEOS_FUNC_C_OBJ,$(PATH_BUILD_32_CORE_OBJ_KERNEL),$(DIR_SRC_HAL_IDT))
_FILES_C_OBJ_BUILD_HAL_NMI      = $(call XEOS_FUNC_C_OBJ,$(PATH_BUILD_32_CORE_OBJ_KERNEL),$(DIR_SRC_HAL_NMI))
_FILES_C_OBJ_BUILD_HAL_GDT      = $(call XEOS_FUNC_C_OBJ,$(PATH_BUILD_32_CORE_OBJ_KERNEL),$(DIR_SRC_HAL_GDT))
_FILES_C_OBJ_BUILD_HAL_PIC      = $(call XEOS_FUNC_C_OBJ,$(PATH_BUILD_32_CORE_OBJ_KERNEL),$(DIR_SRC_HAL_PIC))
_FILES_C_OBJ_BUILD_HAL_PIT      = $(call XEOS_FUNC_C_OBJ,$(PATH_BUILD_32_CORE_OBJ_KERNEL),$(DIR_SRC_HAL_PIT))
_FILES_C_OBJ_BUILD_HAL_PS2      = $(call XEOS_FUNC_C_OBJ,$(PATH_BUILD_32_CORE_OBJ_KERNEL),$(DIR_SRC_HAL_PS2))
_FILES_C_OBJ_BUILD_HAL_KEYBOARD = $(call XEOS_FUNC_C_OBJ,$(PATH_BUILD_32_CORE_OBJ_KERNEL),$(DIR_SRC_HAL_KEYBOARD))
_FILES_C_OBJ_BUILD_ISR          = $(call XEOS_FUNC_C_OBJ,$(PATH_BUILD_32_CORE_OBJ_KERNEL),$(DIR_SRC_ISR))
_FILES_C_OBJ_BUILD_IRQ          = $(call XEOS_FUNC_C_OBJ,$(PATH_BUILD_32_CORE_OBJ_KERNEL),$(DIR_SRC_IRQ))
_FILES_C_OBJ_BUILD_SYSTEM       = $(call XEOS_FUNC_C_OBJ,$(PATH_BUILD_32_CORE_OBJ_KERNEL),$(DIR_SRC_SYSTEM))
_FILES_C_OBJ_BUILD_SYSCALL      = $(call XEOS_FUNC_C_OBJ,$(PATH_BUILD_32_CORE_OBJ_KERNEL),$(DIR_SRC_SYSCALL))
_FILES_C_OBJ_BUILD_VIDEO        = $(call XEOS_FUNC_C_OBJ,$(PATH_BUILD_32_CORE_OBJ_KERNEL),$(DIR_SRC_VIDEO))
_FILES_C_OBJ_BUILD_INFO         = $(call XEOS_FUNC_C_OBJ,$(PATH_BUILD_32_CORE_OBJ_KERNEL),$(DIR_SRC_INFO))
_FILES_C_OBJ_BUILD_VM           = $(call XEOS_FUNC_C_OBJ,$(PATH_BUILD_32_CORE_OBJ_KERNEL),$(DIR_SRC_VM))
_FILES_C_OBJ_BUILD_PROC         = $(call XEOS_FUNC_C_OBJ,$(PATH_BUILD_32_CORE_OBJ_KERNEL),$(DIR_SRC_PROC))
_FILES_C_OBJ_BUILD_MEM          = $(call XEOS_FUNC_C_OBJ,$(PATH_BUILD_32_CORE_OBJ_KERNEL),$(DIR_SRC_MEM))

#-------------------------------------------------------------------------------
# Built-in targets
#-------------------------------------------------------------------------------

# Declaration for phony targets, to avoid problems with local files
.PHONY: all     \
        clean

#-------------------------------------------------------------------------------
# Phony targets
#-------------------------------------------------------------------------------

# Build the full project
all:    $(_FILES_ASM_OBJ_BUILD)             \
        $(_FILES_ASM_OBJ_BUILD_RT)          \
        $(_FILES_C_OBJ_BUILD)               \
        $(_FILES_C_OBJ_BUILD_HAL)           \
        $(_FILES_C_OBJ_BUILD_HAL_CPU)       \
        $(_FILES_C_OBJ_BUILD_HAL_IO)        \
        $(_FILES_C_OBJ_BUILD_HAL_RTC)       \
        $(_FILES_C_OBJ_BUILD_HAL_CMOS)      \
        $(_FILES_C_OBJ_BUILD_HAL_IDT)       \
        $(_FILES_C_OBJ_BUILD_HAL_NMI)       \
        $(_FILES_C_OBJ_BUILD_HAL_GDT)       \
        $(_FILES_C_OBJ_BUILD_HAL_PIC)       \
        $(_FILES_C_OBJ_BUILD_HAL_PIT)       \
        $(_FILES_C_OBJ_BUILD_HAL_PS2)       \
        $(_FILES_C_OBJ_BUILD_HAL_KEYBOARD)  \
        $(_FILES_C_OBJ_BUILD_ISR)           \
        $(_FILES_C_OBJ_BUILD_IRQ)           \
        $(_FILES_C_OBJ_BUILD_SYSTEM)        \
        $(_FILES_C_OBJ_BUILD_SYSCALL)       \
        $(_FILES_C_OBJ_BUILD_VIDEO)         \
        $(_FILES_C_OBJ_BUILD_INFO)          \
        $(_FILES_C_OBJ_BUILD_VM)            \
        $(_FILES_C_OBJ_BUILD_PROC)          \
        $(_FILES_C_OBJ_BUILD_MEM)
	
	@:

# Cleans the build files
clean:
	
	@$(PRINT) $(PROMPT)"Cleaning all build files"
	@$(RM) $(ARGS_RM) $(PATH_BUILD_32_CORE_OBJ_KERNEL)*
	@$(RM) $(ARGS_RM) $(PATH_BUILD_64_CORE_OBJ_KERNEL)*
