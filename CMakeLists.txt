cmake_minimum_required(VERSION 3.10)

# Defines softfloat library
project (SoftFloat )

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# generate compile command database for external tools
set (CMAKE_EXPORT_COMPILE_COMMANDS "ON")

message ( STATUS "Configuring SoftFloat" )
set( C_DEFINES "-DSOFTFLOAT_FAST_INT64 -DSOFTFLOAT_ROUND_EVEN -DINLINE_LEVEL=5 -DSOFTFLOAT_FAST_DIV32TO16 -DSOFTFLOAT_FAST_DIV64TO32" )
set( CMAKE_C_FLAGS " -Wall -Werror-implicit-function-declaration -Wno-conversion ${CMAKE_C_FLAGS} ${C_DEFINES}" )

if(CMAKE_SYSTEM_PROCESSOR MATCHES "wasm|wasm32|wasm64")
   message(STATUS "Configuring for wasm")
   set(ARCH_SOURCE_TYPE 8086-SSE)
   set(ARCH_BUILD_TYPE Linux-x86_64-GCC)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|AMD64|amd64|x64")
   message(STATUS "Configuring for x86_64")
   set(ARCH_SOURCE_TYPE 8086-SSE)
   set(ARCH_BUILD_TYPE Linux-x86_64-GCC)
elseif(MSVC AND CMAKE_SYSTEM_PROCESSOR MATCHES "arm64|ARM64|aarch64")
   message(STATUS "Configuring for Windows ARM64 with generic ARM sources")
   set(ARCH_SOURCE_TYPE ARM-VFPv2)
   set(ARCH_BUILD_TYPE template-FAST_INT64)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "arm64|ARM64|aarch64")
   message(STATUS "Configuring for arm64")
   set(ARCH_SOURCE_TYPE ARM-VFPv2)
   set(ARCH_BUILD_TYPE Linux-ARM-VFPv2-GCC)
else()
   message(FATAL_ERROR "Unsupported architecture: ${CMAKE_SYSTEM_PROCESSOR}")
endif()

