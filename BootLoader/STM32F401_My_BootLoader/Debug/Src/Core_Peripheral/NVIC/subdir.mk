################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/Core_Peripheral/NVIC/NVIC.c 

OBJS += \
./Src/Core_Peripheral/NVIC/NVIC.o 

C_DEPS += \
./Src/Core_Peripheral/NVIC/NVIC.d 


# Each subdirectory must supply rules for building sources it contributes
Src/Core_Peripheral/NVIC/%.o Src/Core_Peripheral/NVIC/%.su Src/Core_Peripheral/NVIC/%.cyclo: ../Src/Core_Peripheral/NVIC/%.c Src/Core_Peripheral/NVIC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F401RCTx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-Core_Peripheral-2f-NVIC

clean-Src-2f-Core_Peripheral-2f-NVIC:
	-$(RM) ./Src/Core_Peripheral/NVIC/NVIC.cyclo ./Src/Core_Peripheral/NVIC/NVIC.d ./Src/Core_Peripheral/NVIC/NVIC.o ./Src/Core_Peripheral/NVIC/NVIC.su

.PHONY: clean-Src-2f-Core_Peripheral-2f-NVIC

