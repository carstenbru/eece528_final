################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../OpenCL_Raytracer.cpp \
../Raytracer.cpp \
../Raytracer_OpenMP.cpp \
../Raytracer_int.cpp \
../Raytracer_pthreads.cpp \
../Sphere.cpp \
../Vec3.cpp \
../main.cpp 

OBJS += \
./OpenCL_Raytracer.o \
./Raytracer.o \
./Raytracer_OpenMP.o \
./Raytracer_int.o \
./Raytracer_pthreads.o \
./Sphere.o \
./Vec3.o \
./main.o 

CPP_DEPS += \
./OpenCL_Raytracer.d \
./Raytracer.d \
./Raytracer_OpenMP.d \
./Raytracer_int.d \
./Raytracer_pthreads.d \
./Sphere.d \
./Vec3.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DTHREAD_NUM=4 -O0 -g3 -Wall -c -fmessage-length=0 -fopenmp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


