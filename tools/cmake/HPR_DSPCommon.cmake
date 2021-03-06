############################
# This configuration file defines some cmake variables:
# HPR_DSP_INCLUDE_DIRS: list of include directories for the universal library
# HPR_DSP_LIBRARIES: libraries needed for peripheral collections 
# HPR_DSP_CXX_DEFINITIONS: definitions to enable the requested interfaces
# HPR_DSP_VERSION: version 
# HPR_DSP_MAJOR_VERSION: major version 
# HPR_DSP_MINOR_VERSION: minor version 
#
#supported components:
#

unset(HPR_DSP_LIBRARIES )
unset(HPR_DSP_CXX_DEFINITIONS )
unset(HPR_DSP_INCLUDE_DIRS )

set(HPR_DSP_VERSION 0)
set(HPR_DSP_MAJOR_VERSION 1)
set(HPR_DSP_MINOR_VERSION 0)

if (MSVC)
    add_definitions(/wd4522) # multiple assignment ops for single type, to be investigated further if avoidable
endif()

if (USE_ASSERTS)
  list(APPEND HPR_DSP_CXX_DEFINITIONS "-DHPR_DSP_ASSERT_FOR_THROW")
endif()

if(EXISTS ${HPR_DSP_DIR}/hprdsp/hprdsp.hpp)
	list(APPEND HPR_DSP_INCLUDE_DIRS "${HPR_DSP_DIR}/hprdsp")
else()
	list(APPEND HPR_DSP_INCLUDE_DIRS "${HPR_DSP_DIR}/../../include")
endif(EXISTS ${HPR_DSP_DIR}/hprdsp/hprdsp.hpp)

macro(hpr_blas_check_cxx_compiler_flag FLAG RESULT)
  # counts entirely on compiler's return code, maybe better to combine it with check_cxx_compiler_flag
  file(WRITE "${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeTmp/src.cxx" "int main() { return 0;}\n")
  try_compile(${RESULT}
    ${CMAKE_BINARY_DIR}
    ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeTmp/src.cxx
    COMPILE_DEFINITIONS ${FLAG})  
endmacro()

