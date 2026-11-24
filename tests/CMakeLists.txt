
# Testes automatizados da Hurtip

set(HURTIP_TEST_RUNNER
    "${CMAKE_CURRENT_SOURCE_DIR}/run_test.cmake"
)

function(add_hurtip_success_test test_name source_file expected_output)
    add_test(
        NAME ${test_name}
        COMMAND
            ${CMAKE_COMMAND}
            "-DPROGRAM=$<TARGET_FILE:hurtip>"
            "-DSOURCE=${PROJECT_SOURCE_DIR}/${source_file}"
            "-DEXPECTED_OUTPUT=${expected_output}"
            "-DEXPECTED_ERROR="
            -P "${HURTIP_TEST_RUNNER}"
    )
endfunction()

function(add_hurtip_error_test test_name source_file expected_error)
    add_test(
        NAME ${test_name}
        COMMAND
            ${CMAKE_COMMAND}
            "-DPROGRAM=$<TARGET_FILE:hurtip>"
            "-DSOURCE=${PROJECT_SOURCE_DIR}/${source_file}"
            "-DEXPECTED_OUTPUT="
            "-DEXPECTED_ERROR=${expected_error}"
            -P "${HURTIP_TEST_RUNNER}"
    )
endfunction()

# Environment

add_hurtip_success_test(
    environment
    tests/environment/environment_test.hurtip
    [=[20
10
30]=]
)

# Functions

add_hurtip_success_test(
    nested_functions
    tests/functions/nested_functions_test.hurtip
    [=[30
30
10]=]
)

add_hurtip_success_test(
    recursion
    tests/functions/recursion_test.hurtip
    [=[120]=]
)

add_hurtip_success_test(
    recursion_scope
    tests/functions/recursion_scope_test.hurtip
    [=[15]=]
)

add_hurtip_success_test(
    module_system
    tests/modules/module_test.hurtip
    [=[30
60]=]
)

# Modules

add_hurtip_success_test(
    module_variable_isolation
    tests/modules/modules/isolation/isolation_test.hurtip
    [=[First
Second]=]
)


add_hurtip_success_test(
    module_state_persistence
    tests/modules/modules/state/state_test.hurtip
    [=[1
2
3]=]
)


add_hurtip_success_test(
    module_alias_shared_state
    tests/modules/modules/state/alias_test.hurtip
    [=[1
2
3]=]
)


add_hurtip_success_test(
    module_nested_loading
    tests/modules/modules/nested/nested_test.hurtip
    [=[15
50]=]
)


add_hurtip_error_test(
    module_circular_dependency
    tests/modules/modules/circular/circular_test.hurtip
    "Circular module dependency:"
)


add_hurtip_error_test(
    module_missing_dependency
    tests/modules/modules/errors/missing_dependency_test.hurtip
    "Could not open module:"
)
# Native imports

add_hurtip_success_test(
    math_import
    tests/import/math_import_test.hurtip
    [=[30]=]
)

add_hurtip_success_test(
    math_alias
    tests/import/math_alias_test.hurtip
    [=[30]=]
)

add_hurtip_error_test(
    unknown_import
    tests/import/unknown_import_test.hurtip
    "Unknown native library: unknown"
)

add_hurtip_error_test(
    unknown_native_function
    tests/import/unknown_function_test.hurtip
    "Unknown function 'subtract' in library 'math'"
)

add_hurtip_error_test(
    invalid_native_arguments
    tests/import/invalid_native_arguments_test.hurtip
    "Native function 'sum' failed: Function 'sum' expects exactly 2 arguments"
)

add_hurtip_error_test(
    invalid_native_types
    tests/import/invalid_native_types_test.hurtip
    "Native function 'sum' failed: Function 'sum' expects numeric arguments"
)

# Parser - successful programs

add_hurtip_success_test(
    parser_function_braces
    tests/parser/function_braces_test.hurtip
    [=[30]=]
)

add_hurtip_success_test(
    parser_braces
    tests/parser/parser_braces_test.hurtip
    [=[20
10]=]
)

add_hurtip_success_test(
    parser_while_braces
    tests/parser/while_braces_test.hurtip
    [=[0
1
2
3]=]
)

# Parser - expected errors

add_hurtip_error_test(
    parser_duplicate_operator
    tests/parser/parser_duplicate_operator_test.hurtip
    "Expected an expression"
)

add_hurtip_error_test(
    parser_incomplete_expression
    tests/parser/parser_incomplete_expression_test.hurtip
    "Expected an expression"
)

add_hurtip_error_test(
    parser_invalid_argument
    tests/parser/parser_invalid_argument_test.hurtip
    "Expected an expression"
)

add_hurtip_error_test(
    parser_invalid_block
    tests/parser/parser_invalid_block_test.hurtip
    "Expected '{' to begin block"
)

