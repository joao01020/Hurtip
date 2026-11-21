
cmake_minimum_required(VERSION 3.16)

project(Hurtip
    VERSION 0.1.0
    DESCRIPTION "Hurtip Programming Language"
    LANGUAGES CXX
)

# Exportar comandos de compilação para o IntelliSense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Configuração do C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Executável principal
add_executable(hurtip
    src/main.cpp
    src/lexer/lexer.cpp
    src/parser/parser.cpp
    src/interpreter/interpreter.cpp
    src/interpreter/interpreter_expressions.cpp
    src/environment/environment.cpp
    src/libraries/math.cpp
    src/libraries/standard_library.cpp
)

# Diretórios de cabeçalhos
target_include_directories(hurtip
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

# Avisos de compilação
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

# Sistema de testes
include(CTest)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
