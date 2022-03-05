################################################################################
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../Libraries/N32_Std_Driver/CMSIS/device/startup/startup_n32g45x_gcc.S 

O_SRCS += \
../Libraries/N32_Std_Driver/CMSIS/device/startup/startup_n32g45x_gcc.o 

OBJS += \
./Libraries/N32_Std_Driver/CMSIS/device/startup/startup_n32g45x_gcc.o 

S_UPPER_DEPS += \
./Libraries/N32_Std_Driver/CMSIS/device/startup/startup_n32g45x_gcc.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/N32_Std_Driver/CMSIS/device/startup/%.o: ../Libraries/N32_Std_Driver/CMSIS/device/startup/%.S
	arm-none-eabi-gcc -x assembler-with-cpp -Xassembler -mimplicit-it=thumb -c -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -ffunction-sections -fdata-sections -x assembler-with-cpp -Wa,-mimplicit-it=thumb  -gdwarf-2 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

