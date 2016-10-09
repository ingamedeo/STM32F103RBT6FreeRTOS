TRGT = arm-none-eabi-
CC   = $(TRGT)gcc
CP   = $(TRGT)objcopy
AS   = $(TRGT)gcc -x assembler-with-cpp
BIN  = $(CP) -O ihex 

MCU  = cortex-m3

# List all default C defines here, like -D_DEBUG=1
DDEFS  = -DSTM32F10X_MD 
DDEFS += -DUSE_STDPERIPH_DRIVER
DDEFS += -DGCC_ARMCM3
# List all default ASM defines here, like -D_DEBUG=1
DADEFS = 

# List all default directories to look for include files here
DINCDIR =

# List the default directory to look for the libraries here
DLIBDIR =

# List all default libraries here
DLIBS = 

#
# End of default section
##############################################################################################

##############################################################################################
# Start of user section
#

# 
# Define project name and Ram/Flash mode here
PROJECT        = main
RUN_FROM_FLASH = 1

# List all user C define here, like -D_DEBUG=1
UDEFS =

# Define ASM defines here
UADEFS = 

# List C source files here
LIBSDIR    = ./Libraries
CORELIBDIR = $(LIBSDIR)/CMSIS/CM3/CoreSupport
DEVDIR  = $(LIBSDIR)/CMSIS/CM3/DeviceSupport/ST/STM32F10x
STMSPDDIR    = $(LIBSDIR)/STM32F10x_StdPeriph_Driver
STMSPSRCDDIR = $(STMSPDDIR)/src
STMSPINCDDIR = $(STMSPDDIR)/inc
DRIVERS    = $(LIBSDIR)/Drivers
DEVICE       = ./Device
STARTUP      = $(DEVICE)/startup
LINKER       = $(DEVICE)/linker
#FreeRtos source locations
FREERTOSSRC  = ./FreeRTOS/Source
FREERTOSINC  = $(FREERTOSSRC)/include
FREERTOSCM3  = $(FREERTOSSRC)/portable/GCC/ARM_CM3
FREERTOSHEAP = $(FREERTOSSRC)/portable/MemMang
##Driver locations
UTILITIES    = $(DRIVERS)/Utilities
LEDS         = $(DRIVERS)/Leds
BUTTONS      = $(DRIVERS)/Buttons
USART        = $(DRIVERS)/Usart
I2C			 = $(DRIVERS)/i2c
BH1750			 = $(DRIVERS)/BH1750
#LCD          = $(DRIVERS)/Lcd
#SPIFLASH     = $(DRIVERS)/SpiFlash
##source list
SRC  = main.c
SRC += stm32f10x_it.c
SRC += $(CORELIBDIR)/core_cm3.c
SRC += $(DEVDIR)/system_stm32f10x.c
SRC += $(STARTUP)/crt.c 
SRC += $(STARTUP)/vectors_stm32f10x_md.c
SRC += $(STARTUP)/newlib_stubs.c
SRC += $(UTILITIES)/delay.c
#SRC += $(UTILITIES)/buffer.c
SRC += $(LEDS)/leds.c
SRC += $(BUTTONS)/buttons.c
SRC += $(USART)/usart.c
SRC += $(I2C)/i2c1_remap.c
SRC += $(BH1750)/bh1750.c
#SRC += $(LCD)/lcd.c
#SRC += $(LCD)/bmp.c
#SRC += $(LCD)/ads7843drv.c
#SRC += $(SPIFLASH)/spi_flash.c
SRC += mytasks.c
#FreeRTOS
SRC += $(FREERTOSCM3)/port.c
SRC += $(FREERTOSHEAP)/heap_2.c 
SRC += $(FREERTOSSRC)/tasks.c
SRC += $(FREERTOSSRC)/queue.c
SRC += $(FREERTOSSRC)/list.c

