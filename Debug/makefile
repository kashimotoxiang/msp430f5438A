################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_15.12.1.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./main.obj" \
"./HARDWARE/LDC1000_cmd.obj" \
"./HARDWARE/myADC.obj" \
"./HARDWARE/myIIC.obj" \
"./HARDWARE/myKey.obj" \
"./HARDWARE/mySPI.obj" \
"./HARDWARE/myTimer.obj" \
"./HARDWARE/myUART.obj" \
"./INCSCREEN/Display_EPD_W21.obj" \
"./INCSCREEN/Display_EPD_W21_Aux.obj" \
"./INCSCREEN/I2C_IncSreen.obj" \
"./OLED/I2C_OLED.obj" \
"./SOFTWARE/24_32yang.obj" \
"./SOFTWARE/KeyBroad.obj" \
"./SOFTWARE/System.obj" \
"./SOFTWARE/Usual.obj" \
"./SOFTWARE/codetab.obj" \
"../lnk_msp430f5438a.cmd" \
$(GEN_CMDS__FLAG) \
-llibmath.a \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include HARDWARE/subdir_vars.mk
-include INCSCREEN/subdir_vars.mk
-include OLED/subdir_vars.mk
-include SOFTWARE/subdir_vars.mk
-include subdir_rules.mk
-include HARDWARE/subdir_rules.mk
-include INCSCREEN/subdir_rules.mk
-include OLED/subdir_rules.mk
-include SOFTWARE/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
msp430f5438A.out \

EXE_OUTPUTS__QUOTED += \
"msp430f5438A.out" \

BIN_OUTPUTS += \
msp430f5438A.hex \

BIN_OUTPUTS__QUOTED += \
"msp430f5438A.hex" \


# All Target
all: msp430f5438A.out

# Tool invocations
msp430f5438A.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: MSP430 Linker'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_15.12.1.LTS/bin/cl430" -vmspx --data_model=restricted -O3 --opt_for_speed=5 --use_hw_mpy=none --advice:power="all" -g --define=__MSP430F5438A__ --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --printf_support=full -z -m"msp430f5438A.map" --heap_size=1000 --stack_size=2000 --cinit_hold_wdt=on -i"C:/ti/ccsv6/ccs_base/msp430/include" -i"C:/ti/ccsv6/ccs_base/msp430/lib/5xx_6xx_FRxx" -i"C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_15.12.1.LTS/lib" -i"C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_15.12.1.LTS/include" --reread_libs --display_error_number --warn_sections --diag_wrap=off --xml_link_info="msp430f5438A_linkInfo.xml" --use_hw_mpy=F5 --rom_model -o "msp430f5438A.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

msp430f5438A.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: MSP430 Hex Utility'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_15.12.1.LTS/bin/hex430" --memwidth=8 --romwidth=8 -o "msp430f5438A.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "main.d" "HARDWARE\LDC1000_cmd.d" "HARDWARE\myADC.d" "HARDWARE\myIIC.d" "HARDWARE\myKey.d" "HARDWARE\mySPI.d" "HARDWARE\myTimer.d" "HARDWARE\myUART.d" "INCSCREEN\Display_EPD_W21.d" "INCSCREEN\Display_EPD_W21_Aux.d" "INCSCREEN\I2C_IncSreen.d" "OLED\I2C_OLED.d" "SOFTWARE\24_32yang.d" "SOFTWARE\KeyBroad.d" "SOFTWARE\System.d" "SOFTWARE\Usual.d" "SOFTWARE\codetab.d" 
	-$(RM) "main.obj" "HARDWARE\LDC1000_cmd.obj" "HARDWARE\myADC.obj" "HARDWARE\myIIC.obj" "HARDWARE\myKey.obj" "HARDWARE\mySPI.obj" "HARDWARE\myTimer.obj" "HARDWARE\myUART.obj" "INCSCREEN\Display_EPD_W21.obj" "INCSCREEN\Display_EPD_W21_Aux.obj" "INCSCREEN\I2C_IncSreen.obj" "OLED\I2C_OLED.obj" "SOFTWARE\24_32yang.obj" "SOFTWARE\KeyBroad.obj" "SOFTWARE\System.obj" "SOFTWARE\Usual.obj" "SOFTWARE\codetab.obj" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

