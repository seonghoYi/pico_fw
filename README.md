# pico_fw
## CMAKE 설정

cmake -S . -B build -G "Unix Makefiles" -DPICO_BOARD=pico 또는

cmake -S . -B build -G "MinGW Makefiles" -DPICO_BOARD=pico 등...



## CMAKE 빌드

cmake --build build -jx
