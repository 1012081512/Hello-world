################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../rt-thread/components/libc/compilers/gcc/newlib/libc.c \
../rt-thread/components/libc/compilers/gcc/newlib/stdio.c \
../rt-thread/components/libc/compilers/gcc/newlib/syscalls.c 

OBJS += \
./rt-thread/components/libc/compilers/gcc/newlib/libc.o \
./rt-thread/components/libc/compilers/gcc/newlib/stdio.o \
./rt-thread/components/libc/compilers/gcc/newlib/syscalls.o 

C_DEPS += \
./rt-thread/components/libc/compilers/gcc/newlib/libc.d \
./rt-thread/components/libc/compilers/gcc/newlib/stdio.d \
./rt-thread/components/libc/compilers/gcc/newlib/syscalls.d 


# Each subdirectory must supply rules for building sources it contributes
rt-thread/components/libc/compilers/gcc/newlib/%.o: ../rt-thread/components/libc/compilers/gcc/newlib/%.c
	arm-none-eabi-gcc -I"E:\2_Software_Project\Nation\demo\N32G45\applications\led" -I"E:\2_Software_Project\Nation\demo\N32G45\applications\lcd" -I"E:\2_Software_Project\Nation\demo\N32G45\applications\spi" -I"E:\2_Software_Project\Nation\demo\N32G45" -I"E:\2_Software_Project\Nation\demo\N32G45\Libraries\N32_Std_Driver\CMSIS\core" -I"E:\2_Software_Project\Nation\demo\N32G45\Libraries\N32_Std_Driver\CMSIS\device" -I"E:\2_Software_Project\Nation\demo\N32G45\Libraries\N32_Std_Driver\n32g45x_std_periph_driver\inc" -I"E:\2_Software_Project\Nation\demo\N32G45\Libraries\rt_drivers" -I"E:\2_Software_Project\Nation\demo\N32G45\applications" -I"E:\2_Software_Project\Nation\demo\N32G45\board\msp" -I"E:\2_Software_Project\Nation\demo\N32G45\board" -I"E:\2_Software_Project\Nation\demo\N32G45\rt-thread\components\drivers\include" -I"E:\2_Software_Project\Nation\demo\N32G45\rt-thread\components\drivers\spi" -I"E:\2_Software_Project\Nation\demo\N32G45\rt-thread\components\finsh" -I"E:\2_Software_Project\Nation\demo\N32G45\rt-thread\components\libc\compilers\common" -I"E:\2_Software_Project\Nation\demo\N32G45\rt-thread\components\libc\compilers\gcc\newlib" -I"E:\2_Software_Project\Nation\demo\N32G45\rt-thread\include" -I"E:\2_Software_Project\Nation\demo\N32G45\rt-thread\libcpu\arm\common" -I"E:\2_Software_Project\Nation\demo\N32G45\rt-thread\libcpu\arm\cortex-m4" -include"E:\2_Software_Project\Nation\demo\N32G45\rtconfig_preinc.h" -std=gnu11 -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -ffunction-sections -fdata-sections -Dgcc -O0 -gdwarf-2 -g -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

