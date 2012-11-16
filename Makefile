#-------------------------------------------------------------------------------
# Copyright (c) 2010-2012, Jean-David Gadina <macmade@eosgarden.com>
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

DIR_SRC_HAL         := $(PATH_SRC_CORE_KERNEL)hal/
DIR_SRC_HAL_CPU     := $(DIR_SRC_HAL)cpu/
DIR_SRC_HAL_IO      := $(DIR_SRC_HAL)io/
DIR_SRC_HAL_MEM     := $(DIR_SRC_HAL)mem/
DIR_SRC_HAL_IDT     := $(DIR_SRC_HAL)idt/
DIR_SRC_HAL_GDT     := $(DIR_SRC_HAL)gdt/
DIR_SRC_HAL_PIC     := $(DIR_SRC_HAL)pic/
DIR_SRC_HAL_PIT     := $(DIR_SRC_HAL)pit/
DIR_SRC_HAL_SMBIOS  := $(DIR_SRC_HAL)smbios/
DIR_SRC_ASM_RT      := $(PATH_SRC_CORE_KERNEL)asm/rt/
DIR_SRC_ISR         := $(PATH_SRC_CORE_KERNEL)isr/
DIR_SRC_SYSTEM      := $(PATH_SRC_CORE_KERNEL)system/
DIR_SRC_VIDEO       := $(PATH_SRC_CORE_KERNEL)video/
DIR_SRC_INC         := $(PATH_SRC_CORE_KERNEL)include/

#-------------------------------------------------------------------------------
# Software arguments
#-------------------------------------------------------------------------------

ARGS_AS_32          := -f $(TARGET_ABI) -I $(PATH_SRC_CORE_INC)
ARGS_AS_64          := -f $(TARGET_ABI)64 -I $(PATH_SRC_CORE_INC)
ARGS_CC_32          := -iquote $(DIR_SRC_INC) $(ARGS_CC_32)
ARGS_CC_64          := -iquote $(DIR_SRC_INC) $(ARGS_CC_64)

#-------------------------------------------------------------------------------
# File extensions
#-------------------------------------------------------------------------------

EXT_ASM_32           = 32.s
EXT_ASM_64           = 64.s

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
vpath %$(EXT_C)         $(DIR_SRC_HAL_MEM)
vpath %$(EXT_C)         $(DIR_SRC_HAL_CPU)
vpath %$(EXT_C)         $(DIR_SRC_HAL_IDT)
vpath %$(EXT_C)         $(DIR_SRC_HAL_GDT)
vpath %$(EXT_C)         $(DIR_SRC_HAL_PIC)
vpath %$(EXT_C)         $(DIR_SRC_HAL_PIT)
vpath %$(EXT_C)         $(DIR_SRC_HAL_SMBIOS)
vpath %$(EXT_C)         $(DIR_SRC_ISR)
vpath %$(EXT_C)         $(DIR_SRC_SYSTEM)
vpath %$(EXT_C)         $(DIR_SRC_VIDEO)
vpath %$(EXT_H)         $(DIR_SRC_INC)

#-------------------------------------------------------------------------------
# File suffixes
#-------------------------------------------------------------------------------

# Adds the suffixes used in this file
.SUFFIXES: $(EXT_ASM_32) $(EXT_ASM_64) $(EXT_C) $(EXT_H) $(EXT_OBJ) $(EXT_BIN)

#-------------------------------------------------------------------------------
# Macros
#-------------------------------------------------------------------------------

