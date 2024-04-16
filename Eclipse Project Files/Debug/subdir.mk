################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LCD.c \
../Mini_Project_Four.c \
../Ultrasonic_HC_SR04.c \
../gpio.c \
../icu.c 

OBJS += \
./LCD.o \
./Mini_Project_Four.o \
./Ultrasonic_HC_SR04.o \
./gpio.o \
./icu.o 

C_DEPS += \
./LCD.d \
./Mini_Project_Four.d \
./Ultrasonic_HC_SR04.d \
./gpio.d \
./icu.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


