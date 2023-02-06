################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/BUTTON.c \
../Core/Src/DELAY.c \
../Core/Src/DHT11.c \
../Core/Src/DISPLAY.c \
../Core/Src/DS1307.c \
../Core/Src/LCD.c \
../Core/Src/MENU.c \
../Core/Src/ROTARY_ENCODER.c \
../Core/Src/main.c \
../Core/Src/stm32f1xx_hal_msp.c \
../Core/Src/stm32f1xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f1xx.c 

OBJS += \
./Core/Src/BUTTON.o \
./Core/Src/DELAY.o \
./Core/Src/DHT11.o \
./Core/Src/DISPLAY.o \
./Core/Src/DS1307.o \
./Core/Src/LCD.o \
./Core/Src/MENU.o \
./Core/Src/ROTARY_ENCODER.o \
./Core/Src/main.o \
./Core/Src/stm32f1xx_hal_msp.o \
./Core/Src/stm32f1xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f1xx.o 

C_DEPS += \
./Core/Src/BUTTON.d \
./Core/Src/DELAY.d \
./Core/Src/DHT11.d \
./Core/Src/DISPLAY.d \
./Core/Src/DS1307.d \
./Core/Src/LCD.d \
./Core/Src/MENU.d \
./Core/Src/ROTARY_ENCODER.d \
./Core/Src/main.d \
./Core/Src/stm32f1xx_hal_msp.d \
./Core/Src/stm32f1xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f1xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -IC:/Users/chaun/STM32Cube/Repository/STM32Cube_FW_F1_V1.8.4/Drivers/STM32F1xx_HAL_Driver/Inc -IC:/Users/chaun/STM32Cube/Repository/STM32Cube_FW_F1_V1.8.4/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -IC:/Users/chaun/STM32Cube/Repository/STM32Cube_FW_F1_V1.8.4/Drivers/CMSIS/Device/ST/STM32F1xx/Include -IC:/Users/chaun/STM32Cube/Repository/STM32Cube_FW_F1_V1.8.4/Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/BUTTON.d ./Core/Src/BUTTON.o ./Core/Src/BUTTON.su ./Core/Src/DELAY.d ./Core/Src/DELAY.o ./Core/Src/DELAY.su ./Core/Src/DHT11.d ./Core/Src/DHT11.o ./Core/Src/DHT11.su ./Core/Src/DISPLAY.d ./Core/Src/DISPLAY.o ./Core/Src/DISPLAY.su ./Core/Src/DS1307.d ./Core/Src/DS1307.o ./Core/Src/DS1307.su ./Core/Src/LCD.d ./Core/Src/LCD.o ./Core/Src/LCD.su ./Core/Src/MENU.d ./Core/Src/MENU.o ./Core/Src/MENU.su ./Core/Src/ROTARY_ENCODER.d ./Core/Src/ROTARY_ENCODER.o ./Core/Src/ROTARY_ENCODER.su ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/stm32f1xx_hal_msp.d ./Core/Src/stm32f1xx_hal_msp.o ./Core/Src/stm32f1xx_hal_msp.su ./Core/Src/stm32f1xx_it.d ./Core/Src/stm32f1xx_it.o ./Core/Src/stm32f1xx_it.su ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f1xx.d ./Core/Src/system_stm32f1xx.o ./Core/Src/system_stm32f1xx.su

.PHONY: clean-Core-2f-Src

