################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../component/uart/fsl_adapter_usart.c 

C_DEPS += \
./component/uart/fsl_adapter_usart.d 

OBJS += \
./component/uart/fsl_adapter_usart.o 


# Each subdirectory must supply rules for building sources it contributes
component/uart/%.o: ../component/uart/%.c component/uart/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -DCPU_LPC55S69JBD100_cm33_core0 -DMCUXPRESSO_SDK -DCPU_LPC55S69JBD100 -DCPU_LPC55S69JBD100_cm33 -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -I"/home/cris/Documents/0_Projects/uarchs_paper/LPC55S69_DMA_Covert_Channel/src/lpcxpresso55s69_hello_world_s/source" -I"/home/cris/Documents/0_Projects/uarchs_paper/LPC55S69_DMA_Covert_Channel/src/lpcxpresso55s69_hello_world_s/utilities" -I"/home/cris/Documents/0_Projects/uarchs_paper/LPC55S69_DMA_Covert_Channel/src/lpcxpresso55s69_hello_world_s/drivers" -I"/home/cris/Documents/0_Projects/uarchs_paper/LPC55S69_DMA_Covert_Channel/src/lpcxpresso55s69_hello_world_s/device" -I"/home/cris/Documents/0_Projects/uarchs_paper/LPC55S69_DMA_Covert_Channel/src/lpcxpresso55s69_hello_world_s/startup" -I"/home/cris/Documents/0_Projects/uarchs_paper/LPC55S69_DMA_Covert_Channel/src/lpcxpresso55s69_hello_world_s/component/uart" -I"/home/cris/Documents/0_Projects/uarchs_paper/LPC55S69_DMA_Covert_Channel/src/lpcxpresso55s69_hello_world_s/component/lists" -I"/home/cris/Documents/0_Projects/uarchs_paper/LPC55S69_DMA_Covert_Channel/src/lpcxpresso55s69_hello_world_s/CMSIS" -I"/home/cris/Documents/0_Projects/uarchs_paper/LPC55S69_DMA_Covert_Channel/src/lpcxpresso55s69_hello_world_s/board" -I"/home/cris/Documents/0_Projects/uarchs_paper/LPC55S69_DMA_Covert_Channel/src/lpcxpresso55s69_hello_world_s/trustzone" -O0 -fno-common -g3 -mcpu=cortex-m33 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -mcmse -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-component-2f-uart

clean-component-2f-uart:
	-$(RM) ./component/uart/fsl_adapter_usart.d ./component/uart/fsl_adapter_usart.o

.PHONY: clean-component-2f-uart

