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
-include Src/MCAL/FLASH/subdir.mk
-include Src/MCAL/EXTI/subdir.mk
-include Src/MCAL/CRC/subdir.mk
-include Src/HAL/LED/subdir.mk
-include Src/HAL/LCD/subdir.mk
-include Src/HAL/Keypad/subdir.mk
-include Src/Core_Peripheral/SystTick/subdir.mk
-include Src/Core_Peripheral/SCB/subdir.mk
-include Src/Core_Peripheral/NVIC/subdir.mk
-include Src/BootLoader/subdir.mk
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


BUILD_ARTIFACT_NAME := STM32F401_My_BootLoader
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
STM32F401_My_BootLoader.elf \

MAP_FILES += \
STM32F401_My_BootLoader.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
STM32F401_My_BootLoader.list \


# All Target
all: main-build

# Main-build Target
main-build: STM32F401_My_BootLoader.elf secondary-outputs

# Tool invocations
STM32F401_My_BootLoader.elf STM32F401_My_BootLoader.map: $(OBJS) $(USER_OBJS) E:\Advanced\ Embedded\ Diploma\Stm32WorkSpace\STM32F401_My_BootLoader\STM32F401RCTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "STM32F401_My_BootLoader.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"E:\Advanced Embedded Diploma\Stm32WorkSpace\STM32F401_My_BootLoader\STM32F401RCTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="STM32F401_My_BootLoader.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

STM32F401_My_BootLoader.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "STM32F401_My_BootLoader.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) STM32F401_My_BootLoader.elf STM32F401_My_BootLoader.list STM32F401_My_BootLoader.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
