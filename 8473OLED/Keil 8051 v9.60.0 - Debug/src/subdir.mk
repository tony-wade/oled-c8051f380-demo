################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
A51_UPPER_SRCS += \
C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/SILABS_STARTUP.A51 

C_SRCS += \
../src/8473OLED_main.c \
../src/button.c \
../src/spi_oled_8473.c \
../src/system_init.c \
../src/test_image.c \
../src/timer.c 

OBJS += \
./src/8473OLED_main.OBJ \
./src/SILABS_STARTUP.OBJ \
./src/button.OBJ \
./src/spi_oled_8473.OBJ \
./src/system_init.OBJ \
./src/test_image.OBJ \
./src/timer.OBJ 


# Each subdirectory must supply rules for building sources it contributes
src/%.OBJ: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Keil 8051 Compiler'
	C51 "@$(patsubst %.OBJ,%.__i,$@)" || $(RC)
	@echo 'Finished building: $<'
	@echo ' '

src/8473OLED_main.OBJ: C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/C8051F380/inc/SI_C8051F380_Register_Enums.h C:/Users/User/Desktop/OLED/F380_OLED/8473OLED/src/system_init.h C:/Users/User/Desktop/OLED/F380_OLED/8473OLED/src/button.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/C8051F380/inc/SI_C8051F380_Defs.h C:/Users/User/Desktop/OLED/F380_OLED/8473OLED/src/timer.h C:/Users/User/Desktop/OLED/F380_OLED/8473OLED/src/spi_oled_8473.h C:/Users/User/Desktop/OLED/F380_OLED/8473OLED/src/test_image.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/stdbool.h

src/SILABS_STARTUP.OBJ: C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/SILABS_STARTUP.A51 src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Keil 8051 Assembler'
	AX51 "@$(patsubst %.OBJ,%.__ia,$@)" || $(RC)
	@echo 'Finished building: $<'
	@echo ' '

src/button.OBJ: C:/Users/User/Desktop/OLED/F380_OLED/8473OLED/src/button.h C:/Users/User/Desktop/OLED/F380_OLED/8473OLED/src/system_init.h C:/Users/User/Desktop/OLED/F380_OLED/8473OLED/src/timer.h C:/Users/User/Desktop/OLED/F380_OLED/8473OLED/src/spi_oled_8473.h C:/Users/User/Desktop/OLED/F380_OLED/8473OLED/src/test_image.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/C8051F380/inc/SI_C8051F380_Register_Enums.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/C8051F380/inc/SI_C8051F380_Defs.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/stdbool.h

src/spi_oled_8473.OBJ: C:/Users/User/Desktop/OLED/F380_OLED/8473OLED/src/spi_oled_8473.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/C8051F380/inc/SI_C8051F380_Register_Enums.h C:/Users/User/Desktop/OLED/F380_OLED/8473OLED/src/system_init.h C:/Users/User/Desktop/OLED/F380_OLED/8473OLED/src/timer.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/C8051F380/inc/SI_C8051F380_Defs.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/stdbool.h

src/system_init.OBJ: C:/Users/User/Desktop/OLED/F380_OLED/8473OLED/src/system_init.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/C8051F380/inc/SI_C8051F380_Register_Enums.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/C8051F380/inc/SI_C8051F380_Defs.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/stdbool.h

src/test_image.OBJ: C:/Users/User/Desktop/OLED/F380_OLED/8473OLED/src/test_image.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/stdint.h

src/timer.OBJ: C:/Users/User/Desktop/OLED/F380_OLED/8473OLED/src/timer.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/C8051F380/inc/SI_C8051F380_Register_Enums.h C:/Users/User/Desktop/OLED/F380_OLED/8473OLED/src/system_init.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/C8051F380/inc/SI_C8051F380_Defs.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/stdbool.h


