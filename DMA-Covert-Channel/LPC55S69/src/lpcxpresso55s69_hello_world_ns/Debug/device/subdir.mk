################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../device/system_LPC55S69_cm33_core0.c 

C_DEPS += \
./device/system_LPC55S69_cm33_core0.d 

OBJS += \
./device/system_LPC55S69_cm33_core0.o 


# Each subdirectory must supply rules for building sources it contributes
device/%.o: ../device/%.c device/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -DCPU_LPC55S69JBD100_cm33_core0 -DMCUXPRESSO_SDK -DCPU_LPC55S69JBD100 -DCPU_LPC55S69JBD100_cm33 -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -DSDK_OS_BAREMETAL -DSERIAL_PORT_TYPE_UART=1 -I"/home/cris/Documents/0_Projects/uarchs_paper/LPC55S69_DMA_Covert_Channel/src/lpcxpresso55s69_hello_world_ns/utilities" -I"/home/cris/Documents/0_Projects/uarchs_paper/LPC55S69_DMA_Covert_Channel/src/lpcxpresso55s69_hello_world_ns/drivers" -I"/home/cris/Documents/0_Projects/uarchs_paper/LPC55S69_DMA_Covert_Channel/src/lpcxpresso55s69_hello_world_ns/device" -I"/home/cris/Documents/0_Projects/uarchs_paper/LPC55S69_DMA_Covert_Channel/src/lpcxpresso55s69_hello_world_ns/startup" -I"/home/cris/Documents/0_Projects/uarchs_paper/LPC55S69_DMA_Covert_Channel/src/lpcxpresso55s69_hello_world_ns/component/uart" -I"/home/cris/Documents/0_Projects/uarchs_paper/LPC55S69_DMA_Covert_Channel/src/lpcxpresso55s69_hello_world_ns/component/lists" -I"/home/cris/Documents/0_Projects/uarchs_paper/LPC55S69_DMA_Covert_Channel/src/lpcxpresso55s69_hello_world_ns/CMSIS" -I"/home/cris/Documents/0_Projects/uarchs_paper/LPC55S69_DMA_Covert_Channel/src/lpcxpresso55s69_hello_world_ns/board" -I"/home/cris/Documents/0_Projects/uarchs_paper/LPC55S69_DMA_Covert_Channel/src/lpcxpresso55s69_hello_world_ns/component/serial_manager" -I"/home/cris/Documents/0_Projects/uarchs_paper/LPC55S69_DMA_Covert_Channel/src/lpcxpresso55s69_hello_world_ns/source" -I"/home/cris/Documents/0_Projects/uarchs_paper/LPC55S69_DMA_Covert_Channel/src/lpcxpresso55s69_hello_world_ns/utilities" -I"/home/cris/Documents/0_Projects/uarchs_paper/LPC55S69_DMA_Covert_Channel/src/lpcxpresso55s69_hello_world_ns/drivers" -I"/home/cris/Documents/0_Projects/uarchs_paper/LPC55S69_DMA_Covert_Channel/src/lpcxpresso55s69_hello_world_ns/device" -I"/home/cris/Documents/0_Projects/uarchs_paper/LPC55S69_DMA_Covert_Channel/src/lpcxpresso55s69_hello_world_ns/startup" -I"/home/cris/Documents/0_Projects/uarchs_paper/LPC55S69_DMA_Covert_Channel/src/lpcxpresso55s69_hello_world_ns/component/uart" -I"/home/cris/Documents/0_Projects/uarchs_paper/LPC55S69_DMA_Covert_Channel/src/lpcxpresso55s69_hello_world_ns/component/lists" -I"/home/cris/Documents/0_Projects/uarchs_paper/LPC55S69_DMA_Covert_Channel/src/lpcxpresso55s69_hello_world_ns/CMSIS" -I"/home/cris/Documents/0_Projects/uarchs_paper/LPC55S69_DMA_Covert_Channel/src/lpcxpresso55s69_hello_world_ns/board" -I"/home/cris/Documents/0_Projects/uarchs_paper/LPC55S69_DMA_Covert_Channel/src/lpcxpresso55s69_hello_world_ns/trustzone" -O0 -fno-common -g3 -D __SEMIHOST_HARDFAULT_DISABLE -mcpu=cortex-m33 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-device

clean-device:
	-$(RM) ./device/system_LPC55S69_cm33_core0.d ./device/system_LPC55S69_cm33_core0.o

.PHONY: clean-device

