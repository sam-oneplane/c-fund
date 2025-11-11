cmake_minimum_required(VERSION 3.16)
project(MyClassLib C)

# Require C11
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Include directory
include_directories(${CMAKE_SOURCE_DIR})

# Library target (can be static or shared)
add_library(MyClass STATIC
    src/class.c
    src/class_rc.c
)

# Main executable
add_executable(main
    main.c
)

# Link executable to library
target_link_libraries(main PRIVATE MyClass)

# Optional: add extra warnings
target_compile_options(MyClass PRIVATE -Wall -Wextra -pedantic)
target_compile_options(main PRIVATE -Wall -Wextra -pedantic)