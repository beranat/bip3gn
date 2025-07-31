################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../stm32g0xx-hal/src/stm32g0xx_ll_exti.c \
../stm32g0xx-hal/src/stm32g0xx_ll_gpio.c \
../stm32g0xx-hal/src/stm32g0xx_ll_pwr.c \
../stm32g0xx-hal/src/stm32g0xx_ll_rcc.c \
../stm32g0xx-hal/src/stm32g0xx_ll_tim.c \
../stm32g0xx-hal/src/stm32g0xx_ll_utils.c 

OBJS += \
./stm32g0xx-hal/src/stm32g0xx_ll_exti.o \
./stm32g0xx-hal/src/stm32g0xx_ll_gpio.o \
./stm32g0xx-hal/src/stm32g0xx_ll_pwr.o \
./stm32g0xx-hal/src/stm32g0xx_ll_rcc.o \
./stm32g0xx-hal/src/stm32g0xx_ll_tim.o \
./stm32g0xx-hal/src/stm32g0xx_ll_utils.o 

C_DEPS += \
./stm32g0xx-hal/src/stm32g0xx_ll_exti.d \
./stm32g0xx-hal/src/stm32g0xx_ll_gpio.d \
./stm32g0xx-hal/src/stm32g0xx_ll_pwr.d \
./stm32g0xx-hal/src/stm32g0xx_ll_rcc.d \
./stm32g0xx-hal/src/stm32g0xx_ll_tim.d \
./stm32g0xx-hal/src/stm32g0xx_ll_utils.d 


# Each subdirectory must supply rules for building sources it contributes
stm32g0xx-hal/src/%.o: ../stm32g0xx-hal/src/%.c stm32g0xx-hal/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -DSTM32G030xx -DHSI_VALUE=16000000U -DLSI_VALUE=32000U -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -DUSE_FULL_LL_DRIVER -pedantic -w -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wpadded -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -g -UDEBUG -UUSE_FULL_ASSERT -I"/mnt/home/anaber/Documents/programming/bip3gn/include" -I"/mnt/home/anaber/Documents/programming/bip3gn/stm32g0xx-hal/Include" -I/mnt/home/anaber/Documents/programming/bip3gn/cmsis -std=c17 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


