cmake_minimum_required(VERSION 3.13)

set(PRJ_NAME pico_fw)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()

set(PICO_SDK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/pico-sdk)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(PRJ_NAME C CXX ASM)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()


add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        -Wno-maybe-uninitialized
        )

add_subdirectory(src)