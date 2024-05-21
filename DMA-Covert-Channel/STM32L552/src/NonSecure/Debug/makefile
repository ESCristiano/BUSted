################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32L5xx_HAL_Driver/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := STM32L552_Covert_Channel_NonSecure
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
STM32L552_Covert_Channel_NonSecure.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
STM32L552_Covert_Channel_NonSecure.list \

OBJCOPY_BIN += \
STM32L552_Covert_Channel_NonSecure.bin \


# All Target
all: main-build

# Main-build Target
main-build: STM32L552_Covert_Channel_NonSecure.elf secondary-outputs

dependents:
	-cd C:/Users/cris9/OneDrive/Documentos/0_Projects/uArchs_Paper/STM32L552_DMA_Covert_Channel/src/Secure/Debug && $(MAKE) clean all

# Tool invocations
STM32L552_Covert_Channel_NonSecure.elf: $(OBJS) $(USER_OBJS) C:/Users/cris9/OneDrive/Documentos/0_Projects/uArchs_Paper/STM32L552_DMA_Covert_Channel/src/Secure/Debug/STM32L552_Covert_Channel_Secure.elf C:\Users\cris9\OneDrive\Documentos\0_Projects\uArchs_Paper\STM32L552_DMA_Covert_Channel\src\NonSecure\STM32L562ZETXQ_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "STM32L552_Covert_Channel_NonSecure.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m33 -T"C:\Users\cris9\OneDrive\Documentos\0_Projects\uArchs_Paper\STM32L552_DMA_Covert_Channel\src\NonSecure\STM32L562ZETXQ_FLASH.ld" --specs=nosys.specs -Wl,-Map="STM32L552_Covert_Channel_NonSecure.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

STM32L552_Covert_Channel_NonSecure.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "STM32L552_Covert_Channel_NonSecure.list"
	@echo 'Finished building: $@'
	@echo ' '

STM32L552_Covert_Channel_NonSecure.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "STM32L552_Covert_Channel_NonSecure.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) STM32L552_Covert_Channel_NonSecure.bin STM32L552_Covert_Channel_NonSecure.elf STM32L552_Covert_Channel_NonSecure.list default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified
C:/Users/cris9/OneDrive/Documentos/0_Projects/uArchs_Paper/STM32L552_DMA_Covert_Channel/src/Secure/Debug/STM32L552_Covert_Channel_Secure.elf:

-include ../makefile.targets
