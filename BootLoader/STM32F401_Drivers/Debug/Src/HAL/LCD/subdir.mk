################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/HAL/LCD/lcd.c 

OBJS += \
./Src/HAL/LCD/lcd.o 

C_DEPS += \
./Src/HAL/LCD/lcd.d 


# Each subdirectory must supply rules for building sources it contributes
Src/HAL/LCD/%.o Src/HAL/LCD/%.su Src/HAL/LCD/%.cyclo: ../Src/HAL/LCD/%.c Src/HAL/LCD/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F401RCTx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-HAL-2f-LCD

clean-Src-2f-HAL-2f-LCD:
	-$(RM) ./Src/HAL/LCD/lcd.cyclo ./Src/HAL/LCD/lcd.d ./Src/HAL/LCD/lcd.o ./Src/HAL/LCD/lcd.su

.PHONY: clean-Src-2f-HAL-2f-LCD

