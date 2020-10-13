################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Client.c \
../src/ClientPublication.c \
../src/Parcial01_Lab.c \
../src/Publication.c \
../src/inform.c \
../src/inputs.c 

OBJS += \
./src/Client.o \
./src/ClientPublication.o \
./src/Parcial01_Lab.o \
./src/Publication.o \
./src/inform.o \
./src/inputs.o 

C_DEPS += \
./src/Client.d \
./src/ClientPublication.d \
./src/Parcial01_Lab.d \
./src/Publication.d \
./src/inform.d \
./src/inputs.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