# Gets every code file in the source directory
_FILES_ASM_32                   = $(foreach dir,$(PATH_SRC_CORE_KERNEL),$(wildcard $(PATH_SRC_CORE_KERNEL)*$(EXT_ASM_32)))
_FILES_ASM_64                   = $(foreach dir,$(PATH_SRC_CORE_KERNEL),$(wildcard $(PATH_SRC_CORE_KERNEL)*$(EXT_ASM_64)))
_FILES_ASM_32_RT                = $(foreach dir,$(DIR_SRC_ASM_RT),$(wildcard $(DIR_SRC_ASM_RT)*$(EXT_ASM_32)))
_FILES_ASM_64_RT                = $(foreach dir,$(DIR_SRC_ASM_RT),$(wildcard $(DIR_SRC_ASM_RT)*$(EXT_ASM_64)))
_FILES_C                        = $(foreach dir,$(PATH_SRC_CORE_KERNEL),$(wildcard $(PATH_SRC_CORE_KERNEL)*$(EXT_C)))
_FILES_C_HAL                    = $(foreach dir,$(DIR_SRC_HAL),$(wildcard $(DIR_SRC_HAL)*$(EXT_C)))
_FILES_C_HAL_IO                 = $(foreach dir,$(DIR_SRC_HAL_IO),$(wildcard $(DIR_SRC_HAL_IO)*$(EXT_C)))
_FILES_C_HAL_MEM                = $(foreach dir,$(DIR_SRC_HAL_MEM),$(wildcard $(DIR_SRC_HAL_MEM)*$(EXT_C)))
_FILES_C_HAL_CPU                = $(foreach dir,$(DIR_SRC_HAL_CPU),$(wildcard $(DIR_SRC_HAL_CPU)*$(EXT_C)))
_FILES_C_HAL_IDT                = $(foreach dir,$(DIR_SRC_HAL_IDT),$(wildcard $(DIR_SRC_HAL_IDT)*$(EXT_C)))
_FILES_C_HAL_GDT                = $(foreach dir,$(DIR_SRC_HAL_GDT),$(wildcard $(DIR_SRC_HAL_GDT)*$(EXT_C)))
_FILES_C_HAL_PIC                = $(foreach dir,$(DIR_SRC_HAL_PIC),$(wildcard $(DIR_SRC_HAL_PIC)*$(EXT_C)))
_FILES_C_HAL_PIT                = $(foreach dir,$(DIR_SRC_HAL_PIT),$(wildcard $(DIR_SRC_HAL_PIT)*$(EXT_C)))
_FILES_C_HAL_SMBIOS             = $(foreach dir,$(DIR_SRC_HAL_SMBIOS),$(wildcard $(DIR_SRC_HAL_SMBIOS)*$(EXT_C)))
_FILES_C_ISR                    = $(foreach dir,$(DIR_SRC_ISR),$(wildcard $(DIR_SRC_ISR)*$(EXT_C)))
_FILES_C_SYSTEM                 = $(foreach dir,$(DIR_SRC_SYSTEM),$(wildcard $(DIR_SRC_SYSTEM)*$(EXT_C)))
_FILES_C_VIDEO                  = $(foreach dir,$(DIR_SRC_VIDEO),$(wildcard $(DIR_SRC_VIDEO)*$(EXT_C)))

# Gets only the file name of the code files
_FILES_ASM_REL_32               = $(notdir $(_FILES_ASM_32))
_FILES_ASM_REL_64               = $(notdir $(_FILES_ASM_64))
_FILES_ASM_REL_32_RT            = $(notdir $(_FILES_ASM_32_RT))
_FILES_ASM_REL_64_RT            = $(notdir $(_FILES_ASM_64_RT))
_FILES_C_REL                    = $(notdir $(_FILES_C))
_FILES_C_REL_HAL                = $(notdir $(_FILES_C_HAL))
_FILES_C_REL_HAL_CPU            = $(notdir $(_FILES_C_HAL_CPU))
_FILES_C_REL_HAL_IO             = $(notdir $(_FILES_C_HAL_IO))
_FILES_C_REL_HAL_MEM            = $(notdir $(_FILES_C_HAL_MEM))
_FILES_C_REL_HAL_IDT            = $(notdir $(_FILES_C_HAL_IDT))
_FILES_C_REL_HAL_GDT            = $(notdir $(_FILES_C_HAL_GDT))
_FILES_C_REL_HAL_PIC            = $(notdir $(_FILES_C_HAL_PIC))
_FILES_C_REL_HAL_PIT            = $(notdir $(_FILES_C_HAL_PIT))
_FILES_C_REL_HAL_SMBIOS         = $(notdir $(_FILES_C_HAL_SMBIOS))
_FILES_C_REL_ISR                = $(notdir $(_FILES_C_ISR))
_FILES_C_REL_SYSTEM             = $(notdir $(_FILES_C_SYSTEM))
_FILES_C_REL_VIDEO              = $(notdir $(_FILES_C_VIDEO))

