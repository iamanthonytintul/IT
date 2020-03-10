file(GLOB sources "${PROJECT_SOURCE_DIR}/src/*.c")
list(REMOVE_ITEM sources "${PROJECT_SOURCE_DIR}/src/main.c")

file(GLOB tests "${PROJECT_SOURCE_DIR}/test/*.cpp")
list(REMOVE_ITEM tests "${PROJECT_SOURCE_DIR}/test/main.cpp")

include_directories(${PROJECT_SOURCE_DIR}/include)

add_definitions(-DPATH_TO_IO_TEST_INTEGER="${PROJECT_SOURCE_DIR}/test/inputTest/IO/IntegerInput"
        -DPATH_TO_IO_TEST_WRONG="${PROJECT_SOURCE_DIR}/test/inputTest/IO/WrongInput"
        -DPATH_TO_IO_TEST_DOUBLE="${PROJECT_SOURCE_DIR}/test/inputTest/IO/DoubleInput"
        -DPATH_TO_IO_TEST_SPACE="${PROJECT_SOURCE_DIR}/test/inputTest/IO/FirstSpaceInput"
        -DPATH_TO_IO_TEST_NEGATIVE="${PROJECT_SOURCE_DIR}/test/inputTest/IO/NegativeNumberInput")

add_definitions(-DPATH_TO_IO_DOTS_TEST_INTEGER="${PROJECT_SOURCE_DIR}/test/inputTest/IODots/IntegerInput"
        -DPATH_TO_IO_DOTS_TEST_DOUBLE="${PROJECT_SOURCE_DIR}/test/inputTest/IODots/DoubleInput"
        -DPATH_TO_IO_DOTS_TEST_WRONG="${PROJECT_SOURCE_DIR}/test/inputTest/IODots/WrongInput"
        -DPATH_TO_IO_DOTS_TEST_NULL="${PROJECT_SOURCE_DIR}/test/inputTest/IODots/NullInput")


foreach(file ${tests})
    set(name)
    get_filename_component(name ${file} NAME_WE)
    add_executable("${name}_tests"
            ${sources}
            ${file}
            "${PROJECT_SOURCE_DIR}/test/main.cpp" Calculate.cpp Determinate.cpp InputNumbers.cpp InputDots.cpp)
    target_link_libraries("${name}_tests" gtest_main)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage -fprofile-arcs -ftest-coverage")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -fprofile-arcs -ftest-coverage")
    add_test(NAME ${name} COMMAND "${name}_tests")
endforeach()
