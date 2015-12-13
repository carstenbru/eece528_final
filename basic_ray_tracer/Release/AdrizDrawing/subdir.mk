################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../AdrizDrawing/AdrizDrawing.c \
../AdrizDrawing/bmplib.c \
../AdrizDrawing/extras.c \
../AdrizDrawing/tahomabold_20.c \
../AdrizDrawing/tahomabold_32.c 

OBJS += \
./AdrizDrawing/AdrizDrawing.o \
./AdrizDrawing/bmplib.o \
./AdrizDrawing/extras.o \
./AdrizDrawing/tahomabold_20.o \
./AdrizDrawing/tahomabold_32.o 

C_DEPS += \
./AdrizDrawing/AdrizDrawing.d \
./AdrizDrawing/bmplib.d \
./AdrizDrawing/extras.d \
./AdrizDrawing/tahomabold_20.d \
./AdrizDrawing/tahomabold_32.d 


# Each subdirectory must supply rules for building sources it contributes
AdrizDrawing/%.o: ../AdrizDrawing/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -DTHREAD_NUM=4 -O3 -Wall -c -fmessage-length=0 -fopenmp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


