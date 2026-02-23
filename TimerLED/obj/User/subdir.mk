################################################################################
# MRS Version: 2.3.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/ch32v00x_it.c \
../User/color_data.c \
../User/main.c \
../User/mode_function.c \
../User/pwm.c \
../User/ram.c \
../User/sequence.c \
../User/spi.c \
../User/system_ch32v00x.c \
../User/timer.c 

C_DEPS += \
./User/ch32v00x_it.d \
./User/color_data.d \
./User/main.d \
./User/mode_function.d \
./User/pwm.d \
./User/ram.d \
./User/sequence.d \
./User/spi.d \
./User/system_ch32v00x.d \
./User/timer.d 

OBJS += \
./User/ch32v00x_it.o \
./User/color_data.o \
./User/main.o \
./User/mode_function.o \
./User/pwm.o \
./User/ram.o \
./User/sequence.o \
./User/spi.o \
./User/system_ch32v00x.o \
./User/timer.o 

DIR_OBJS += \
./User/*.o \

DIR_DEPS += \
./User/*.d \

DIR_EXPANDS += \
./User/*.234r.expand \


# Each subdirectory must supply rules for building sources it contributes
User/%.o: ../User/%.c
	@	riscv-none-embed-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"c:/Users/user/mounriver-studio-projects/CH32V003F4P/Debug" -I"c:/Users/user/mounriver-studio-projects/CH32V003F4P/Core" -I"c:/Users/user/mounriver-studio-projects/CH32V003F4P/User" -I"c:/Users/user/mounriver-studio-projects/CH32V003F4P/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