# Replace the code extension by the object one
_FILES_ASM_OBJ_32               = $(subst $(EXT_ASM_32),$(EXT_ASM_32)$(EXT_OBJ),$(_FILES_ASM_REL_32))
_FILES_ASM_OBJ_64               = $(subst $(EXT_ASM_64),$(EXT_ASM_64)$(EXT_OBJ),$(_FILES_ASM_REL_64))
_FILES_ASM_OBJ_32_RT            = $(subst $(EXT_ASM_32),$(EXT_ASM_32)$(EXT_OBJ),$(_FILES_ASM_REL_32_RT))
_FILES_ASM_OBJ_64_RT            = $(subst $(EXT_ASM_64),$(EXT_ASM_64)$(EXT_OBJ),$(_FILES_ASM_REL_64_RT))
_FILES_C_OBJ                    = $(subst $(EXT_C),$(EXT_C)$(EXT_OBJ),$(_FILES_C_REL))
_FILES_C_OBJ_HAL                = $(subst $(EXT_C),$(EXT_C)$(EXT_OBJ),$(_FILES_C_REL_HAL))
_FILES_C_OBJ_HAL_CPU            = $(subst $(EXT_C),$(EXT_C)$(EXT_OBJ),$(_FILES_C_REL_HAL_CPU))
_FILES_C_OBJ_HAL_IO             = $(subst $(EXT_C),$(EXT_C)$(EXT_OBJ),$(_FILES_C_REL_HAL_IO))
_FILES_C_OBJ_HAL_MEM            = $(subst $(EXT_C),$(EXT_C)$(EXT_OBJ),$(_FILES_C_REL_HAL_MEM))
_FILES_C_OBJ_HAL_IDT            = $(subst $(EXT_C),$(EXT_C)$(EXT_OBJ),$(_FILES_C_REL_HAL_IDT))
_FILES_C_OBJ_HAL_GDT            = $(subst $(EXT_C),$(EXT_C)$(EXT_OBJ),$(_FILES_C_REL_HAL_GDT))
_FILES_C_OBJ_HAL_PIC            = $(subst $(EXT_C),$(EXT_C)$(EXT_OBJ),$(_FILES_C_REL_HAL_PIC))
_FILES_C_OBJ_HAL_PIT            = $(subst $(EXT_C),$(EXT_C)$(EXT_OBJ),$(_FILES_C_REL_HAL_PIT))
_FILES_C_OBJ_HAL_SMBIOS         = $(subst $(EXT_C),$(EXT_C)$(EXT_OBJ),$(_FILES_C_REL_HAL_SMBIOS))
_FILES_C_OBJ_ISR                = $(subst $(EXT_C),$(EXT_C)$(EXT_OBJ),$(_FILES_C_REL_ISR))
_FILES_C_OBJ_SYSTEM             = $(subst $(EXT_C),$(EXT_C)$(EXT_OBJ),$(_FILES_C_REL_SYSTEM))
_FILES_C_OBJ_VIDEO              = $(subst $(EXT_C),$(EXT_C)$(EXT_OBJ),$(_FILES_C_REL_VIDEO))

