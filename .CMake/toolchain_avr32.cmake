# SPDX-License-Identifier: MIT

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR avr)
set(CMAKE_CROSSCOMPILING ON)

set(CMAKE_C_COMPILER avr32-gcc)
set(CMAKE_CXX_COMPILER avr32-g++)
set(CMAKE_ASM_COMPILER avr32-gcc)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

#set(CMAKE_C_COMPILER_WORKS 1) # force override initial compiler test
#add_compile_options(--specs=nano.specs)



#set(CMAKE_CROSSCOMPILING_EMULATOR "qemu-aarch64-static;-L;/usr/aarch64-linux-gnu/")
