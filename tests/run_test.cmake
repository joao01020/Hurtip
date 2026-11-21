
if(NOT DEFINED PROGRAM OR NOT DEFINED SOURCE)
    message(FATAL_ERROR "PROGRAM and SOURCE must be defined")
endif()

if(NOT EXISTS "${PROGRAM}")
    message(FATAL_ERROR "Hurtip executable not found: ${PROGRAM}")
endif()

if(NOT EXISTS "${SOURCE}")
    message(FATAL_ERROR "Test source not found: ${SOURCE}")
endif()

execute_process(
    COMMAND "${PROGRAM}" "${SOURCE}"
    RESULT_VARIABLE TEST_RESULT
    OUTPUT_VARIABLE TEST_OUTPUT
    ERROR_VARIABLE TEST_ERROR
)

set(TEST_COMBINED_OUTPUT "${TEST_OUTPUT}${TEST_ERROR}")

if(DEFINED EXPECTED_ERROR AND NOT EXPECTED_ERROR STREQUAL "")
    if(TEST_RESULT EQUAL 0)
        message(FATAL_ERROR
            "Expected the program to fail, but it succeeded.\n"
            "Source: ${SOURCE}\n"
            "Output:\n${TEST_COMBINED_OUTPUT}"
        )
    endif()

    string(FIND
        "${TEST_COMBINED_OUTPUT}"
        "${EXPECTED_ERROR}"
        ERROR_POSITION
    )

    if(ERROR_POSITION EQUAL -1)
        message(FATAL_ERROR
            "Expected error message not found.\n"
            "Expected: ${EXPECTED_ERROR}\n"
            "Actual output:\n${TEST_COMBINED_OUTPUT}"
        )
    endif()

    message(STATUS "Expected error detected: ${EXPECTED_ERROR}")

else()
    if(NOT TEST_RESULT EQUAL 0)
        message(FATAL_ERROR
            "Program execution failed.\n"
            "Source: ${SOURCE}\n"
            "Exit code: ${TEST_RESULT}\n"
            "Output:\n${TEST_COMBINED_OUTPUT}"
        )
    endif()

    string(STRIP "${TEST_OUTPUT}" ACTUAL_OUTPUT)
    string(STRIP "${EXPECTED_OUTPUT}" EXPECTED_OUTPUT_STRIPPED)

    if(NOT ACTUAL_OUTPUT STREQUAL EXPECTED_OUTPUT_STRIPPED)
        message(FATAL_ERROR
            "Output does not match expected result.\n"
            "Source: ${SOURCE}\n"
            "Expected:\n${EXPECTED_OUTPUT_STRIPPED}\n"
            "Actual:\n${ACTUAL_OUTPUT}"
        )
    endif()

    message(STATUS "Output matches expected result")
endif()