## used parts of the STM-Library
SRC += $(STMSPSRCDDIR)/stm32f10x_usart.c
SRC += $(STMSPSRCDDIR)/stm32f10x_i2c.c
#SRC += $(STMSPSRCDDIR)/stm32f10x_flash.c
SRC  += $(STMSPSRCDDIR)/stm32f10x_gpio.c
SRC  += $(STMSPSRCDDIR)/stm32f10x_rcc.c
SRC += $(STMSPSRCDDIR)/stm32f10x_spi.c
#SRC += $(STMSPSRCDDIR)/stm32f10x_rtc.c
#SRC += $(STMSPSRCDDIR)/stm32f10x_bkp.c
#SRC += $(STMSPSRCDDIR)/stm32f10x_pwr.c
#SRC += $(STMSPSRCDDIR)/stm32f10x_dma.c
#SRC += $(STMSPSRCDDIR)/stm32f10x_tim.c
SRC += $(STMSPSRCDDIR)/stm32f10x_fsmc.c
SRC += $(STMSPSRCDDIR)/stm32f10x_exti.c
SRC += $(STMSPSRCDDIR)/misc.c

# List ASM source files here
ASRC =

# List all user directories here
UINCDIR  = $(CORELIBDIR)
UINCDIR += $(DEVDIR)
UINCDIR += $(STMSPINCDDIR)
UINCDIR += $(LEDS)
UINCDIR += $(BUTTONS)   
UINCDIR += $(USART)
UINCDIR += $(I2C) 
UINCDIR += $(BH1750)
#UINCDIR += $(LCD)   
UINCDIR += $(SPIFLASH)  
UINCDIR += $(UTILITIES)
UINCDIR += $(FREERTOSINC)
UINCDIR += $(FREERTOSCM3)
# List the user directory to look for the libraries here
ULIBDIR =

# List all user libraries here
ULIBS = 

# Define optimisation level here
OPT = -Os

#
# End of user defines
##############################################################################################
#
# Define linker script file here
#
ifeq ($(RUN_FROM_FLASH), 0)
LDSCRIPT = $(LINKER)/stm32f103xe_ram.ld
FULL_PRJ = $(PROJECT)_ram
else
LDSCRIPT = $(LINKER)/stm32f103xe_flash.ld
FULL_PRJ = $(PROJECT)_rom
endif

INCDIR  = $(patsubst %,-I%,$(DINCDIR) $(UINCDIR))
LIBDIR  = $(patsubst %,-L%,$(DLIBDIR) $(ULIBDIR))

ifeq ($(RUN_FROM_FLASH), 0)
DEFS    = $(DDEFS) $(UDEFS) -DRUN_FROM_FLASH=0 -DVECT_TAB_SRAM
else
DEFS    = $(DDEFS) $(UDEFS) -DRUN_FROM_FLASH=1
endif

ADEFS   = $(DADEFS) $(UADEFS)
OBJS    = $(ASRC:.s=.o) $(SRC:.c=.o)
LIBS    = $(DLIBS) $(ULIBS)
MCFLAGS = -mcpu=$(MCU)

ASFLAGS = $(MCFLAGS) -g -gdwarf-2 -Wa,-amhls=$(<:.s=.lst) $(ADEFS)
CPFLAGS = $(MCFLAGS) $(OPT) -gdwarf-2 -mthumb -fomit-frame-pointer -Wall -Wstrict-prototypes -fverbose-asm -Wa,-ahlms=$(<:.c=.lst) $(DEFS)
LDFLAGS = $(MCFLAGS) -mthumb -nostartfiles -T$(LDSCRIPT) -Wl,-Map=$(FULL_PRJ).map,--cref,--no-warn-mismatch $(LIBDIR)
LDFLAGS += -lm

# Generate dependency information
CPFLAGS += -MD -MP -MF .dep/$(@F).d

#
# makefile rules
#

all: $(OBJS) $(FULL_PRJ).elf $(FULL_PRJ).hex
ifeq ($(RUN_FROM_FLASH), 0)
	$(TRGT)size $(PROJECT)_ram.elf
else
	$(TRGT)size $(PROJECT)_rom.elf
endif

%o : %c
	$(CC) -c $(CPFLAGS) -I . $(INCDIR) $< -o $@

%o : %s
	$(AS) -c $(ASFLAGS) $< -o $@

%elf: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) $(LIBS) -o $@

%hex: %elf
	$(BIN) $< $@
clean:
	-rm -f $(OBJS)
	-rm -f $(FULL_PRJ).elf
	-rm -f $(FULL_PRJ).map
	-rm -f $(FULL_PRJ).hex
	-rm -f $(SRC:.c=.c.bak)
	-rm -f $(SRC:.c=.lst)
	-rm -f $(ASRC:.s=.s.bak)
	-rm -f $(ASRC:.s=.lst)
	-rm -fR .dep

# 
# Include the dependency files, should be the last of the makefile
#
-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)

# *** EOF ***