set ( softfloat_sources
  source/s_eq128.c
  source/s_le128.c
  source/s_lt128.c
  source/s_shortShiftLeft128.c
  source/s_shortShiftRight128.c
  source/s_shortShiftRightJam64.c
  source/s_shortShiftRightJam64Extra.c
  source/s_shortShiftRightJam128.c
  source/s_shortShiftRightJam128Extra.c
  source/s_shiftRightJam32.c
  source/s_shiftRightJam64.c
  source/s_shiftRightJam64Extra.c
  source/s_shiftRightJam128.c
  source/s_shiftRightJam128Extra.c
  source/s_shiftRightJam256M.c
  source/s_countLeadingZeros8.c
  source/s_countLeadingZeros16.c
  source/s_countLeadingZeros32.c
  source/s_countLeadingZeros64.c
  source/s_add128.c
  source/s_add256M.c
  source/s_sub128.c
  source/s_sub256M.c
  source/s_mul64ByShifted32To128.c
  source/s_mul64To128.c
  source/s_mul128By32.c
  source/s_mul128To256M.c
  source/s_approxRecip_1Ks.c
  source/s_approxRecip32_1.c
  source/s_approxRecipSqrt_1Ks.c
  source/s_approxRecipSqrt32_1.c
  source/${ARCH_SOURCE_TYPE}/softfloat_raiseFlags.c
  source/${ARCH_SOURCE_TYPE}/s_f16UIToCommonNaN.c
  source/${ARCH_SOURCE_TYPE}/s_commonNaNToF16UI.c
  source/${ARCH_SOURCE_TYPE}/s_propagateNaNF16UI.c
  source/${ARCH_SOURCE_TYPE}/s_f32UIToCommonNaN.c
  source/${ARCH_SOURCE_TYPE}/s_commonNaNToF32UI.c
  source/${ARCH_SOURCE_TYPE}/s_propagateNaNF32UI.c
  source/${ARCH_SOURCE_TYPE}/s_f64UIToCommonNaN.c
  source/${ARCH_SOURCE_TYPE}/s_commonNaNToF64UI.c
  source/${ARCH_SOURCE_TYPE}/s_propagateNaNF64UI.c
  source/${ARCH_SOURCE_TYPE}/extF80M_isSignalingNaN.c
  source/${ARCH_SOURCE_TYPE}/s_extF80UIToCommonNaN.c
  source/${ARCH_SOURCE_TYPE}/s_commonNaNToExtF80UI.c
  source/${ARCH_SOURCE_TYPE}/s_propagateNaNExtF80UI.c
  source/${ARCH_SOURCE_TYPE}/f128M_isSignalingNaN.c
  source/${ARCH_SOURCE_TYPE}/s_f128UIToCommonNaN.c
  source/${ARCH_SOURCE_TYPE}/s_commonNaNToF128UI.c
  source/${ARCH_SOURCE_TYPE}/s_propagateNaNF128UI.c
  source/s_roundToUI32.c
  source/s_roundToUI64.c
  source/s_roundToI32.c
  source/s_roundToI64.c
  source/s_normSubnormalF16Sig.c
  source/s_roundPackToF16.c
  source/s_normRoundPackToF16.c
  source/s_addMagsF16.c
  source/s_subMagsF16.c
  source/s_mulAddF16.c
  source/s_normSubnormalF32Sig.c
  source/s_roundPackToF32.c
  source/s_normRoundPackToF32.c
  source/s_addMagsF32.c
  source/s_subMagsF32.c
  source/s_mulAddF32.c
  source/s_normSubnormalF64Sig.c
  source/s_roundPackToF64.c
  source/s_normRoundPackToF64.c
  source/s_addMagsF64.c
  source/s_subMagsF64.c
  source/s_mulAddF64.c
  source/s_normSubnormalExtF80Sig.c
  source/s_roundPackToExtF80.c
  source/s_normRoundPackToExtF80.c
  source/s_addMagsExtF80.c
  source/s_subMagsExtF80.c
  source/s_normSubnormalF128Sig.c
  source/s_roundPackToF128.c
  source/s_normRoundPackToF128.c
  source/s_addMagsF128.c
  source/s_subMagsF128.c
  source/s_mulAddF128.c
  source/softfloat_state.c
  source/ui32_to_f16.c
  source/ui32_to_f32.c
  source/ui32_to_f64.c
  source/ui32_to_extF80.c
  source/ui32_to_extF80M.c
  source/ui32_to_f128.c
  source/ui32_to_f128M.c
  source/ui64_to_f16.c
  source/ui64_to_f32.c
  source/ui64_to_f64.c
  source/ui64_to_extF80.c
  source/ui64_to_extF80M.c
  source/ui64_to_f128.c
  source/ui64_to_f128M.c
  source/i32_to_f16.c
  source/i32_to_f32.c
  source/i32_to_f64.c
  source/i32_to_extF80.c
  source/i32_to_extF80M.c
  source/i32_to_f128.c
  source/i32_to_f128M.c
  source/i64_to_f16.c
  source/i64_to_f32.c
  source/i64_to_f64.c
  source/i64_to_extF80.c
  source/i64_to_extF80M.c
  source/i64_to_f128.c
  source/i64_to_f128M.c
  source/f16_to_ui32.c
  source/f16_to_ui64.c
  source/f16_to_i32.c
  source/f16_to_i64.c
  source/f16_to_ui32_r_minMag.c
  source/f16_to_ui64_r_minMag.c
  source/f16_to_i32_r_minMag.c
  source/f16_to_i64_r_minMag.c
  source/f16_to_f32.c
  source/f16_to_f64.c
  source/f16_to_extF80.c
  source/f16_to_extF80M.c
  source/f16_to_f128.c
  source/f16_to_f128M.c
  source/f16_roundToInt.c
  source/f16_add.c
  source/f16_sub.c
  source/f16_mul.c
  source/f16_mulAdd.c
  source/f16_div.c
  source/f16_rem.c
  source/f16_sqrt.c
  source/f16_eq.c
  source/f16_le.c
  source/f16_lt.c
  source/f16_eq_signaling.c
  source/f16_le_quiet.c
  source/f16_lt_quiet.c
  source/f16_isSignalingNaN.c
  source/f32_to_ui32.c
  source/f32_to_ui64.c
  source/f32_to_i32.c
  source/f32_to_i64.c
  source/f32_to_ui32_r_minMag.c
  source/f32_to_ui64_r_minMag.c
  source/f32_to_i32_r_minMag.c
  source/f32_to_i64_r_minMag.c
  source/f32_to_f16.c
  source/f32_to_f64.c
  source/f32_to_extF80.c
  source/f32_to_extF80M.c
  source/f32_to_f128.c
  source/f32_to_f128M.c
  source/f32_roundToInt.c
  source/f32_add.c
  source/f32_sub.c
  source/f32_mul.c
  source/f32_mulAdd.c
  source/f32_div.c
  source/f32_rem.c
  source/f32_sqrt.c
  source/f32_eq.c
  source/f32_le.c
  source/f32_lt.c
  source/f32_eq_signaling.c
  source/f32_le_quiet.c
  source/f32_lt_quiet.c
  source/f32_isSignalingNaN.c
  source/f64_to_ui32.c
  source/f64_to_ui64.c
  source/f64_to_i32.c
  source/f64_to_i64.c
  source/f64_to_ui32_r_minMag.c
  source/f64_to_ui64_r_minMag.c
  source/f64_to_i32_r_minMag.c
  source/f64_to_i64_r_minMag.c
  source/f64_to_f16.c
  source/f64_to_f32.c
  source/f64_to_extF80.c
  source/f64_to_extF80M.c
  source/f64_to_f128.c
  source/f64_to_f128M.c
  source/f64_roundToInt.c
  source/f64_add.c
  source/f64_sub.c
  source/f64_mul.c
  source/f64_mulAdd.c
  source/f64_div.c
  source/f64_rem.c
  source/f64_sqrt.c
  source/f64_eq.c
  source/f64_le.c
  source/f64_lt.c
  source/f64_eq_signaling.c
  source/f64_le_quiet.c
  source/f64_lt_quiet.c
  source/f64_isSignalingNaN.c
  source/extF80_to_ui32.c
  source/extF80_to_ui64.c
  source/extF80_to_i32.c
  source/extF80_to_i64.c
  source/extF80_to_ui32_r_minMag.c
  source/extF80_to_ui64_r_minMag.c
  source/extF80_to_i32_r_minMag.c
  source/extF80_to_i64_r_minMag.c
  source/extF80_to_f16.c
  source/extF80_to_f32.c
  source/extF80_to_f64.c
  source/extF80_to_f128.c
  source/extF80_roundToInt.c
  source/extF80_add.c
  source/extF80_sub.c
  source/extF80_mul.c
  source/extF80_div.c
  source/extF80_rem.c
  source/extF80_sqrt.c
  source/extF80_eq.c
  source/extF80_le.c
  source/extF80_lt.c
  source/extF80_eq_signaling.c
  source/extF80_le_quiet.c
  source/extF80_lt_quiet.c
  source/extF80_isSignalingNaN.c
  source/extF80M_to_ui32.c
  source/extF80M_to_ui64.c
  source/extF80M_to_i32.c
  source/extF80M_to_i64.c
  source/extF80M_to_ui32_r_minMag.c
  source/extF80M_to_ui64_r_minMag.c
  source/extF80M_to_i32_r_minMag.c
  source/extF80M_to_i64_r_minMag.c
  source/extF80M_to_f16.c
  source/extF80M_to_f32.c
  source/extF80M_to_f64.c
  source/extF80M_to_f128M.c
  source/extF80M_roundToInt.c
  source/extF80M_add.c
  source/extF80M_sub.c
  source/extF80M_mul.c
  source/extF80M_div.c
  source/extF80M_rem.c
  source/extF80M_sqrt.c
  source/extF80M_eq.c
  source/extF80M_le.c
  source/extF80M_lt.c
  source/extF80M_eq_signaling.c
  source/extF80M_le_quiet.c
  source/extF80M_lt_quiet.c
  source/f128_to_ui32.c
  source/f128_to_ui64.c
  source/f128_to_i32.c
  source/f128_to_i64.c
  source/f128_to_ui32_r_minMag.c
  source/f128_to_ui64_r_minMag.c
  source/f128_to_i32_r_minMag.c
  source/f128_to_i64_r_minMag.c
  source/f128_to_f16.c
  source/f128_to_f32.c
  source/f128_to_extF80.c
  source/f128_to_f64.c
  source/f128_roundToInt.c
  source/f128_add.c
  source/f128_sub.c
  source/f128_mul.c
  source/f128_mulAdd.c
  source/f128_div.c
  source/f128_rem.c
  source/f128_sqrt.c
  source/f128_eq.c
  source/f128_le.c
  source/f128_lt.c
  source/f128_eq_signaling.c
  source/f128_le_quiet.c
  source/f128_lt_quiet.c
  source/f128_isSignalingNaN.c
  source/f128M_to_ui32.c
  source/f128M_to_ui64.c
  source/f128M_to_i32.c
  source/f128M_to_i64.c
  source/f128M_to_ui32_r_minMag.c
  source/f128M_to_ui64_r_minMag.c
  source/f128M_to_i32_r_minMag.c
  source/f128M_to_i64_r_minMag.c
  source/f128M_to_f16.c
  source/f128M_to_f32.c
  source/f128M_to_extF80M.c
  source/f128M_to_f64.c
  source/f128M_roundToInt.c
  source/f128M_add.c
  source/f128M_sub.c
  source/f128M_mul.c
  source/f128M_mulAdd.c
  source/f128M_div.c
  source/f128M_rem.c
  source/f128M_sqrt.c
  source/f128M_eq.c
  source/f128M_le.c
  source/f128M_lt.c
  source/f128M_eq_signaling.c
  source/f128M_le_quiet.c
  source/f128M_lt_quiet.c
)

