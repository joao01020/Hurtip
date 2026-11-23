#!/usr/bin/env bash

set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="$ROOT_DIR/build"
HURTIP_BIN="$BUILD_DIR/hurtip"

JOBS="$(getconf _NPROCESSORS_ONLN 2>/dev/null || echo 2)"

show_help() {
    echo "Hurtip Development Tools"
    echo
    echo "Usage: ./dev.sh <command>"
    echo
    echo "Commands:"
    echo "  build              Configure and compile the project"
    echo "  test               Build and run all tests"
    echo "  run <file>         Execute a Hurtip source file"
    echo "  clean              Remove build files"
    echo "  rebuild            Clean and build the project"
    echo "  help               Show this help message"
}

configure() {
    cmake -S "$ROOT_DIR" -B "$BUILD_DIR"
}

build() {
    echo "Configuring Hurtip..."
    configure

    echo
    echo "Building Hurtip..."
    cmake --build "$BUILD_DIR" -j"$JOBS"
}

test() {
    build

    echo
    echo "Running tests..."
    ctest --test-dir "$BUILD_DIR" --output-on-failure
}

run() {
    if [[ $# -eq 0 ]]; then
        echo "Error: Please provide a .hurtip file."
        echo "Usage: ./dev.sh run examples/main.hurtip"
        exit 1
    fi

    if [[ ! -x "$HURTIP_BIN" ]]; then
        echo "Error: Hurtip is not compiled."
        echo "Run './dev.sh build' first."
        exit 1
    fi

    exec "$HURTIP_BIN" "$@"
}

clean() {
    echo "Cleaning build directory..."
    rm -rf "$BUILD_DIR"
    echo "Build directory removed."
}

case "${1:-help}" in
    build)
        build
        ;;
    test)
        test 
        ;;
    run)
        shift
        run "$@"
        ;;
    clean)
        clean
        ;;
    rebuild)
        clean
        build
        ;;
    help|--help|-h)
        show_help
        ;;
    *)
        echo "Unknown command: $1"
        echo
        show_help
        exit 1
        ;;
esac
