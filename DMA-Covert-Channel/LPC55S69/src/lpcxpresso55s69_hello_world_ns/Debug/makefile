################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include utilities/subdir.mk
-include startup/subdir.mk
-include source/subdir.mk
-include drivers/subdir.mk
-include device/subdir.mk
-include component/uart/subdir.mk
-include component/serial_manager/subdir.mk
-include component/lists/subdir.mk
-include board/subdir.mk
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := lpcxpresso55s69_hello_world_ns
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: lpcxpresso55s69_hello_world_ns.axf

# Tool invocations
lpcxpresso55s69_hello_world_ns.axf: $(OBJS) $(USER_OBJS) makefile $(OPTIONAL_TOOL_DEPS) /home/cris/Documents/0_Projects/uarchs_paper/LPC55S69_DMA_Covert_Channel/src/lpcxpresso55s69_hello_world_s/Debug/lpcxpresso55s69_hello_world_s_CMSE_lib.o
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -Map="lpcxpresso55s69_hello_world_ns.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -Xlinker --sort-section=alignment -Xlinker --cref -mcpu=cortex-m33 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -T lpcxpresso55s69_hello_world_ns_Debug.ld -o "lpcxpresso55s69_hello_world_ns.axf" $(OBJS) $(USER_OBJS) $(LIBS) "/home/cris/Documents/0_Projects/uarchs_paper/LPC55S69_DMA_Covert_Channel/src/lpcxpresso55s69_hello_world_s/Debug/lpcxpresso55s69_hello_world_s_CMSE_lib.o"
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) lpcxpresso55s69_hello_world_ns.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "lpcxpresso55s69_hello_world_ns.axf"; # arm-none-eabi-objcopy -v -O binary "lpcxpresso55s69_hello_world_ns.axf" "lpcxpresso55s69_hello_world_ns.bin" ; # checksum -p LPC55S69 -d "lpcxpresso55s69_hello_world_ns.bin";
	-@echo ' '

.PHONY: all clean dependents main-build post-build

-include ../makefile.targets
