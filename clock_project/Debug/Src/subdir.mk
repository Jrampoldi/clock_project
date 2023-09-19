################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/clock_handler.c \
../Src/exti_driver.c \
../Src/main.c \
../Src/shift_reg_handler.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/timer_driver.c \
../Src/uart_driver.c 

OBJS += \
./Src/clock_handler.o \
./Src/exti_driver.o \
./Src/main.o \
./Src/shift_reg_handler.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/timer_driver.o \
./Src/uart_driver.o 

C_DEPS += \
./Src/clock_handler.d \
./Src/exti_driver.d \
./Src/main.d \
./Src/shift_reg_handler.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/timer_driver.d \
./Src/uart_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F411CEUx -c -I../Inc -I/Users/jourdanrampoldi/workspace/CMSIS/Include -I/Users/jourdanrampoldi/workspace/CMSIS/Device/ST/STM32F4xx -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/clock_handler.cyclo ./Src/clock_handler.d ./Src/clock_handler.o ./Src/clock_handler.su ./Src/exti_driver.cyclo ./Src/exti_driver.d ./Src/exti_driver.o ./Src/exti_driver.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/shift_reg_handler.cyclo ./Src/shift_reg_handler.d ./Src/shift_reg_handler.o ./Src/shift_reg_handler.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/timer_driver.cyclo ./Src/timer_driver.d ./Src/timer_driver.o ./Src/timer_driver.su ./Src/uart_driver.cyclo ./Src/uart_driver.d ./Src/uart_driver.o ./Src/uart_driver.su

.PHONY: clean-Src

