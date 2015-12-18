################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cfgProject.c \
../src/drvSysTick.c \
../src/main.c \
../src/prpSwitch.c \
../src/prpWebClient.c 

OBJS += \
./src/cfgProject.o \
./src/drvSysTick.o \
./src/main.o \
./src/prpSwitch.o \
./src/prpWebClient.o 

C_DEPS += \
./src/cfgProject.d \
./src/drvSysTick.d \
./src/main.d \
./src/prpSwitch.d \
./src/prpWebClient.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I../src -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


