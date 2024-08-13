################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/MCAL/USART/subdir.mk
-include Src/MCAL/SYSCFG/subdir.mk
-include Src/MCAL/SPI/subdir.mk
-include Src/MCAL/RCC/subdir.mk
-include Src/MCAL/I2C/subdir.mk
-include Src/MCAL/GPIO/subdir.mk
-include Src/MCAL/EXTI/subdir.mk
-include Src/HAL/LED/subdir.mk
-include Src/HAL/LCD/subdir.mk
-include Src/HAL/Keypad/subdir.mk
-include Src/HAL/Dot_Matrix/subdir.mk
-include Src/Core_Peripheral/SystTick/subdir.mk
-include Src/Core_Peripheral/SCB/subdir.mk
-include Src/Core_Peripheral/NVIC/subdir.mk
-include Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := STM32F401_Drivers
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
STM32F401_Drivers.elf \

MAP_FILES += \
STM32F401_Drivers.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
STM32F401_Drivers.list \

OBJCOPY_HEX += \
STM32F401_Drivers.hex \

OBJCOPY_BIN += \
STM32F401_Drivers.bin \


# All Target
all: main-build

# Main-build Target
main-build: STM32F401_Drivers.elf secondary-outputs

# Tool invocations
STM32F401_Drivers.elf STM32F401_Drivers.map: $(OBJS) $(USER_OBJS) E:\Advanced\ Embedded\ Diploma\Stm32WorkSpace\STM32F401_Drivers\STM32F401RCTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "STM32F401_Drivers.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"E:\Advanced Embedded Diploma\Stm32WorkSpace\STM32F401_Drivers\STM32F401RCTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="STM32F401_Drivers.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

STM32F401_Drivers.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "STM32F401_Drivers.list"
	@echo 'Finished building: $@'
	@echo ' '

STM32F401_Drivers.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "STM32F401_Drivers.hex"
	@echo 'Finished building: $@'
	@echo ' '

STM32F401_Drivers.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "STM32F401_Drivers.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) STM32F401_Drivers.bin STM32F401_Drivers.elf STM32F401_Drivers.hex STM32F401_Drivers.list STM32F401_Drivers.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
