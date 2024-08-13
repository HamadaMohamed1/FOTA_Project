################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/HAL/LED/led.c 

OBJS += \
./Src/HAL/LED/led.o 

C_DEPS += \
./Src/HAL/LED/led.d 


# Each subdirectory must supply rules for building sources it contributes
Src/HAL/LED/%.o Src/HAL/LED/%.su Src/HAL/LED/%.cyclo: ../Src/HAL/LED/%.c Src/HAL/LED/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F401RCTx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-HAL-2f-LED

clean-Src-2f-HAL-2f-LED:
	-$(RM) ./Src/HAL/LED/led.cyclo ./Src/HAL/LED/led.d ./Src/HAL/LED/led.o ./Src/HAL/LED/led.su

.PHONY: clean-Src-2f-HAL-2f-LED

