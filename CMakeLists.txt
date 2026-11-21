
cmake_minimum_required(VERSION 3.16)

project(Hurtip
    VERSION 0.1.0
    DESCRIPTION "Hurtip Programming Language"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(hurtip
    src/main.cpp
    src/lexer/lexer.cpp
    src/parser/parser.cpp
    src/interpreter/interpreter.cpp
    src/interpreter/interpreter_expressions.cpp
)

target_include_directories(hurtip
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

if(MSVC)
    target_compile_options(hurtip PRIVATE /W4)
else()
    target_compile_options(hurtip PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Recursos visuais da Hurtip

install(
    DIRECTORY ${PROJECT_SOURCE_DIR}/assets/
    DESTINATION share/hurtip/assets
)
