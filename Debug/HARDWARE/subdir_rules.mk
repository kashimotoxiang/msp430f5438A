################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
HARDWARE/LDC1000_cmd.obj: ../HARDWARE/LDC1000_cmd.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_15.12.1.LTS/bin/cl430" -vmspx --data_model=restricted -O3 --opt_for_speed=5 --use_hw_mpy=none --include_path="C:/ti/ccsv6/ccs_base/msp430/include" --include_path="D:/Documents/workspace/TIM4/msp430f5438A/HARDWARE" --include_path="D:/Documents/workspace/TIM4/msp430f5438A/SOFTWARE" --include_path="D:/Documents/workspace/TIM4/msp430f5438A/OLED" --include_path="D:/Documents/workspace/TIM4/msp430f5438A/INCSCREEN" --include_path="D:/Documents/workspace/TIM4/msp430f5438A" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_15.12.1.LTS/include" --advice:power="all" -g --define=__MSP430F5438A__ --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --printf_support=full --preproc_with_compile --preproc_dependency="HARDWARE/LDC1000_cmd.d" --obj_directory="HARDWARE" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

HARDWARE/myADC.obj: ../HARDWARE/myADC.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_15.12.1.LTS/bin/cl430" -vmspx --data_model=restricted -O3 --opt_for_speed=5 --use_hw_mpy=none --include_path="C:/ti/ccsv6/ccs_base/msp430/include" --include_path="D:/Documents/workspace/TIM4/msp430f5438A/HARDWARE" --include_path="D:/Documents/workspace/TIM4/msp430f5438A/SOFTWARE" --include_path="D:/Documents/workspace/TIM4/msp430f5438A/OLED" --include_path="D:/Documents/workspace/TIM4/msp430f5438A/INCSCREEN" --include_path="D:/Documents/workspace/TIM4/msp430f5438A" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_15.12.1.LTS/include" --advice:power="all" -g --define=__MSP430F5438A__ --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --printf_support=full --preproc_with_compile --preproc_dependency="HARDWARE/myADC.d" --obj_directory="HARDWARE" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

HARDWARE/myIIC.obj: ../HARDWARE/myIIC.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_15.12.1.LTS/bin/cl430" -vmspx --data_model=restricted -O3 --opt_for_speed=5 --use_hw_mpy=none --include_path="C:/ti/ccsv6/ccs_base/msp430/include" --include_path="D:/Documents/workspace/TIM4/msp430f5438A/HARDWARE" --include_path="D:/Documents/workspace/TIM4/msp430f5438A/SOFTWARE" --include_path="D:/Documents/workspace/TIM4/msp430f5438A/OLED" --include_path="D:/Documents/workspace/TIM4/msp430f5438A/INCSCREEN" --include_path="D:/Documents/workspace/TIM4/msp430f5438A" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_15.12.1.LTS/include" --advice:power="all" -g --define=__MSP430F5438A__ --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --printf_support=full --preproc_with_compile --preproc_dependency="HARDWARE/myIIC.d" --obj_directory="HARDWARE" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

HARDWARE/myKey.obj: ../HARDWARE/myKey.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_15.12.1.LTS/bin/cl430" -vmspx --data_model=restricted -O3 --opt_for_speed=5 --use_hw_mpy=none --include_path="C:/ti/ccsv6/ccs_base/msp430/include" --include_path="D:/Documents/workspace/TIM4/msp430f5438A/HARDWARE" --include_path="D:/Documents/workspace/TIM4/msp430f5438A/SOFTWARE" --include_path="D:/Documents/workspace/TIM4/msp430f5438A/OLED" --include_path="D:/Documents/workspace/TIM4/msp430f5438A/INCSCREEN" --include_path="D:/Documents/workspace/TIM4/msp430f5438A" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_15.12.1.LTS/include" --advice:power="all" -g --define=__MSP430F5438A__ --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --printf_support=full --preproc_with_compile --preproc_dependency="HARDWARE/myKey.d" --obj_directory="HARDWARE" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

HARDWARE/mySPI.obj: ../HARDWARE/mySPI.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_15.12.1.LTS/bin/cl430" -vmspx --data_model=restricted -O3 --opt_for_speed=5 --use_hw_mpy=none --include_path="C:/ti/ccsv6/ccs_base/msp430/include" --include_path="D:/Documents/workspace/TIM4/msp430f5438A/HARDWARE" --include_path="D:/Documents/workspace/TIM4/msp430f5438A/SOFTWARE" --include_path="D:/Documents/workspace/TIM4/msp430f5438A/OLED" --include_path="D:/Documents/workspace/TIM4/msp430f5438A/INCSCREEN" --include_path="D:/Documents/workspace/TIM4/msp430f5438A" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_15.12.1.LTS/include" --advice:power="all" -g --define=__MSP430F5438A__ --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --printf_support=full --preproc_with_compile --preproc_dependency="HARDWARE/mySPI.d" --obj_directory="HARDWARE" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

HARDWARE/myTimer.obj: ../HARDWARE/myTimer.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_15.12.1.LTS/bin/cl430" -vmspx --data_model=restricted -O3 --opt_for_speed=5 --use_hw_mpy=none --include_path="C:/ti/ccsv6/ccs_base/msp430/include" --include_path="D:/Documents/workspace/TIM4/msp430f5438A/HARDWARE" --include_path="D:/Documents/workspace/TIM4/msp430f5438A/SOFTWARE" --include_path="D:/Documents/workspace/TIM4/msp430f5438A/OLED" --include_path="D:/Documents/workspace/TIM4/msp430f5438A/INCSCREEN" --include_path="D:/Documents/workspace/TIM4/msp430f5438A" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_15.12.1.LTS/include" --advice:power="all" -g --define=__MSP430F5438A__ --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --printf_support=full --preproc_with_compile --preproc_dependency="HARDWARE/myTimer.d" --obj_directory="HARDWARE" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

HARDWARE/myUART.obj: ../HARDWARE/myUART.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_15.12.1.LTS/bin/cl430" -vmspx --data_model=restricted -O3 --opt_for_speed=5 --use_hw_mpy=none --include_path="C:/ti/ccsv6/ccs_base/msp430/include" --include_path="D:/Documents/workspace/TIM4/msp430f5438A/HARDWARE" --include_path="D:/Documents/workspace/TIM4/msp430f5438A/SOFTWARE" --include_path="D:/Documents/workspace/TIM4/msp430f5438A/OLED" --include_path="D:/Documents/workspace/TIM4/msp430f5438A/INCSCREEN" --include_path="D:/Documents/workspace/TIM4/msp430f5438A" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_15.12.1.LTS/include" --advice:power="all" -g --define=__MSP430F5438A__ --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --printf_support=full --preproc_with_compile --preproc_dependency="HARDWARE/myUART.d" --obj_directory="HARDWARE" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


