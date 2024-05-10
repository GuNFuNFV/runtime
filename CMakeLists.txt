cmake_minimum_required(VERSION 3.10)
project(nflr)




# The initial file(GLOB_RECURSE) command
file(GLOB_RECURSE SRCS-y "${CMAKE_CURRENT_SOURCE_DIR}/headers/*.c")

# Append source files from another directory
file(GLOB_RECURSE additional_sources "${CMAKE_CURRENT_SOURCE_DIR}/common/*.c")
list(APPEND SRCS-y ${additional_sources})
list(APPEND SRCS-y ${CMAKE_CURRENT_SOURCE_DIR}/main.c)

file(GLOB_RECURSE headers "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

# Define build types and set the default build type
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
    set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configurations" FORCE)
endif()

# Find pkg-config
find_package(PkgConfig REQUIRED)

# Check for DPDK using pkg-config
pkg_check_modules(DPDK REQUIRED libdpdk)

# Include DPDK include directories
include_directories(${DPDK_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/headers)
# Add the executable for the APP
add_executable(${PROJECT_NAME} ${SRCS-y} ${headers})

# Link against the DPDK library and add compiler flags
target_link_libraries(${PROJECT_NAME} PRIVATE ${DPDK_LIBRARIES})
target_compile_options(${PROJECT_NAME} PRIVATE ${DPDK_CFLAGS_OTHER})

find_library(JANSSON_LIBRARY NAMES jansson)
if (NOT JANSSON_LIBRARY)
    message(FATAL_ERROR "jansson library not found! execute 'sudo apt-get install libjansson-dev' to install it")
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE ${JANSSON_LIBRARY})
endif()

add_custom_target(run_python_script
        COMMAND python3 ${CMAKE_SOURCE_DIR}/headers/nf/register_actor.py
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Running Python script before compilation"
        VERBATIM
)

add_dependencies(nflr run_python_script)
# add -DDEBUG flag to compiler if build type is Debug
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
endif()
