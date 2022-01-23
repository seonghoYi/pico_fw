add_executable(${PRJ_NAME}
  main.c
  
  ap/ap.c
  bsp/bsp.c
  common/core/qbuffer.c
  hw/hw.c

  
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

)


pico_add_extra_outputs(${PRJ_NAME})