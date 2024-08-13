################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/MCAL/USART/USART.c 

OBJS += \
./Src/MCAL/USART/USART.o 

C_DEPS += \
./Src/MCAL/USART/USART.d 


# Each subdirectory must supply rules for building sources it contributes
Src/MCAL/USART/%.o Src/MCAL/USART/%.su Src/MCAL/USART/%.cyclo: ../Src/MCAL/USART/%.c Src/MCAL/USART/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F401RCTx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-MCAL-2f-USART

clean-Src-2f-MCAL-2f-USART:
	-$(RM) ./Src/MCAL/USART/USART.cyclo ./Src/MCAL/USART/USART.d ./Src/MCAL/USART/USART.o ./Src/MCAL/USART/USART.su

.PHONY: clean-Src-2f-MCAL-2f-USART

