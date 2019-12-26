message(STATUS " HPR_BLAS_DIR is ${HPR_BLAS_DIR}")

set(HPR_BLAS_COMMON_CONFIG "${HPR_BLAS_DIR}/tools/cmake/HPR_BLASCommon.cmake")

if( EXISTS ${HPR_BLAS_COMMON_CONFIG})
	include(${HPR_BLAS_COMMON_CONFIG})
else()
	message(ERROR "  Could not find the HPR-BLAS library configuration at ${HPR_BLAS_COMMON_CONFIG}")
endif()
