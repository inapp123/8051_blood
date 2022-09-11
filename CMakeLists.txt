cmake_minimum_required(VERSION 3.16)
set(CMAKE_TOOLCHAIN_FILE "toolchain.cmake")

project("8051")


function(ihx_to_hex bin)
    add_custom_command(TARGET ${bin} POST_BUILD COMMAND  packihx ${bin}.ihx > ${bin}.hex)
endfunction(ihx_to_hex)

include_directories(".")

file(GLOB blood_src CONFIGURE_DEPENDS 
    "*.h" 
    "*.c"
)

add_executable(${PROJECT_NAME} ${blood_src})
ihx_to_hex(${PROJECT_NAME})