add_hurtip_error_test(
    parser_invalid_call
    tests/parser/parser_invalid_call_test.hurtip
    "Expected ')' after function arguments"
)

add_hurtip_error_test(
    parser_missing_brace
    tests/parser/parser_missing_brace_test.hurtip
    "Expected '}' to close block"
)

add_hurtip_error_test(
    parser_missing_parenthesis
    tests/parser/parser_missing_parenthesis_test.hurtip
    "Expected ')' after if condition"
)

add_hurtip_error_test(
    parser_trailing_comma
    tests/parser/parser_trailing_comma_test.hurtip
    "Expected an expression"
)

# Scopes

add_hurtip_success_test(
    block_assignment
    tests/scopes/block_assignment_test.hurtip
    [=[50
50]=]
)

add_hurtip_success_test(
    block_scope
    tests/scopes/block_scope_test.hurtip
    [=[20
10]=]
)

add_hurtip_success_test(
    else_scope
    tests/scopes/else_scope_test.hurtip
    [=[30
10]=]
)

add_hurtip_success_test(
    loop_control_scope
    tests/scopes/loop_control_scope_test.hurtip
    [=[10
12
4]=]
)

add_hurtip_success_test(
    while_scope
    tests/scopes/while_scope_test.hurtip
    [=[10
11
12
3]=]
)


# Arrays

add_hurtip_success_test(
    array_creation
    tests/arrays/array_creation_test.hurtip
    [=[[10, 20, 30]
[Ana, João, Maria]
[]]=]
)

add_hurtip_success_test(
    array_mixed
    tests/arrays/array_mixed_test.hurtip
    [=[[10, Hurtip, true, false]
10
Hurtip
true
false]=]
)

add_hurtip_success_test(
    array_nested
    tests/arrays/array_nested_test.hurtip
    [=[[[1, 2], [3, 4]]
[1, 2]
[3, 4]
1
4]=]
)

add_hurtip_success_test(
    array_assignment
    tests/arrays/array_assignment_test.hurtip
    [=[[100, 20, 30]
[[1, 99], [3, 4]]]=]
)

add_hurtip_success_test(
    array_length
    tests/arrays/array_length_test.hurtip
    [=[3
0
2
2]=]
)

add_hurtip_error_test(
    array_negative_index
    tests/arrays/array_negative_index_test.hurtip
    "Array index must be a non-negative integer"
)

add_hurtip_error_test(
    array_fractional_index
    tests/arrays/array_fractional_index_test.hurtip
    "Array index must be a non-negative integer"
)

add_hurtip_error_test(
    array_out_of_range
    tests/arrays/array_out_of_range_test.hurtip
    "Array index out of range"
)

add_hurtip_error_test(
    array_invalid_object
    tests/arrays/array_invalid_object_test.hurtip
    "Index access requires an array"
)



# Lexer unit tests

add_executable(lexer_tests
    lexer/lexer_test.cpp
    ${PROJECT_SOURCE_DIR}/src/lexer/lexer.cpp
)

target_include_directories(lexer_tests
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

if(MSVC)
    target_compile_options(lexer_tests PRIVATE /W4)
else()
    target_compile_options(lexer_tests PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_test(
    NAME lexer_unit_tests
    COMMAND lexer_tests
)

# Parser unit tests

add_executable(parser_tests
    parser/parser_test.cpp
    ${PROJECT_SOURCE_DIR}/src/lexer/lexer.cpp
    ${PROJECT_SOURCE_DIR}/src/parser/parser.cpp
)

target_include_directories(parser_tests
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

if(MSVC)
    target_compile_options(parser_tests PRIVATE /W4)
else()
    target_compile_options(parser_tests PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_test(
    NAME parser_unit_tests
    COMMAND parser_tests
)


# Interpreter module recovery tests

add_executable(interpreter_module_recovery_tests
    modules/interpreter_module_recovery_test.cpp
    ${PROJECT_SOURCE_DIR}/src/lexer/lexer.cpp
    ${PROJECT_SOURCE_DIR}/src/parser/parser.cpp
    ${PROJECT_SOURCE_DIR}/src/interpreter/interpreter.cpp
    ${PROJECT_SOURCE_DIR}/src/interpreter/interpreter_expressions.cpp
    ${PROJECT_SOURCE_DIR}/src/environment/environment.cpp
    ${PROJECT_SOURCE_DIR}/src/libraries/math.cpp
    ${PROJECT_SOURCE_DIR}/src/libraries/standard_library.cpp
)

target_include_directories(interpreter_module_recovery_tests
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

target_compile_definitions(interpreter_module_recovery_tests
    PRIVATE
        HURTIP_PROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}"
)

if(MSVC)
    target_compile_options(interpreter_module_recovery_tests PRIVATE /W4)
else()
    target_compile_options(interpreter_module_recovery_tests PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_test(
    NAME interpreter_module_recovery
    COMMAND interpreter_module_recovery_tests
)