file ( GLOB softfloat_headers "${CMAKE_CURRENT_SOURCE_DIR}/source/include/*.h"
                              "${CMAKE_CURRENT_SOURCE_DIR}/build/${ARCH_BUILD_TYPE}/platform.h"
                              "${CMAKE_CURRENT_SOURCE_DIR}/source/${ARCH_SOURCE_TYPE}/specialize.h" )
list( APPEND softfloat_sources ${softfloat_headers} )
add_library ( softfloat STATIC ${softfloat_sources} )
target_include_directories( softfloat PUBLIC
   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/source/include>
   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/source/${ARCH_SOURCE_TYPE}>
   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/build/${ARCH_BUILD_TYPE}>
   $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/softfloat>
)
target_compile_options(softfloat PRIVATE
   $<$<COMPILE_LANG_AND_ID:C,AppleClang,Clang,GNU>:-Wno-unused-label>
)

if((APPLE OR CMAKE_SYSTEM_NAME STREQUAL "Linux") AND CMAKE_SYSTEM_PROCESSOR MATCHES "arm64|ARM64|aarch64")
   target_compile_definitions(softfloat INTERFACE
      SOFTFLOAT_DISABLE_LEGACY_TYPE_ALIASES
   )

   file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/include/softfloat")
   configure_file(
      "${CMAKE_CURRENT_SOURCE_DIR}/source/include/softfloat.hpp"
      "${CMAKE_CURRENT_BINARY_DIR}/include/softfloat/softfloat.hpp"
      COPYONLY
   )
   configure_file(
      "${CMAKE_CURRENT_SOURCE_DIR}/source/include/softfloat_types.h"
      "${CMAKE_CURRENT_BINARY_DIR}/include/softfloat_types.h"
      COPYONLY
   )
   add_executable(softfloat_neon_include_order_test
      tests/softfloat_neon_include_order_test.cpp
      tests/softfloat_neon_include_order_reverse_test.cpp
   )
   target_include_directories(softfloat_neon_include_order_test PRIVATE
      "${CMAKE_CURRENT_BINARY_DIR}/include"
      "${CMAKE_CURRENT_SOURCE_DIR}/source/include"
   )
   target_link_libraries(softfloat_neon_include_order_test PRIVATE softfloat)
endif()

if(SOFTFLOAT_INSTALL_COMPONENT)
   set(INSTALL_COMPONENT_ARGS COMPONENT ${SOFTFLOAT_INSTALL_COMPONENT} EXCLUDE_FROM_ALL)
endif()

write_basic_package_version_file(
   "${CMAKE_CURRENT_BINARY_DIR}/softfloat-config-version.cmake"
   VERSION 3.0.0
   COMPATIBILITY SameMajorVersion
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/source/include/ DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/softfloat ${INSTALL_COMPONENT_ARGS})
install(TARGETS softfloat
   EXPORT softfloat-config
   LIBRARY DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR} ${INSTALL_COMPONENT_ARGS}
   ARCHIVE DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR} ${INSTALL_COMPONENT_ARGS})
install(EXPORT softfloat-config
   FILE softfloat-config.cmake
   NAMESPACE softfloat::
   DESTINATION ${CMAKE_INSTALL_DATADIR}/softfloat
   ${INSTALL_COMPONENT_ARGS})
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/softfloat-config-version.cmake"
   DESTINATION ${CMAKE_INSTALL_DATADIR}/softfloat
   ${INSTALL_COMPONENT_ARGS})
