################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/MCAL/FLASH/Flash.c 

OBJS += \
./Src/MCAL/FLASH/Flash.o 

C_DEPS += \
./Src/MCAL/FLASH/Flash.d 


# Each subdirectory must supply rules for building sources it contributes
Src/MCAL/FLASH/%.o Src/MCAL/FLASH/%.su Src/MCAL/FLASH/%.cyclo: ../Src/MCAL/FLASH/%.c Src/MCAL/FLASH/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F401RCTx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-MCAL-2f-FLASH

clean-Src-2f-MCAL-2f-FLASH:
	-$(RM) ./Src/MCAL/FLASH/Flash.cyclo ./Src/MCAL/FLASH/Flash.d ./Src/MCAL/FLASH/Flash.o ./Src/MCAL/FLASH/Flash.su

.PHONY: clean-Src-2f-MCAL-2f-FLASH

