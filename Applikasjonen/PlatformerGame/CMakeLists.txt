cmake_minimum_required(VERSION 3.21)
project(sdl3_image_wasm_test C)

set(CMAKE_C_STANDARD 11)

find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)

add_executable(game main.c)
target_link_libraries(game PRIVATE SDL3::SDL3 SDL3_image::SDL3_image-static)

set_target_properties(game PROPERTIES SUFFIX ".html")

# Embed all images in the virtual filesystem root
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --preload-file \"${CMAKE_SOURCE_DIR}/assets@assets\"")

# Fix OOM crash
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -sALLOW_MEMORY_GROWTH=1 -sINITIAL_MEMORY=32MB")