################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
RCCA_HW.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
RCCA_HW.list \

OBJCOPY_BIN += \
RCCA_HW.bin \


# All Target
all: RCCA_HW.elf secondary-outputs

# Tool invocations
RCCA_HW.elf: $(OBJS) $(USER_OBJS) C:\Users\Andrew\ Kwok\Senior-Project-RCCA\Senior-Project-RCCA\Senior-Project-RCCA\Senior\ Project\RCCA\ HW\STM32F429ZITX_FLASH.ld
	arm-none-eabi-gcc -o "RCCA_HW.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\Andrew Kwok\Senior-Project-RCCA\Senior-Project-RCCA\Senior-Project-RCCA\Senior Project\RCCA HW\STM32F429ZITX_FLASH.ld" --specs=nosys.specs -Wl,-Map="RCCA_HW.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

RCCA_HW.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "RCCA_HW.list"
	@echo 'Finished building: $@'
	@echo ' '

RCCA_HW.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "RCCA_HW.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
