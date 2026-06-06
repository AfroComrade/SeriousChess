cmake_minimum_required(VERSION 3.23)

project(
  MyGame
  VERSION 1.0
  DESCRIPTION "My first SDL3 Game"
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(
    CMAKE_RUNTIME_OUTPUT_DIRECTORY
    "${CMAKE_BINARY_DIR}/$<CONFIGURATION>"
)

set(
    CMAKE_LIBRARY_OUTPUT_DIRECTORY
    "${CMAKE_BINARY_DIR}/$<CONFIGURATION>"
)

set(SOURCES src/main.cpp src/Init/loaders.cpp src/Logic/GameLogic.cpp src/Render.cpp)

add_executable(MyGame
  ${SOURCES}
)

target_include_directories(MyGame PRIVATE 01_hello_SDL)

set(VENDOR_DIR "${PROJECT_SOURCE_DIR}/vendor") 

add_subdirectory(${VENDOR_DIR}/SDL)
add_subdirectory(${VENDOR_DIR}/SDL_image)
add_subdirectory(${VENDOR_DIR}/SDL_ttf)
add_subdirectory(${VENDOR_DIR}/SDL_mixer)

target_link_libraries(MyGame 
  SDL3::SDL3
  SDL3_image::SDL3_image
  SDL3_ttf::SDL3_ttf
  SDL3_mixer::SDL3_mixer
)

add_custom_target(copy_resources ALL  
    COMMAND ${CMAKE_COMMAND} -E copy_directory  
        ${PROJECT_SOURCE_DIR}/assets  
        ${CMAKE_BINARY_DIR}/assets  
    COMMENT "Copying assets to build"
)  
