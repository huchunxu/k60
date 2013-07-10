# Hey Emacs, this is a -*- makefile -*-
#
# WinARM template makefile 
# by Martin Thomas, Kaiserslautern, Germany 
# <eversmith@heizung-thomas.de>
#
# based on the WinAVR makefile written by Eric B. Weddington, J��g Wunsch, et al.
# Released to the Public Domain
# Please read the make user manual!
#
#
# On command line:
#
# make all = Make software.
#
# make clean = Clean out built project files.
#
# (TODO: make filename.s = Just compile filename.c into the assembler code only)
#
# To rebuild project do "make clean" then "make all".
#
# Changelog:
# - 17. Feb. 2005  - added thumb-interwork support (mth)
# - 28. Apr. 2005  - added C++ support (mth)
# - 29. Arp. 2005  - changed handling for lst-Filename (mth)
# -  1. Nov. 2005  - exception-vector placement options (mth)
# - 15. Nov. 2005  - added library-search-path (EXTRA_LIB...) (mth)
# -  2. Dec. 2005  - fixed ihex and binary file extensions (mth)
# - 22. Feb. 2006  - added AT91LIBNOWARN setting (mth)
# - 19. Apr. 2006  - option FLASH_TOOL (default lpc21isp); variable IMGEXT (mth)
# - 23. Jun. 2006  - option USE_THUMB_MODE -> THUMB/THUMB_IW
# -  3. Aug. 2006  - added -ffunction-sections -fdata-sections to CFLAGS
#                    and --gc-sections to LDFLAGS. Only available for gcc 4 (mth)
# -  4. Aug. 2006  - pass SUBMDL-define to frontend (mth)
# - 11. Nov. 2006  - FLASH_TOOL-config, TCHAIN-config (mth)
# - 28. Mar. 2007  - remove .dep-Directory with rm -r -f and force "no error"
# - 24. Aprl 2007  - added "both" option for format (.bin and .hex)

# Toolchain prefix (i.e arm-elf -> arm-elf-gcc.exe)

# -  2. Oct. 2008  - Changed for example project of FatFs moddule (chan)
# -  1, July. 2011 - Change  for bootloader for LPC2479
# -  13,March. 2012 -Change for HUST-RENESAS lab's Freecale smartcar
#    match

# MCU name and submodel
MCU      = cortex-m4
THUMB_MODE = YES
SUBMDL   = K60


DIR_EXE	= exe
DIR_OBJS_PRE = objs

DIR_SRC = arch/arm/k60/analog \
          arch/arm/k60/clock \
          arch/arm/k60/comi \
          arch/arm/k60/core \
          arch/arm/k60/hmi \
          arch/arm/k60/memory \
          arch/arm/k60/startup \
          arch/arm/k60/system \
          arch/arm/k60/timer \
          modules/comm \
          modules/device \
          modules/sensor \
          modules/signal \
          common common/ntshell_cmd \
          library/ntshell \
          library/fatfs

# Target file name (without extension).
DIR_TARGET = app/laser_car
TARGET_NAME = main
TARGET := $(addprefix $(DIR_EXE)/, $(TARGET_NAME))

