############################
# This configuration file defines some cmake variables:
# HPR_BLAS_INCLUDE_DIRS: list of include directories for the HPR-BLAS library
# HPR_BLAS_LIBRARIES: libraries needed 
# HPR_BLAS_CXX_DEFINITIONS: definitions to enable the requested interfaces
# HPR_BLAS_VERSION: version
# HPR_BLAS_MAJOR_VERSION: major version 
# HPR_BLAS_MINOR_VERSION: minor version 
#
#supported components:
#

unset(HPR_BLAS_LIBRARIES )
unset(HPR_BLAS_CXX_DEFINITIONS )
unset(HPR_BLAS_INCLUDE_DIRS )

set(HPR_BLAS_VERSION 1)
set(HPR_BLAS_MAJOR_VERSION 0)
set(HPR_BLAS_MINOR_VERSION 1)

message(STATUS " HPR_BLASCommon.cmake: HPR_BLAS_DIR is ${HPR_BLAS_DIR}")
message(STATUS " HPR_BLASCommon.cmake: HPR_DSP_DIR is ${HPR_DSP_DIR}")

if (MSVC)
    add_definitions(/wd4522) # multiple assignment ops for single type, to be investigated further if avoidable
endif()

if (USE_ASSERTS)
  list(APPEND HPR_BLAS_CXX_DEFINITIONS "-DHPR_BLAS_ASSERT_FOR_THROW")
endif()

if(EXISTS ${HPR_BLAS_DIR}/include/hpbblas.hpp)
	message(STATUS " HPR_BLAS include was found")
	list(APPEND HPR_BLAS_INCLUDE_DIRS "${HPR_BLAS_DIR}/include")
else()
	# assuming a dev tree where the repos are stored along side each other, i.e.
	# .../dev/clones/universal
	# .../dev/clones/mtl4
	# .../dev/clones/hpr-blas
	# .../dev/clones/hpr-dsp
	list(APPEND HPR_BLAS_INCLUDE_DIRS "${HPR_DSP_DIR}/../hpr-blas/include")
endif(EXISTS ${HPR_BLAS_DIR}/include/hprblas.hpp)

macro(hpr_blas_check_cxx_compiler_flag FLAG RESULT)
  # counts entirely on compiler's return code, maybe better to combine it with check_cxx_compiler_flag
  file(WRITE "${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeTmp/src.cxx" "int main() { return 0;}\n")
  try_compile(${RESULT}
    ${CMAKE_BINARY_DIR}
    ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeTmp/src.cxx
    COMPILE_DEFINITIONS ${FLAG})  
endmacro()

