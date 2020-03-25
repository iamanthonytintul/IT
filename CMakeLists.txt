cmake_minimum_required(VERSION 3.9)

project(Park_Mail_Ru_IZ2)
set(CMAKE_C_STANDARD 11)

##
### Test definitions ###
##
configure_file(CMakeLists.txt.in
        googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build)

add_definitions(-DPATH_TO_DYNAMIC_LIB="${CMAKE_BINARY_DIR}/libdynamic_employee_DB.so")

##
### Source definitions ###
##
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wpedantic -fPIC")

include_directories(${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/libs)

add_library(employee_DB STATIC libs/employee_DB.c)
add_library(static_employee_DB STATIC libs/static_employee_DB.c libs/employee_DB.c)
add_library(dynamic_employee_DB SHARED libs/dynamic_employee_DB.c libs/employee_DB.c)

add_executable(static_library_main src/static_library_main.c src/count_time.c)
add_executable(dynamic_library_main src/dynamic_library_main.c src/count_time.c)

target_link_libraries(static_employee_DB  employee_DB)
target_link_libraries(dynamic_employee_DB  employee_DB)

target_link_libraries(static_library_main  static_employee_DB )
target_link_libraries(dynamic_library_main  dynamic_employee_DB ${CMAKE_DL_LIBS} ${CMAKE_THREAD_LIBS_INIT})

enable_testing()
add_subdirectory(test)
