file(GLOB tests "${PROJECT_SOURCE_DIR}/test/*_tests/*.cpp")
list(REMOVE_ITEM tests "${PROJECT_SOURCE_DIR}/test/main.cpp")
file(GLOB sources "${PROJECT_SOURCE_DIR}/src/count_time.c")

include_directories(${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/libs ${PROJECT_SOURCE_DIR}/src)

add_definitions(-DPATH_INPUT_REGULAR_CASE="${PROJECT_SOURCE_DIR}/test/test_files/regular_case/employees"
        -DPATH_INPUT_SAME_SURNAME_CASE="${PROJECT_SOURCE_DIR}/test/test_files/same_surname_case/employees"
        -DPATH_INPUT_INVALID_CASE="${PROJECT_SOURCE_DIR}/test/test_files/invalid_case/employees"
        -DPATH_OUTPUT="${PROJECT_SOURCE_DIR}/test/test_files/same_surname_case/output"
        -DPATH_TRUE_OUTPUT="${PROJECT_SOURCE_DIR}/test/test_files/same_surname_case/true_output")

add_definitions(-DPATH_FUNCTIONAL_INPUT_FIRST_REGULAR_CASE="${PROJECT_SOURCE_DIR}/test/test_files/functional_test/first_employees"
        -DPATH_FUNCTIONAL_INPUT_SECOND_REGULAR_CASE="${PROJECT_SOURCE_DIR}/test/test_files/functional_test/second_employees"
        -DPATH_FUNCTIONAL_OUTPUT_STATIC_LIB="${PROJECT_SOURCE_DIR}/test/test_files/functional_test/output_static"
        -DPATH_FUNCTIONAL_OUTPUT_DYNAMIC_LIB="${PROJECT_SOURCE_DIR}/test/test_files/functional_test/output_dynamic")

add_definitions(-DPATH_STRESS_INPUT_HUNDRED_THOUSAND_CASE="${PROJECT_SOURCE_DIR}/test/test_files/stress_test/hundred_thousand_employees"
        -DPATH_STRESS_INPUT_FIVE_HUNDRED_THOUSAND_CASE="${PROJECT_SOURCE_DIR}/test/test_files/stress_test/five_hundred_thousands_employees"
        -DPATH_STRESS_OUTPUT_STATIC_LIB="${PROJECT_SOURCE_DIR}/test/test_files/stress_test/output_static"
        -DPATH_STRESS_OUTPUT_DYNAMIC_LIB="${PROJECT_SOURCE_DIR}/test/test_files/stress_test/output_dynamic")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
set (CMAKE_CXX_STANDARD 11)

foreach(file ${tests})
    set(name)
    get_filename_component(name ${file} NAME_WE)
    add_executable("${name}_tests"
            ${sources}
            ${file}
            "${PROJECT_SOURCE_DIR}/test/main.cpp")
    target_link_libraries("${name}_tests" gtest gtest_main pthread dynamic_employee_DB static_employee_DB)
    add_test(NAME ${name} COMMAND "${name}_tests")
endforeach()
