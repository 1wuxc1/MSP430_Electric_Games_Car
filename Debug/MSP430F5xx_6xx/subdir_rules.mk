################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
MSP430F5xx_6xx/%.obj: ../MSP430F5xx_6xx/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"D:/software/TI_CCS/an_zhaung/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="D:/software/TI_CCS/an_zhaung/ccs/ccs_base/msp430/include" --include_path="D:/qian_ru/MSP430/Project_dian_sai_Car" --include_path="D:/software/TI_CCS/an_zhaung/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/include" --include_path="D:/qian_ru/MSP430/Project_dian_sai_Car/BSP" --include_path="D:/qian_ru/MSP430/Project_dian_sai_Car/HARDWARE" --advice:power="all" --define=__MSP430F5529__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="MSP430F5xx_6xx/$(basename $(<F)).d_raw" --obj_directory="MSP430F5xx_6xx" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


