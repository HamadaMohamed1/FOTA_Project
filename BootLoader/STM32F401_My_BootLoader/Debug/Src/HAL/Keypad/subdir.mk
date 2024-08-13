################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/HAL/Keypad/keypad.c 

OBJS += \
./Src/HAL/Keypad/keypad.o 

C_DEPS += \
./Src/HAL/Keypad/keypad.d 


# Each subdirectory must supply rules for building sources it contributes
Src/HAL/Keypad/%.o Src/HAL/Keypad/%.su Src/HAL/Keypad/%.cyclo: ../Src/HAL/Keypad/%.c Src/HAL/Keypad/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F401RCTx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-HAL-2f-Keypad

clean-Src-2f-HAL-2f-Keypad:
	-$(RM) ./Src/HAL/Keypad/keypad.cyclo ./Src/HAL/Keypad/keypad.d ./Src/HAL/Keypad/keypad.o ./Src/HAL/Keypad/keypad.su

.PHONY: clean-Src-2f-HAL-2f-Keypad

