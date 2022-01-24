add_executable(${PRJ_NAME}
  main.c
  
  ap/ap.c
  bsp/bsp.c
  common/core/qbuffer.c
  hw/hw.c
  hw/driver/uart.c
  

)


target_include_directories(${PRJ_NAME} PUBLIC
  ap
  bsp
  common
  common/core
  common/hw/include
  hw

)

target_link_libraries(${PRJ_NAME}
  pico_stdlib
  hardware_clocks
  hardware_pll
)


pico_add_extra_outputs(${PRJ_NAME})
pico_enable_stdio_usb(${PRJ_NAME}  1)
pico_enable_stdio_uart(${PRJ_NAME} 0)