################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../rt-thread/src/clock.c \
../rt-thread/src/components.c \
../rt-thread/src/device.c \
../rt-thread/src/idle.c \
../rt-thread/src/ipc.c \
../rt-thread/src/irq.c \
../rt-thread/src/kservice.c \
../rt-thread/src/mem.c \
../rt-thread/src/mempool.c \
../rt-thread/src/object.c \
../rt-thread/src/scheduler.c \
../rt-thread/src/thread.c \
../rt-thread/src/timer.c 

OBJS += \
./rt-thread/src/clock.o \
./rt-thread/src/components.o \
./rt-thread/src/device.o \
./rt-thread/src/idle.o \
./rt-thread/src/ipc.o \
./rt-thread/src/irq.o \
./rt-thread/src/kservice.o \
./rt-thread/src/mem.o \
./rt-thread/src/mempool.o \
./rt-thread/src/object.o \
./rt-thread/src/scheduler.o \
./rt-thread/src/thread.o \
./rt-thread/src/timer.o 

C_DEPS += \
./rt-thread/src/clock.d \
./rt-thread/src/components.d \
./rt-thread/src/device.d \
./rt-thread/src/idle.d \
./rt-thread/src/ipc.d \
./rt-thread/src/irq.d \
./rt-thread/src/kservice.d \
./rt-thread/src/mem.d \
./rt-thread/src/mempool.d \
./rt-thread/src/object.d \
./rt-thread/src/scheduler.d \
./rt-thread/src/thread.d \
./rt-thread/src/timer.d 


# Each subdirectory must supply rules for building sources it contributes
rt-thread/src/%.o: ../rt-thread/src/%.c
	arm-none-eabi-gcc -I"E:\2_Software_Project\Nation\demo\N32G45\applications\led" -I"E:\2_Software_Project\Nation\demo\N32G45\applications\lcd" -I"E:\2_Software_Project\Nation\demo\N32G45\applications\spi" -I"E:\2_Software_Project\Nation\demo\N32G45" -I"E:\2_Software_Project\Nation\demo\N32G45\Libraries\N32_Std_Driver\CMSIS\core" -I"E:\2_Software_Project\Nation\demo\N32G45\Libraries\N32_Std_Driver\CMSIS\device" -I"E:\2_Software_Project\Nation\demo\N32G45\Libraries\N32_Std_Driver\n32g45x_std_periph_driver\inc" -I"E:\2_Software_Project\Nation\demo\N32G45\Libraries\rt_drivers" -I"E:\2_Software_Project\Nation\demo\N32G45\applications" -I"E:\2_Software_Project\Nation\demo\N32G45\board\msp" -I"E:\2_Software_Project\Nation\demo\N32G45\board" -I"E:\2_Software_Project\Nation\demo\N32G45\rt-thread\components\drivers\include" -I"E:\2_Software_Project\Nation\demo\N32G45\rt-thread\components\drivers\spi" -I"E:\2_Software_Project\Nation\demo\N32G45\rt-thread\components\finsh" -I"E:\2_Software_Project\Nation\demo\N32G45\rt-thread\components\libc\compilers\common" -I"E:\2_Software_Project\Nation\demo\N32G45\rt-thread\components\libc\compilers\gcc\newlib" -I"E:\2_Software_Project\Nation\demo\N32G45\rt-thread\include" -I"E:\2_Software_Project\Nation\demo\N32G45\rt-thread\libcpu\arm\common" -I"E:\2_Software_Project\Nation\demo\N32G45\rt-thread\libcpu\arm\cortex-m4" -include"E:\2_Software_Project\Nation\demo\N32G45\rtconfig_preinc.h" -std=gnu11 -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -ffunction-sections -fdata-sections -Dgcc -O0 -gdwarf-2 -g -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

