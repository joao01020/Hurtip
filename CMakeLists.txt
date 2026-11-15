
cmake_minimum_required(VERSION 3.16)

project(Netuno
    VERSION 0.1.0
    DESCRIPTION "Netuno Programming Language"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(netuno
    src/main.cpp
    src/lexer.cpp
    src/parser.cpp
    src/interpreter.cpp
)

target_include_directories(netuno
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

if(MSVC)
    target_compile_options(netuno PRIVATE /W4)
else()
    target_compile_options(netuno PRIVATE -Wall -Wextra -Wpedantic)
endif()


# Netuno visual assets
install(
    DIRECTORY ${PROJECT_SOURCE_DIR}/assets/
    DESTINATION share/netuno/assets
)