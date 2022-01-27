add_executable(${PRJ_NAME}
  main.c
  
  ap/ap.c
  bsp/bsp.c
  common/core/qbuffer.c
  hw/hw.c
  hw/driver/uart.c
  hw/driver/i2c.c

  hw/driver/cli.c

  hw/driver/lcd/font.c
  hw/driver/lcd/ssd1306.c
  hw/driver/lcd.c 

)


target_include_directories(${PRJ_NAME} PUBLIC
  ap
  bsp
  common
  common/core
  common/hw/include
  hw
  hw/include/lcd

)

target_link_libraries(${PRJ_NAME}
  pico_stdlib
  hardware_clocks
  hardware_pll
  hardware_i2c
)


pico_add_extra_outputs(${PRJ_NAME})
pico_enable_stdio_usb(${PRJ_NAME}  1)
pico_enable_stdio_uart(${PRJ_NAME} 0)