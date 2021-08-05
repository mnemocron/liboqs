# SPDX-License-Identifier: MIT

# arm-none-eabi-gcc "../Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal.c" 
# -mcpu=cortex-m7
# -std=gnu11
# -g3
# -DDEBUG
# -DUSE_HAL_DRIVER
# -DSTM32F746xx
# -c
# -I../Core/Inc
# -I../Drivers/STM32F7xx_HAL_Driver/Inc
# -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy
# -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include
# -I../Drivers/CMSIS/Include
# -I../Middlewares/Third_Party/liboqs/src
# -O0
# -ffunction-sections
# -fdata-sections
# -Wall
# -fstack-usage
# -MMD
# -MP
# -MF"Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal.d"
# -MT"Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal.o"
# --specs=nano.specs
# -mfpu=fpv5-sp-d16
# -mfloat-abi=hard
# -mthumb
# -o "Drivers/STM32F7xx_HAL_Driver/Src/stm32f7xx_hal.o"

# set(CMAKE_SYSTEM_NAME FreeRTOS)
set(CMAKE_SYSTEM_PROCESSOR cortex-m7)
set(CMAKE_CROSSCOMPILING ON)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_FORCE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_C_COMPILER_WORKS 1)
add_compile_options(--specs=nano.specs)
#add_compile_options(--specs=nosys.specs)
add_compile_options(-mcpu=cortex-m7)
add_compile_options(-g3)
add_compile_options(-DSTM32F746xx)
add_compile_options(-O0)
add_compile_options(-ffunction-sections)
add_compile_options(-fdata-sections)
add_compile_options(-Wall)
add_compile_options(-fstack-usage)
add_compile_options(-MMD)
add_compile_options(-MP)
add_compile_options(-mfpu=fpv5-sp-d16)
#add_compile_options(-mfloat-abi=hard)
add_compile_options(-mfloat-abi=soft)
add_compile_options(-mthumb)

#set(CMAKE_CROSSCOMPILING_EMULATOR "qemu-aarch64-static;-L;/usr/aarch64-linux-gnu/")
