################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/Core_Peripheral/SystTick/SystTick.c 

OBJS += \
./Src/Core_Peripheral/SystTick/SystTick.o 

C_DEPS += \
./Src/Core_Peripheral/SystTick/SystTick.d 


# Each subdirectory must supply rules for building sources it contributes
Src/Core_Peripheral/SystTick/%.o Src/Core_Peripheral/SystTick/%.su Src/Core_Peripheral/SystTick/%.cyclo: ../Src/Core_Peripheral/SystTick/%.c Src/Core_Peripheral/SystTick/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F401RCTx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-Core_Peripheral-2f-SystTick

clean-Src-2f-Core_Peripheral-2f-SystTick:
	-$(RM) ./Src/Core_Peripheral/SystTick/SystTick.cyclo ./Src/Core_Peripheral/SystTick/SystTick.d ./Src/Core_Peripheral/SystTick/SystTick.o ./Src/Core_Peripheral/SystTick/SystTick.su

.PHONY: clean-Src-2f-Core_Peripheral-2f-SystTick

