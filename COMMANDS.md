# Hurtip — Development Commands

This document contains the main terminal commands used to build, test, run and
maintain the Hurtip programming language.

## 1. Build

Configure the project with CMake:

```bash
cmake -S . -B build
```

Compile the project:

```bash
cmake --build build -j$(nproc)
```

## 2. Run

Execute a Hurtip source file:

```bash
./build/hurtip examples/main.hurtip
```

Execute a mathematics example:

```bash
./build/hurtip examples/mathematics/complex_numbers.hurtip
```

## 3. Tests

Run all registered tests:

```bash
ctest --test-dir build --output-on-failure
```

Run a specific test executable or script:

```bash
./build/hurtip tests/path/to/test.hurtip
```

## 4. Clean

Remove the build directory:

```bash
rm -rf build
```

Configure and compile again:

```bash
cmake -S . -B build
cmake --build build -j$(nproc)
```

## 5. Development Script

Use the development helper script:

```bash
./dev.sh build
./dev.sh test
./dev.sh run examples/main.hurtip
./dev.sh clean
./dev.sh rebuild
./dev.sh help
```

## Requirements

- CMake
- C++ compiler
- CTest
- GNU Make or another supported CMake generator
