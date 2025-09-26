# Defines softfloat library
cmake_minimum_required(VERSION 3.10)
project(SoftFloat)

# HELPERS
include(GNUInstallDirs)

# DEFAULTS
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "-fdiagnostics-color=always")
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)

# DEPENDENCIES
find_package(Threads REQUIRED)
link_libraries(Threads::Threads)

# VARIABLES FOR KEEP TRACK OF ARCH
# TYPE VARIANTS
set(IS_WASM OFF)
set(IS_ARM OFF)

# DEFINE THE ARCH TYPES OF THE TARGET FOR
# THE PURPOSE OF INCLUDING THE CORRECT ACCELERATION
# `ARCH_(SOURCE|BUILD)_TYPE`. DEFAULTS TO x64
set(ARCH_SOURCE_TYPE 8086-SSE)
set(ARCH_BUILD_TYPE Linux-x86_64-GCC)

# CHECK FOR WASM
if(CMAKE_SYSTEM_PROCESSOR MATCHES "wasm32|wasm64|wasm")
   set(IS_WASM ON)
   message(STATUS "Configuring for WebAssembly")
endif()

# CHECK FOR X64/ARM
if(LINUX AND CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|AMD64|amd64|x64|wasm|wasm32|wasm64")
   message(STATUS "Configuring for x86_64 OR wasm")
elseif(LINUX AND CMAKE_SYSTEM_PROCESSOR MATCHES "arm64|aarch64")
   set(IS_ARM ON)
   message(STATUS "Configuring for arm64")

   # IF ARM, SET THE CORRECT `SOURCE|BUILD` VALUES
   set(ARCH_SOURCE_TYPE ARM-VFPv2)
   set(ARCH_BUILD_TYPE Linux-ARM-VFPv2-GCC)
else()
   # ONLY X64 & ARM ARE CURRENTLY SUPPORTED
   message(FATAL_ERROR "Unsupported architecture: ${CMAKE_SYSTEM_PROCESSOR}")
endif()

message(STATUS "SYSTEM PROCESSOR: ${CMAKE_SYSTEM_PROCESSOR}, IS_WASM: ${IS_WASM}, IS_ARM: ${IS_ARM}")

# OPTIONS
option(SOFTFLOAT_LEGACY_COMPAT "Enable Legacy Compatability (WASM VM, etc)" ON)
option(SOFTFLOAT_SKIP_INSTALL "Skip installation setup/config" OFF)

# COMPATIBILITY: TO ENSURE THE BUILD WORKS 
# WITH PREVIOUS BUILDS THE FLAG SOFTFLOAT_LEGACY_COMPAT 
# DEFAULTS TO `ON`, WHICH EXPLICITLY REMOVES 
# SEVERAL COMPILER FLAGS
if(SOFTFLOAT_LEGACY_COMPAT)
   set(CMAKE_POSITION_INDEPENDENT_CODE OFF)

   macro(remove_release_flags flag)
      foreach(type CMAKE_C_FLAGS_RELEASE CMAKE_CXX_FLAGS_RELEASE)
         string(REPLACE "${flag}" "" ${type} "${${type}}")
      endforeach()
   endmacro()

   macro(remove_debug_flags flag)
      foreach(type CMAKE_C_FLAGS_DEBUG CMAKE_CXX_FLAGS_DEBUG)
         string(REPLACE "${flag}" "" ${type} "${${type}}")
      endforeach()
   endmacro()

   remove_release_flags(-O3)
   remove_release_flags(-O2)
   remove_release_flags(-O1)
   remove_release_flags(-Os)
   remove_release_flags(-O)
   remove_release_flags(-fPIC)

   remove_debug_flags(-O3)
   remove_debug_flags(-O2)
   remove_debug_flags(-O1)
   remove_debug_flags(-Os)
   remove_debug_flags(-O)
   remove_debug_flags(-fPIC)

   set(CMAKE_C_FLAGS "")
   set(CMAKE_CXX_FLAGS "")
   remove_release_flags(-DNDEBUG)
   remove_definitions(-DNDEBUG)
   remove_definitions(-fPIC)
   add_definitions(-w)
endif()



set(softfloat_sources
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
   "source/${ARCH_SOURCE_TYPE}/softfloat_raiseFlags.c"
   "source/${ARCH_SOURCE_TYPE}/s_f16UIToCommonNaN.c"
   "source/${ARCH_SOURCE_TYPE}/s_commonNaNToF16UI.c"
   "source/${ARCH_SOURCE_TYPE}/s_propagateNaNF16UI.c"
   "source/${ARCH_SOURCE_TYPE}/s_f32UIToCommonNaN.c"
   "source/${ARCH_SOURCE_TYPE}/s_commonNaNToF32UI.c"
   "source/${ARCH_SOURCE_TYPE}/s_propagateNaNF32UI.c"
   "source/${ARCH_SOURCE_TYPE}/s_f64UIToCommonNaN.c"
   "source/${ARCH_SOURCE_TYPE}/s_commonNaNToF64UI.c"
   "source/${ARCH_SOURCE_TYPE}/s_propagateNaNF64UI.c"
   "source/${ARCH_SOURCE_TYPE}/extF80M_isSignalingNaN.c"
   "source/${ARCH_SOURCE_TYPE}/s_extF80UIToCommonNaN.c"
   "source/${ARCH_SOURCE_TYPE}/s_commonNaNToExtF80UI.c"
   "source/${ARCH_SOURCE_TYPE}/s_propagateNaNExtF80UI.c"
   "source/${ARCH_SOURCE_TYPE}/f128M_isSignalingNaN.c"
   "source/${ARCH_SOURCE_TYPE}/s_f128UIToCommonNaN.c"
   "source/${ARCH_SOURCE_TYPE}/s_commonNaNToF128UI.c"
   "source/${ARCH_SOURCE_TYPE}/s_propagateNaNF128UI.c"
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

# CONFIGURE FILES
file(
   GLOB
   softfloat_headers
   source/include/*.h
   source/include/*.hpp
   "build/${ARCH_BUILD_TYPE}/platform.h"
   "source/${ARCH_SOURCE_TYPE}/specialize.h"
)


# CREATE LIBRARY
add_library(
   softfloat
   STATIC
   ${softfloat_sources}
)

if(SOFTFLOAT_LEGACY_COMPAT)
   set_target_properties(
      softfloat
      PROPERTIES
      POSITION_INDEPENDENT_CODE OFF
   )
endif()

# CONFIGURE TARGET
# target_compile_options(
#    softfloat
#    PRIVATE
#    -Wall
#    -Wno-conversion
#    -Wno-everything 
# )

target_compile_definitions(
   softfloat
   PUBLIC
   # "-DSOFTFLOAT_FAST_INT64 -DSOFTFLOAT_ROUND_EVEN -DINLINE_LEVEL=5 -DSOFTFLOAT_FAST_DIV32TO16 -DSOFTFLOAT_FAST_DIV64TO32"
   -DSOFTFLOAT_FAST_INT64
   -DSOFTFLOAT_ROUND_EVEN
   -DINLINE_LEVEL=5
   -DSOFTFLOAT_FAST_DIV32TO16
   -DSOFTFLOAT_FAST_DIV64TO32
)


# WASM SPECIFIC FLAGS
if(IS_WASM)
   target_compile_options(
      softfloat
      PRIVATE
      -Werror-implicit-function-declaration
      -allow-sse
   )
endif()

target_include_directories(
   softfloat
   PRIVATE
   source/include
   source/${ARCH_SOURCE_TYPE}
   build/${ARCH_BUILD_TYPE}
)

if(NOT SOFTFLOAT_SKIP_INSTALL)

   install(
      TARGETS softfloat
      EXPORT softfloat-config
      RUNTIME DESTINATION bin
      ARCHIVE DESTINATION lib
      LIBRARY DESTINATION lib
      PUBLIC_HEADER DESTINATION include/softfloat
   )

   install(FILES ${softfloat_headers} DESTINATION include/softfloat)

   install(
      EXPORT softfloat-config
      FILE softfloat-config.cmake
      NAMESPACE softfloat::
      DESTINATION share/softfloat
   )

endif()
