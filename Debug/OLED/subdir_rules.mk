################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
OLED/I2C_OLED.obj: ../OLED/I2C_OLED.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_15.12.1.LTS/bin/cl430" -vmspx --data_model=restricted -Ooff --use_hw_mpy=F5 --include_path="C:/ti/ccsv6/ccs_base/msp430/include" --include_path="D:/Documents/workspace/TIM4/msp430f5438A/HARDWARE" --include_path="D:/Documents/workspace/TIM4/msp430f5438A/SOFTWARE" --include_path="D:/Documents/workspace/TIM4/msp430f5438A/OLED" --include_path="D:/Documents/workspace/TIM4/msp430f5438A/LIB" --include_path="D:/Documents/workspace/TIM4/msp430f5438A" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_15.12.1.LTS/include" --advice:power=all -g --define=__MSP430F5438A__ --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --printf_support=minimal --preproc_with_compile --preproc_dependency="OLED/I2C_OLED.d" --obj_directory="OLED" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


