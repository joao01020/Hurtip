# Automated Hurtip tests

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

# Modules

add_hurtip_success_test(
    module_system
    tests/modules/module_test.hurtip
    [=[30
60]=]
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
    array_pop
    tests/arrays/array_pop_test.hurtip
    [=[30
[10, 20]
2
42
[Hurtip, true]]=]
)

add_hurtip_error_test(
    array_pop_empty
    tests/arrays/array_pop_empty_test.hurtip
    "Cannot pop from an empty array"
)

add_hurtip_success_test(
    array_push
    tests/arrays/array_push_test.hurtip
    [=[[10, 20, 30]
3
[Hurtip, 10, true, C++]]=]
)

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

add_hurtip_success_test(
    array_remove
    tests/arrays/array_remove_test.hurtip
    [=[20
[10, 30, 40]
3
Hurtip
[true, 42]]=]
)

add_hurtip_error_test(
    array_remove_invalid
    tests/arrays/array_remove_invalid_test.hurtip
    "Array remove index out of range"
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

add_hurtip_success_test(
    array_insert
    tests/arrays/array_insert_test.hurtip
    [=[4
[10, 20, 30, 40]
[5, 10, 20, 30, 40, 50]
1
[Hurtip]
[10, Hello, true]]=]
)

add_hurtip_error_test(
    array_insert_invalid
    tests/arrays/array_insert_invalid_test.hurtip
    "Array insert index out of range"
)

add_hurtip_error_test(
    array_insert_negative
    tests/arrays/array_insert_negative_test.hurtip
    "Array insert index must be a non-negative integer"
)

add_hurtip_error_test(
    array_insert_arguments
    tests/arrays/array_insert_arguments_test.hurtip
    "Array method 'insert' expects exactly 2 arguments"
)

add_hurtip_success_test(
    array_contains
    tests/arrays/array_contains_test.hurtip
    [=[true
true
false
true
true
true
false
false]=]
)

add_hurtip_success_test(
    array_index_of
    tests/arrays/array_index_of_test.hurtip
    [=[0
1
2
-1
0
1
2]=]
)

add_hurtip_success_test(
    array_clear
    tests/arrays/array_clear_test.hurtip
    [=[0
[]
0
0
[]
0]=]
)

add_hurtip_success_test(
    array_reverse
    tests/arrays/array_reverse_test.hurtip
    [=[[40, 30, 20, 10]
[40, 30, 20, 10]
[true, 10, Hurtip]
[true, 10, Hurtip]
[]
[]]=]
)

add_hurtip_error_test(
    array_contains_arguments
    tests/arrays/array_contains_arguments_test.hurtip
    "Array method 'contains' expects exactly 1 argument"
)

add_hurtip_error_test(
    array_index_of_arguments
    tests/arrays/array_index_of_arguments_test.hurtip
    "Array method 'indexOf' expects exactly 1 argument"
)

add_hurtip_error_test(
    array_clear_arguments
    tests/arrays/array_clear_arguments_test.hurtip
    "Array method 'clear' expects no arguments"
)

add_hurtip_error_test(
    array_reverse_arguments
    tests/arrays/array_reverse_arguments_test.hurtip
    "Array method 'reverse' expects no arguments"
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