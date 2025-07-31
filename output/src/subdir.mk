################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/hw.c \
../src/main.c \
../src/stm32g0xx_it.c \
../src/syscall.c 

S_UPPER_SRCS += \
../src/startup.S 

OBJS += \
./src/hw.o \
./src/main.o \
./src/startup.o \
./src/stm32g0xx_it.o \
./src/syscall.o 

S_UPPER_DEPS += \
./src/startup.d 

C_DEPS += \
./src/hw.d \
./src/main.d \
./src/stm32g0xx_it.d \
./src/syscall.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -DSTM32G030xx -DHSI_VALUE=16000000U -DLSI_VALUE=32000U -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -DUSE_FULL_LL_DRIVER -pedantic -w -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wpadded -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -g -UDEBUG -UUSE_FULL_ASSERT -I"/mnt/home/anaber/Documents/programming/bip3gn/include" -I"/mnt/home/anaber/Documents/programming/bip3gn/stm32g0xx-hal/Include" -I/mnt/home/anaber/Documents/programming/bip3gn/cmsis -std=c17 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.S src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -DSTM32G030xx -DHSI_VALUE=16000000U -DLSI_VALUE=32000U -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -DUSE_FULL_LL_DRIVER -pedantic -w -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wpadded -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -g -UDEBUG -UUSE_FULL_ASSERT -x assembler-with-cpp -I"/mnt/home/anaber/Documents/programming/bip3gn/include" -I"/mnt/home/anaber/Documents/programming/bip3gn/stm32g0xx-hal/Include" -I"/mnt/home/anaber/Documents/programming/bip3gn/cmsis" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


