# HPR-DSP: high-performance reproducible digital signal processing
project (hpr-dsp)

cmake_minimum_required(VERSION 3.0)

option(HPR_DSP_CMAKE_TRACE "Tracing CMake results, i.e. printing variable settings." OFF)
option(HPR_DSP_ENABLE_TESTS "Enable the build and run of tests." ON)
option(HPR_DSP_VERBOSE_TESTS "Always print test output, otherwise only errors. Only relevant when tests enabled." OFF)

macro(trace_variable variable)
    if (HPR_DSP_CMAKE_TRACE)
        message(STATUS "${variable} = ${${variable}}")
    endif()
endmacro()
        
# TODO: Check whether this is needed for old CMake versions
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/tools/cmake") 
trace_variable(CMAKE_MODULE_PATH)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/tools/cmake") 
trace_variable(CMAKE_PREFIX_PATH)

# Must be located in root dir, doesn't work in tests
if (HPR_DSP_ENABLE_TESTS)
    enable_testing()
    # include(Dart)
endif()

cmake_policy(SET CMP0074 NEW)
find_package(Boost)
message(STATUS "Boost_FOUND " ${Boost_FOUND})
if (Boost_FOUND)
	message(STATUS "Including Boost_INCLUDE_DIR " ${Boost_INCLUDE_DIR})
	include_directories(${Boost_INCLUDE_DIR})
endif (Boost_FOUND)

cmake_policy(SET CMP0054 NEW)
find_package(MTL REQUIRED)
include_directories(${MTL_INCLUDE_DIRS})
add_definitions(${MTL_CXX_DEFINITIONS})

# Set include directory for universal number lib (posit, fixedpoint, afloat)
find_package(UNIVERSAL REQUIRED)
include_directories(${UNIVERSAL_INCLUDE_DIRS})
message(STATUS "UNIVERSAL INCLUDE DIR " ${UNIVERSAL_INCLUDE_DIRS})

# set include directory for hpr-blas
find_package(HPR_BLAS REQUIRED)
include_directories(${HPR_BLAS_INCLUDE_DIRS})
message(STATUS "HPR BLAS INCLUDE DIR " ${HPR_BLAS_INCLUDE_DIRS})

# Set hpr-dsp include directory
include_directories("./include")

# Possibly not under Windows
#add_compile_options ( -fext-numeric-literals )
add_compile_options ( -std=c++14 )

macro (compile_all testing prefix)
    # cycle through the sources
    # For the according directories, we assume that each cpp file is a separate test
    # and create a executable target and an associated test target for that file
    foreach (source ${ARGN})
        get_filename_component (test ${source} NAME_WE)
        string(REPLACE " " ";" new_source ${source})
        set(test_name ${prefix}_${test})
        # message(STATUS "Add test ${test_name} from source ${new_source}.")
        add_executable (${test_name} ${new_source})
        if (${testing} STREQUAL "true")
	    if (HPR_DSP_CMAKE_TRACE)
                message(STATUS "testing: ${test_name} ${RUNTIME_OUTPUT_DIRECTORY}/${test_name}")
            endif()
            add_test(${test_name} ${RUNTIME_OUTPUT_DIRECTORY}/${test_name})
        endif()
    endforeach (source)
endmacro (compile_all)

add_subdirectory("tools/benchmark")
#add_subdirectory("tools/matrix_generation")
add_subdirectory("dsp")
add_subdirectory("applications")
