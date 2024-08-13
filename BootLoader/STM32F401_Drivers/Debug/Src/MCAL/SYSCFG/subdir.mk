################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/MCAL/SYSCFG/syscfg.c 

OBJS += \
./Src/MCAL/SYSCFG/syscfg.o 

C_DEPS += \
./Src/MCAL/SYSCFG/syscfg.d 


# Each subdirectory must supply rules for building sources it contributes
Src/MCAL/SYSCFG/%.o Src/MCAL/SYSCFG/%.su Src/MCAL/SYSCFG/%.cyclo: ../Src/MCAL/SYSCFG/%.c Src/MCAL/SYSCFG/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F401RCTx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-MCAL-2f-SYSCFG

clean-Src-2f-MCAL-2f-SYSCFG:
	-$(RM) ./Src/MCAL/SYSCFG/syscfg.cyclo ./Src/MCAL/SYSCFG/syscfg.d ./Src/MCAL/SYSCFG/syscfg.o ./Src/MCAL/SYSCFG/syscfg.su

.PHONY: clean-Src-2f-MCAL-2f-SYSCFG