# Prefix all binary files with the build directory
_FILES_ASM_OBJ_BUILD_32         = $(addprefix $(PATH_BUILD_32_CORE_OBJ_KERNEL),$(_FILES_ASM_OBJ_32))
_FILES_ASM_OBJ_BUILD_64         = $(addprefix $(PATH_BUILD_64_CORE_OBJ_KERNEL),$(_FILES_ASM_OBJ_64))
_FILES_ASM_OBJ_BUILD_32_RT      = $(addprefix $(PATH_BUILD_32_CORE_OBJ_KERNEL),$(_FILES_ASM_OBJ_32_RT))
_FILES_ASM_OBJ_BUILD_64_RT      = $(addprefix $(PATH_BUILD_64_CORE_OBJ_KERNEL),$(_FILES_ASM_OBJ_64_RT))
_FILES_C_OBJ_BUILD              = $(addprefix $(PATH_BUILD_32_CORE_OBJ_KERNEL),$(_FILES_C_OBJ))
_FILES_C_OBJ_BUILD_HAL          = $(addprefix $(PATH_BUILD_32_CORE_OBJ_KERNEL),$(_FILES_C_OBJ_HAL))
_FILES_C_OBJ_BUILD_HAL_CPU      = $(addprefix $(PATH_BUILD_32_CORE_OBJ_KERNEL),$(_FILES_C_OBJ_HAL_CPU))
_FILES_C_OBJ_BUILD_HAL_IO       = $(addprefix $(PATH_BUILD_32_CORE_OBJ_KERNEL),$(_FILES_C_OBJ_HAL_IO))
_FILES_C_OBJ_BUILD_HAL_MEM      = $(addprefix $(PATH_BUILD_32_CORE_OBJ_KERNEL),$(_FILES_C_OBJ_HAL_MEM))
_FILES_C_OBJ_BUILD_HAL_IDT      = $(addprefix $(PATH_BUILD_32_CORE_OBJ_KERNEL),$(_FILES_C_OBJ_HAL_IDT))
_FILES_C_OBJ_BUILD_HAL_GDT      = $(addprefix $(PATH_BUILD_32_CORE_OBJ_KERNEL),$(_FILES_C_OBJ_HAL_GDT))
_FILES_C_OBJ_BUILD_HAL_PIC      = $(addprefix $(PATH_BUILD_32_CORE_OBJ_KERNEL),$(_FILES_C_OBJ_HAL_PIC))
_FILES_C_OBJ_BUILD_HAL_PIT      = $(addprefix $(PATH_BUILD_32_CORE_OBJ_KERNEL),$(_FILES_C_OBJ_HAL_PIT))
_FILES_C_OBJ_BUILD_HAL_SMBIOS   = $(addprefix $(PATH_BUILD_32_CORE_OBJ_KERNEL),$(_FILES_C_OBJ_HAL_SMBIOS))
_FILES_C_OBJ_BUILD_ISR          = $(addprefix $(PATH_BUILD_32_CORE_OBJ_KERNEL),$(_FILES_C_OBJ_ISR))
_FILES_C_OBJ_BUILD_SYSTEM       = $(addprefix $(PATH_BUILD_32_CORE_OBJ_KERNEL),$(_FILES_C_OBJ_SYSTEM))
_FILES_C_OBJ_BUILD_VIDEO        = $(addprefix $(PATH_BUILD_32_CORE_OBJ_KERNEL),$(_FILES_C_OBJ_VIDEO))

#-------------------------------------------------------------------------------
# Built-in targets
#-------------------------------------------------------------------------------

# Declaration for phony targets, to avoid problems with local files
.PHONY: all clean

# Declaration for precious targets, to avoid cleaning of intermediate files
.PRECIOUS: $(PATH_BUILD_64_CORE_OBJ_KERNEL)%$(EXT_C)$(EXT_OBJ)

#-------------------------------------------------------------------------------
# Phony targets
#-------------------------------------------------------------------------------

