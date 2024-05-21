################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/fsl_clock.c \
../drivers/fsl_common.c \
../drivers/fsl_common_arm.c \
../drivers/fsl_dma.c \
../drivers/fsl_flexcomm.c \
../drivers/fsl_gpio.c \
../drivers/fsl_i2c.c \
../drivers/fsl_power.c \
../drivers/fsl_reset.c \
../drivers/fsl_usart.c 

C_DEPS += \
./drivers/fsl_clock.d \
./drivers/fsl_common.d \
./drivers/fsl_common_arm.d \
./drivers/fsl_dma.d \
./drivers/fsl_flexcomm.d \
./drivers/fsl_gpio.d \
./drivers/fsl_i2c.d \
./drivers/fsl_power.d \
./drivers/fsl_reset.d \
./drivers/fsl_usart.d 

OBJS += \
./drivers/fsl_clock.o \
./drivers/fsl_common.o \
./drivers/fsl_common_arm.o \
./drivers/fsl_dma.o \
./drivers/fsl_flexcomm.o \
./drivers/fsl_gpio.o \
./drivers/fsl_i2c.o \
./drivers/fsl_power.o \
./drivers/fsl_reset.o \
./drivers/fsl_usart.o 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c drivers/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -DCPU_LPC55S69JBD100_cm33_core0 -DMCUXPRESSO_SDK -DCPU_LPC55S69JBD100 -DCPU_LPC55S69JBD100_cm33 -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -DSDK_OS_BAREMETAL -DSERIAL_PORT_TYPE_UART=1 -I"/home/cris/Documents/0_Projects/uarchs_paper/LPC55S69_DMA_Covert_Channel/src/lpcxpresso55s69_hello_world_ns/utilities" -I"/home/cris/Documents/0_Projects/uarchs_paper/LPC55S69_DMA_Covert_Channel/src/lpcxpresso55s69_hello_world_ns/drivers" -I"/home/cris/Documents/0_Projects/uarchs_paper/LPC55S69_DMA_Covert_Channel/src/lpcxpresso55s69_hello_world_ns/device" -I"/home/cris/Documents/0_Projects/uarchs_paper/LPC55S69_DMA_Covert_Channel/src/lpcxpresso55s69_hello_world_ns/startup" -I"/home/cris/Documents/0_Projects/uarchs_paper/LPC55S69_DMA_Covert_Channel/src/lpcxpresso55s69_hello_world_ns/component/uart" -I"/home/cris/Documents/0_Projects/uarchs_paper/LPC55S69_DMA_Covert_Channel/src/lpcxpresso55s69_hello_world_ns/component/lists" -I"/home/cris/Documents/0_Projects/uarchs_paper/LPC55S69_DMA_Covert_Channel/src/lpcxpresso55s69_hello_world_ns/CMSIS" -I"/home/cris/Documents/0_Projects/uarchs_paper/LPC55S69_DMA_Covert_Channel/src/lpcxpresso55s69_hello_world_ns/board" -I"/home/cris/Documents/0_Projects/uarchs_paper/LPC55S69_DMA_Covert_Channel/src/lpcxpresso55s69_hello_world_ns/component/serial_manager" -I"/home/cris/Documents/0_Projects/uarchs_paper/LPC55S69_DMA_Covert_Channel/src/lpcxpresso55s69_hello_world_ns/source" -I"/home/cris/Documents/0_Projects/uarchs_paper/LPC55S69_DMA_Covert_Channel/src/lpcxpresso55s69_hello_world_ns/utilities" -I"/home/cris/Documents/0_Projects/uarchs_paper/LPC55S69_DMA_Covert_Channel/src/lpcxpresso55s69_hello_world_ns/drivers" -I"/home/cris/Documents/0_Projects/uarchs_paper/LPC55S69_DMA_Covert_Channel/src/lpcxpresso55s69_hello_world_ns/device" -I"/home/cris/Documents/0_Projects/uarchs_paper/LPC55S69_DMA_Covert_Channel/src/lpcxpresso55s69_hello_world_ns/startup" -I"/home/cris/Documents/0_Projects/uarchs_paper/LPC55S69_DMA_Covert_Channel/src/lpcxpresso55s69_hello_world_ns/component/uart" -I"/home/cris/Documents/0_Projects/uarchs_paper/LPC55S69_DMA_Covert_Channel/src/lpcxpresso55s69_hello_world_ns/component/lists" -I"/home/cris/Documents/0_Projects/uarchs_paper/LPC55S69_DMA_Covert_Channel/src/lpcxpresso55s69_hello_world_ns/CMSIS" -I"/home/cris/Documents/0_Projects/uarchs_paper/LPC55S69_DMA_Covert_Channel/src/lpcxpresso55s69_hello_world_ns/board" -I"/home/cris/Documents/0_Projects/uarchs_paper/LPC55S69_DMA_Covert_Channel/src/lpcxpresso55s69_hello_world_ns/trustzone" -O0 -fno-common -g3 -D __SEMIHOST_HARDFAULT_DISABLE -mcpu=cortex-m33 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-drivers

clean-drivers:
	-$(RM) ./drivers/fsl_clock.d ./drivers/fsl_clock.o ./drivers/fsl_common.d ./drivers/fsl_common.o ./drivers/fsl_common_arm.d ./drivers/fsl_common_arm.o ./drivers/fsl_dma.d ./drivers/fsl_dma.o ./drivers/fsl_flexcomm.d ./drivers/fsl_flexcomm.o ./drivers/fsl_gpio.d ./drivers/fsl_gpio.o ./drivers/fsl_i2c.d ./drivers/fsl_i2c.o ./drivers/fsl_power.d ./drivers/fsl_power.o ./drivers/fsl_reset.d ./drivers/fsl_reset.o ./drivers/fsl_usart.d ./drivers/fsl_usart.o

.PHONY: clean-drivers

