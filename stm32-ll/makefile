TARGET    := led-blink

# 存放编译文件的目录
BUILD_DIR := ./Build

# ARM GCC 工具链
TOOLCHAIN  = arm-none-eabi-
CC  := $(TOOLCHAIN)gcc
CP  := $(TOOLCHAIN)objcopy
AS  := $(TOOLCHAIN)gcc -x assembler-with-cpp
SZ  := $(TOOLCHAIN)size
HEX := $(CP) -O ihex
BIN := $(CP) -O binary -S

# CPU 内核架构
CPU := cortex-m3

# 链接脚本
LINK_SCRIPT := ./STM32F103ZETx_FLASH.ld

# gcc 预定义参数
DEFS := -D STM32F103xE \
		-D USE_FULL_LL_DRIVER \
		-D HSE_VALUE=8000000 \
		-D HSE_STARTUP_TIMEOUT=100 \
		-D LSE_STARTUP_TIMEOUT=5000 \
		-D LSE_VALUE=32768 \
		-D HSI_VALUE=8000000 \
		-D LSI_VALUE=40000 \
		-D VDD_VALUE=3300 \
		-D PREFETCH_ENABLE=1

# LL 库头文件路径
INC_DIR := ./Drivers/CMSIS/Include/
INC_DIR += ./Drivers/CMSIS/Device/ST/STM32F1xx/Include/
INC_DIR += ./Drivers/STM32F1xx_HAL_Driver/Inc/

# 启动文件
ASM_SRC := ./Drivers/CMSIS/Device/ST/STM32F1xx/Source/Templates/gcc/startup_stm32f103xe.s

# CMSIS 系统文件
C_SRC := ./Drivers/CMSIS/Device/ST/STM32F1xx/Source/Templates/system_stm32f1xx.c

# LL 库外设源文件
C_SRC += $(wildcard ./Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_ll*.c)
C_SRC := $(filter-out %ll_usb.c, $(C_SRC))
C_SRC := $(filter-out %ll_sdmmc.c, $(C_SRC))
C_SRC := $(filter-out %ll_fsmc.c, $(C_SRC))

# 用户头文件路径
INC_DIR += ./User/
INC_DIR += ./User/led/

# 用户代码
C_SRC += $(wildcard ./User/*.c)
C_SRC += $(wildcard ./User/led/*.c)

# 目标文件
C_OBJ := $(addprefix $(BUILD_DIR)/,$(notdir $(C_SRC:.c=.o)))
ASM_OBJ := $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SRC:.s=.o)))

# 编译参数
CP_FLAGS := $(addprefix -I,$(INC_DIR)) -mcpu=$(CPU) -g -gdwarf-2 -mthumb -Os -Wall -fdata-sections -ffunction-sections -MMD -MP $(DEFS)
# 汇编参数
AS_FLAGS := $(addprefix -I,$(INC_DIR)) -mcpu=$(CPU) -g -gdwarf-2 -mthumb -Os -Wall -fdata-sections -ffunction-sections -MMD -MP
# 链接参数
LD_FLAGS := -mcpu=$(CPU) -specs=nano.specs -T $(LINK_SCRIPT) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref,--gc-sections

# 设置 make 文件搜索路径，.h文件由 gcc -I 参数包含了
vpath %.c $(sort $(dir $(C_SRC)))
vpath %.s $(sort $(dir $(ASM_SRC)))

# 保留目标文件，make 默认是删除编译生成的 .o 文件
.PRECIOUS: $(BUILD_DIR)/%.o




.PHONY: all
all: $(BUILD_DIR) $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).bin $(BUILD_DIR)/$(TARGET).hex
	@echo "-------------------------------------------------------------------------------"
	$(SZ) $(BUILD_DIR)/$(TARGET).elf
	@echo "-------------------------------------------------------------------------------"
	@stat $(BUILD_DIR)/$(TARGET).bin | head -n2
	@echo "-------------------------------------------------------------------------------"

$(BUILD_DIR)/%.o: %.c
	$(CC) -c $(CP_FLAGS) $< -o $@

$(BUILD_DIR)/%.o: %.s
	$(AS) -c $(AS_FLAGS) $< -o $@

%.elf: $(C_OBJ) $(ASM_OBJ) 
	$(CC) $(LD_FLAGS) $^ -o $@

%.hex: %.elf
	$(HEX) $< $@

%.bin: %.elf
	$(BIN) $< $@

$(BUILD_DIR):
	mkdir -p $@




clean:
	rm $(BUILD_DIR)/ -rf

rebuild:
	make clean && make

install:
	st-flash write $(BUILD_DIR)/$(TARGET).bin 0x8000000

st-flash:
	st-flash write $(BUILD_DIR)/$(TARGET).bin 0x8000000

st-erase:
	st-flash erase

isp-flash:
	stm32flash -b 115200 -i '-dtr&rts,dtr:-dtr&-rts,dtr' -v -w $(BUILD_DIR)/$(TARGET).bin /dev/ttyUSB0

isp-erase:
	stm32flash -b 115200 -i '-dtr&rts,dtr:-dtr&-rts,dtr' -o /dev/ttyUSB0

isp-info:
	stm32flash -b 115200 -i '-dtr&rts,dtr:-dtr&-rts,dtr' /dev/ttyUSB0


# 包含由 gcc -MMD 参数生成的 .d 文件
-include $(BUILD_DIR)/*.d
