# Compilação da Hurtip

Este documento explica como configurar, compilar, testar e executar a Hurtip.

## Requisitos

- Git
- CMake 3.21 ou superior
- Compilador compatível com C++17
- Make ou outro gerador compatível com CMake

## Linux (Ubuntu/Debian)

Instale as dependências:

    sudo apt update
    sudo apt install build-essential cmake git

Clone o repositório:

    git clone https://github.com/joao01020/Hurtip.git
    cd Hurtip

Configure:

    cmake -S . -B build

Compile:

    cmake --build build -j$(nproc)

Execute os testes:

    ctest --test-dir build --output-on-failure

Execute um programa:

    ./build/hurtip examples/main.hurtip

## Windows

Instale Git, CMake e Visual Studio com suporte a C++.

Clone o repositório:

    git clone https://github.com/joao01020/Hurtip.git
    cd Hurtip

Configure e compile:

    cmake -S . -B build
    cmake --build build --config Release

Execute os testes:

    ctest --test-dir build -C Release --output-on-failure

O caminho do executável depende do gerador do CMake utilizado.

## macOS

Instale as ferramentas de desenvolvimento:

    xcode-select --install

Instale o CMake pelo Homebrew:

    brew install cmake

Clone, configure e compile:

    git clone https://github.com/joao01020/Hurtip.git
    cd Hurtip
    cmake -S . -B build
    cmake --build build --parallel

Execute os testes:

    ctest --test-dir build --output-on-failure

## Script de desenvolvimento

No Linux e macOS, também é possível utilizar o script dev.sh:

    ./dev.sh build
    ./dev.sh test
    ./dev.sh run examples/main.hurtip

## Limpeza

Para remover os arquivos de compilação:

    cmake -E rm -rf build

## Problemas

Se encontrar problemas, verifique as versões das ferramentas, consulte as Issues existentes e, se necessário, abra um relatório de erro no GitHub.

A Hurtip é experimental e seus procedimentos podem mudar durante o desenvolvimento.