# Build the full project
all: $(_FILES_ASM_OBJ_BUILD_32) $(_FILES_ASM_OBJ_BUILD_64) $(_FILES_ASM_OBJ_BUILD_32_RT) $(_FILES_ASM_OBJ_BUILD_64_RT) $(_FILES_C_OBJ_BUILD) $(_FILES_C_OBJ_BUILD_HAL) $(_FILES_C_OBJ_BUILD_HAL_CPU) $(_FILES_C_OBJ_BUILD_HAL_IO) $(_FILES_C_OBJ_BUILD_HAL_MEM) $(_FILES_C_OBJ_BUILD_HAL_IDT) $(_FILES_C_OBJ_BUILD_HAL_GDT) $(_FILES_C_OBJ_BUILD_HAL_PIC) $(_FILES_C_OBJ_BUILD_HAL_PIT) $(_FILES_C_OBJ_BUILD_HAL_SMBIOS) $(_FILES_C_OBJ_BUILD_ISR) $(_FILES_C_OBJ_BUILD_SYSTEM) $(_FILES_C_OBJ_BUILD_VIDEO)
	
	@:

# Cleans the build files
clean:
	
	@$(PRINT) $(PROMPT)"Cleaning all build files"
	@$(RM) $(ARGS_RM) $(PATH_BUILD_32_CORE_OBJ_KERNEL)*
	@$(RM) $(ARGS_RM) $(PATH_BUILD_64_CORE_OBJ_KERNEL)*
	
# Compiles an assembly file (32 bits)
$(PATH_BUILD_32_CORE_OBJ_KERNEL)%$(EXT_ASM_32)$(EXT_OBJ): %$(EXT_ASM_32)
	
	@$(PRINT) $(PROMPT)"Compiling assembly file [ 32 bits ]: "$(COLOR_YELLOW)"$(notdir $< )"$(COLOR_NONE)" -> "$(COLOR_GRAY)"$(notdir $@)"$(COLOR_NONE)
	@$(AS_32) $(ARGS_AS_32) -o $(PATH_BUILD_32_CORE_OBJ_KERNEL)$(@F) $(abspath $<)
	
# Compiles an assembly file (64 bits)
$(PATH_BUILD_64_CORE_OBJ_KERNEL)%$(EXT_ASM_64)$(EXT_OBJ): %$(EXT_ASM_64)
	
	@$(PRINT) $(PROMPT)"Compiling assembly file [ 64 bits ]: "$(COLOR_YELLOW)"$(notdir $< )"$(COLOR_NONE)" -> "$(COLOR_GRAY)"$(notdir $@)"$(COLOR_NONE)
	@$(AS_64) $(ARGS_AS_64) -o $(PATH_BUILD_64_CORE_OBJ_KERNEL)$(@F) $(abspath $<)
	
# Compiles a C file (64 bits)
$(PATH_BUILD_64_CORE_OBJ_KERNEL)%$(EXT_C)$(EXT_OBJ): %$(EXT_C)
	
	@$(PRINT) $(PROMPT)"Compiling C file [ 64 bits ]: "$(COLOR_YELLOW)"$(notdir $< )"$(COLOR_NONE)" -> "$(COLOR_GRAY)"$(notdir $@)"$(COLOR_NONE)
	@$(CC_64) $(ARGS_CC_64) -o $(PATH_BUILD_64_CORE_OBJ_KERNEL)$(@F) -c $(abspath $<)

# Targets with second expansion
.SECONDEXPANSION:
    
# Compiles a C file (32 bits)
$(PATH_BUILD_32_CORE_OBJ_KERNEL)%$(EXT_C)$(EXT_OBJ): %$(EXT_C) $$(subst $(PATH_BUILD_32_CORE_OBJ_KERNEL),$(PATH_BUILD_64_CORE_OBJ_KERNEL),$$@)
	
	@$(PRINT) $(PROMPT)"Compiling C file [ 32 bits ]: "$(COLOR_YELLOW)"$(notdir $< )"$(COLOR_NONE)" -> "$(COLOR_GRAY)"$(notdir $@)"$(COLOR_NONE)
	@$(CC_32) $(ARGS_CC_32) -o $(PATH_BUILD_32_CORE_OBJ_KERNEL)$(@F) -c $(abspath $<)