# List C source files here. (C dependencies are automatically generated.)
# use file-extension c for "c-only"-files
SRC := $(foreach dir, $(DIR_SRC), $(wildcard $(dir)/*.c))
SRC := $(SRC) $(wildcard $(DIR_TARGET)/*.c)

# List Assembler source files here.
# Make them always end in a capital .S.  Files ending in a lowercase .s
# will not be considered source files but generated files (assembler
# output from the compiler), and will be deleted upon "make clean"!
# Even though the DOS/Win* filesystem matches both .s and .S the same,
# it will preserve the spelling of the filenames, and gcc itself does
# care about how the name is spelled on its command-line.
ASRC := $(foreach dir, $(DIR_SRC), $(wildcard $(dir)/*.S))
ASRC := $(ASRC) $(wildcard $(DIR_TARGET)/*.S)

# Define all object files.
COBJ := $(addprefix $(DIR_OBJS_PRE)/, $(SRC:.c=.o)) 
AOBJ := $(addprefix $(DIR_OBJS_PRE)/, $(ASRC:.S=.o))

DIR_OBJS := $(foreach dir, $(DIR_SRC), $(addprefix $(DIR_OBJS_PRE)/, $(dir)))
DIR_OBJS := $(DIR_OBJS) $(addprefix $(DIR_OBJS_PRE)/, $(DIR_TARGET))

DIRS := $(DIR_OBJS) $(DIR_EXE)

## Output format. (can be ihex or binary or both)
## (binary i.e. for openocd and SAM-BA, hex i.e. for lpc21isp and uVision)
FORMAT = ihex

# Optimization level, can be [0, 1, 2, 3, s]. 
# 0 = turn off optimization. s = optimize for size.
# (Note: 3 is not always the best optimization level. See avr-libc FAQ.)
OPT = -O0

# Debugging format.
# Native formats for AVR-GCC's -g are stabs [default], or dwarf-2.
# AVR (extended) COFF requires stabs, plus an avr-objcopy run.
#DEBUG = stabs
DEBUG = dwarf-2

# List any extra directories to look for include files here.
#     Each directory must be seperated by a space.
EXTRAINCDIRS = include $(DIR_SRC) $(DIR_TARGET) library/CMSIS_V3P00/CMSIS/Include

# List any extra directories to look for library files here.
#     Each directory must be seperated by a space.
EXTRA_LIBDIRS = library/CMSIS_V3P00/CMSIS/DSP_Lib

# Compiler flag to set the C Standard level.
# c89   - "ANSI" C
# gnu89 - c89 plus GCC extensions
# c99   - ISO C99 standard (not yet fully implemented)
# gnu99 - c99 plus GCC extensions
CSTANDARD = -std=gnu99

# Place -D or -U options for C here
RUN_MODE=ROM_RUN
CDEFS =  -D$(RUN_MODE)

# Place -D or -U options for ASM here
ADEFS =  -D$(RUN_MODE)

# Compiler flags.

ifeq ($(THUMB_MODE),YES)
THUMB    = -mthumb
THUMB_IW = 
else 
THUMB    = 
THUMB_IW = 
endif

#  -g*:          generate debugging information
#  -O*:          optimization level
#  -f...:        tuning, see GCC manual and avr-libc documentation
#  -Wall...:     warning level
#  -Wa,...:      tell GCC to pass this to the assembler.
#    -adhlns...: create assembler listing
#
# Flags for C and C++ (arm-elf-gcc/arm-elf-g++)
CFLAGS = -g$(DEBUG)
CFLAGS += $(CDEFS) $(CINCS)
CFLAGS += $(OPT)
CFLAGS += -Wall -Wcast-align -Wimplicit

CFLAGS += -Wpointer-arith -Wswitch
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -Wredundant-decls -Wreturn-type -Wshadow -Wunused
CFLAGS += $(patsubst %,-I%,$(EXTRAINCDIRS))

# flags only for C
CONLYFLAGS += -Wnested-externs 
CONLYFLAGS += $(CSTANDARD)

ifneq ($(AT91LIBNOWARN),yes)
#AT91-lib warnings with:
CFLAGS += -Wcast-qual
CONLYFLAGS += -Wstrict-prototypes
#CONLYFLAGS += -Wmissing-declarations
#CONLYFLAGS += -Wmissing-prototypes
endif

# flags only for C++ (arm-elf-g++)
# CPPFLAGS = -fno-rtti -fno-exceptions
CPPFLAGS = 

# Assembler flags.
#  -Wa,...:    tell GCC to pass this to the assembler.
#  -ahlns:     create listing
#  -g$(DEBUG): have the assembler create line number information
ASFLAGS = $(ADEFS) -Wa,-g$(DEBUG)


#Additional libraries.

# Extra libraries
#    Each library-name must be seperated by a space.
#    To add libxyz.a, libabc.a and libefsl.a: 
#    EXTRA_LIBS = xyz abc efsl
EXTRA_LIBS = cmsis

#Support for newlibc-lpc (file: libnewlibc-lpc.a)
#NEWLIBLPC = -lnewlib-lpc

MATH_LIB = -lm

# CPLUSPLUS_LIB = -lstdc++


# Linker flags.
#  -Wl,...:     tell GCC to pass this to linker.
#    -Map:      create map file
#    --cref:    add cross reference to  map file
LDFLAGS = -Wl,-Map=$(TARGET).map,--cref,--gc-sections
LDFLAGS += -lc
LDFLAGS += $(NEWLIBLPC) $(MATH_LIB)
LDFLAGS += -lc -lgcc 
LDFLAGS += $(CPLUSPLUS_LIB)
LDFLAGS += $(patsubst %,-L%,$(EXTRA_LIBDIRS))
LDFLAGS += $(patsubst %,-l%,$(EXTRA_LIBS))


# Set Linker-Script Depending On Selected Memory and Controller
LDFLAGS +=-T$(SUBMDL)_FLASH.ld


# Define programs and commands.
SHELL = sh
CC = arm-none-eabi-gcc
AR = arm-none-eabi-ar
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump
SIZE = arm-none-eabi-size
NM = arm-none-eabi-nm
REMOVE = rm -f
REMOVEDIR = rm -f -r
COPY = cp
MKDIR = mkdir


# Define Messages
# English
MSG_END = --------  end  --------
MSG_FLASH = Creating load file for Flash:
MSG_LST = Creating listing file
MSG_EXTENDED_LISTING = Creating Extended Listing:
MSG_SYMBOL_TABLE = Creating Symbol Table:
MSG_LINKING = Linking:
MSG_COMPILING = Compiling C:
MSG_ASSEMBLING = Assembling:
MSG_CLEANING = Cleaning project:
MSG_FORMATERROR = Can not handle output-format
MSG_LPC21_RESETREMINDER = You may have to bring the target in bootloader-mode now.



# Define all listing files.
LST = $(TARGET).lst $(ASRC:.S=.lst) $(SRC:.c=.lst)

# Compiler flags to generate dependency files.
### GENDEPFLAGS = -Wp,-M,-MP,-MT,$(*F).o,-MF,.dep/$(@F).d
GENDEPFLAGS = 

# Combine all necessary flags and optional flags.
# Add target processor to flags.
ALL_CFLAGS  = -mcpu=$(MCU) $(THUMB_IW) -I. $(CFLAGS) $(GENDEPFLAGS)
ALL_ASFLAGS = -mcpu=$(MCU) $(THUMB) -I. -x assembler-with-cpp $(ASFLAGS)


# Default target.
all: $(DIRS) version build size

# create object dirs
$(DIRS):
	$(MKDIR) -p  $@

ifeq ($(FORMAT),ihex)
build: elf hex lst sym
hex: $(TARGET).hex
IMGEXT=hex
else 
ifeq ($(FORMAT),binary)
build: elf bin lst sym
bin: $(TARGET).bin
IMGEXT=bin
else 
ifeq ($(FORMAT),both)
build: elf hex bin lst sym
hex: $(TARGET).hex
bin: $(TARGET).bin
else 
$(error "$(MSG_FORMATERROR) $(FORMAT)")
endif
endif
endif

elf: $(TARGET).elf
lst: $(TARGET).lst 
sym: $(TARGET).sym


# Display size of file.
ELFSIZE = $(SIZE) -A $(TARGET).elf

size:
	@if [ -f $(TARGET).elf ]; then $(ELFSIZE); fi

# Display compiler version information.
version : 
	@$(CC) --version

# Create final output file (.hex) from ELF output file.
%.hex: %.elf
	@echo
	@echo $(MSG_FLASH) $@
	$(OBJCOPY) -O ihex $< $@

# Create final output file (.bin) from ELF output file.
%.bin: %.elf
	@echo
	@echo $(MSG_FLASH) $@
	$(OBJCOPY) -O binary $< $@

# Create extended listing file from ELF output file.
# testing: option -C
%.lst: %.elf
	@echo
	@echo $(MSG_EXTENDED_LISTING) $@
	$(OBJDUMP) -h -S -C $< > $@


# Create a symbol table from ELF output file.
%.sym: %.elf
	@echo
	@echo $(MSG_SYMBOL_TABLE) $@
	$(NM) -n $< > $@


# Link: create ELF output file from object files.
.SECONDARY : $(TARGET).elf
.PRECIOUS : $(AOBJ) $(COBJ)
%.elf: $(AOBJ) $(COBJ)
	@echo
	@echo $(MSG_LINKING) $@
	$(CC) $(THUMB) $(ALL_CFLAGS) $(AOBJ) $(COBJ) --output $@ $(LDFLAGS)

# Compile: create object files from C source files. ARM/Thumb
$(COBJ) : $(DIR_OBJS_PRE)/%.o : %.c
	@echo
	@echo $(MSG_COMPILING) $<
	$(CC) -c $(THUMB) $(ALL_CFLAGS) $(CONLYFLAGS) $< -o $@ 


# Compile: create assembler files from C source files. ARM/Thumb
## does not work - TODO - hints welcome
##$(COBJ) : %.s : %.c
##	$(CC) $(THUMB) -S $(ALL_CFLAGS) $< -o $@


# Assemble: create object files from assembler source files. ARM/Thumb
$(AOBJ) : $(DIR_OBJS_PRE)/%.o : %.S
	@echo
	@echo $(MSG_ASSEMBLING) $<
	$(CC) -c $(THUMB) $(ALL_ASFLAGS) $< -o $@


# Target: clean project.
clean: clean_list


clean_list :
	@echo
	@echo $(MSG_CLEANING)
	$(REMOVE) $(TARGET).hex
	$(REMOVE) $(TARGET).bin
	$(REMOVE) $(TARGET).obj
	$(REMOVE) $(TARGET).elf
	$(REMOVE) $(TARGET).map
	$(REMOVE) $(TARGET).obj
	$(REMOVE) $(TARGET).a90
	$(REMOVE) $(TARGET).sym
	$(REMOVE) $(TARGET).lnk
	$(REMOVE) $(TARGET).lst
	$(REMOVE) $(COBJ)
	$(REMOVE) $(AOBJ)
	$(REMOVE) $(LST)
	$(REMOVE) $(SRC:.c=.s)
#	$(REMOVE) $(SRC:.c=.d)
	$(REMOVEDIR) $(DIRS)
#	$(REMOVE) $(SRCARM:.c=.d)
#	$(REMOVEDIR) .dep | exit 0


# Include the dependency files.
#-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)


# Listing of phony targets.
.PHONY : all begin finish end size gccversion \
build elf hex bin lss sym clean clean_list program

