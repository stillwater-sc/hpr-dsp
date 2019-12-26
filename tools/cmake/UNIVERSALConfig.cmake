message(STATUS "UNIVERSAL_DIR is ${UNIVERSAL_DIR}")

set(UNIVERSAL_COMMON_CONFIG "${UNIVERSAL_DIR}/tools/cmake/UNIVERSALCommon.cmake")

message(STATUS "UNIVERSAL_COMMON_CONFIG is ${UNIVERSAL_COMMON_CONFIGIR}")

if( EXISTS ${UNIVERSAL_COMMON_CONFIG})
	include(${UNIVERSAL_COMMON_CONFIG})
else()
	message(ERROR "Could not find the common universal arithmetic library configuration.")
endif()
