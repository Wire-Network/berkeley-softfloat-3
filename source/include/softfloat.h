
/*============================================================================

This C header file is part of the SoftFloat IEEE Floating-Point Arithmetic
Package, Release 3e, by John R. Hauser.

Copyright 2011, 2012, 2013, 2014, 2015, 2016, 2017 The Regents of the
University of California.  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 1. Redistributions of source code must retain the above copyright notice,
    this list of conditions, and the following disclaimer.

 2. Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions, and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

 3. Neither the name of the University nor the names of its contributors may
    be used to endorse or promote products derived from this software without
    specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS "AS IS", AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE, ARE
DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=============================================================================*/


/*============================================================================
| Note:  If SoftFloat is made available as a general library for programs to
| use, it is strongly recommended that a platform-specific version of this
| header, "softfloat.h", be created that folds in "softfloat_types.h" and that
| eliminates all dependencies on compile-time macros.
*============================================================================*/


#ifndef softfloat_h
#define softfloat_h 1

#include <stdbool.h>
#include <stdint.h>
#include "softfloat_types.h"

#ifndef THREAD_LOCAL
#define THREAD_LOCAL
#endif

/*----------------------------------------------------------------------------
| Software floating-point underflow tininess-detection mode.
*----------------------------------------------------------------------------*/
extern THREAD_LOCAL uint_fast8_t softfloat_detectTininess;
enum {
    softfloat_tininess_beforeRounding = 0,
    softfloat_tininess_afterRounding  = 1
};

/*----------------------------------------------------------------------------
| Software floating-point rounding mode.  (Mode "odd" is supported only if
| SoftFloat is compiled with macro 'SOFTFLOAT_ROUND_ODD' defined.)
*----------------------------------------------------------------------------*/
extern THREAD_LOCAL uint_fast8_t softfloat_roundingMode;
enum {
    softfloat_round_near_even   = 0,
    softfloat_round_minMag      = 1,
    softfloat_round_min         = 2,
    softfloat_round_max         = 3,
    softfloat_round_near_maxMag = 4,
    softfloat_round_odd         = 6
};

/*----------------------------------------------------------------------------
| Software floating-point exception flags.
*----------------------------------------------------------------------------*/
extern THREAD_LOCAL uint_fast8_t softfloat_exceptionFlags;
enum {
    softfloat_flag_inexact   =  1,
    softfloat_flag_underflow =  2,
    softfloat_flag_overflow  =  4,
    softfloat_flag_infinite  =  8,
    softfloat_flag_invalid   = 16
};

/*----------------------------------------------------------------------------
| Routine to raise any or all of the software floating-point exception flags.
*----------------------------------------------------------------------------*/
void softfloat_raiseFlags( uint_fast8_t );

/*----------------------------------------------------------------------------
| Integer-to-floating-point conversion routines.
*----------------------------------------------------------------------------*/
softfloat16_t ui32_to_f16( uint32_t );
softfloat32_t ui32_to_f32( uint32_t );
softfloat64_t ui32_to_f64( uint32_t );
#ifdef SOFTFLOAT_FAST_INT64
extFloat80_t ui32_to_extF80( uint32_t );
softfloat128_t ui32_to_f128( uint32_t );
#endif
void ui32_to_extF80M( uint32_t, extFloat80_t * );
void ui32_to_f128M( uint32_t, softfloat128_t * );
softfloat16_t ui64_to_f16( uint64_t );
softfloat32_t ui64_to_f32( uint64_t );
softfloat64_t ui64_to_f64( uint64_t );
#ifdef SOFTFLOAT_FAST_INT64
extFloat80_t ui64_to_extF80( uint64_t );
softfloat128_t ui64_to_f128( uint64_t );
#endif
void ui64_to_extF80M( uint64_t, extFloat80_t * );
void ui64_to_f128M( uint64_t, softfloat128_t * );
softfloat16_t i32_to_f16( int32_t );
softfloat32_t i32_to_f32( int32_t );
softfloat64_t i32_to_f64( int32_t );
#ifdef SOFTFLOAT_FAST_INT64
extFloat80_t i32_to_extF80( int32_t );
softfloat128_t i32_to_f128( int32_t );
#endif
void i32_to_extF80M( int32_t, extFloat80_t * );
void i32_to_f128M( int32_t, softfloat128_t * );
softfloat16_t i64_to_f16( int64_t );
softfloat32_t i64_to_f32( int64_t );
softfloat64_t i64_to_f64( int64_t );
#ifdef SOFTFLOAT_FAST_INT64
extFloat80_t i64_to_extF80( int64_t );
softfloat128_t i64_to_f128( int64_t );
#endif
void i64_to_extF80M( int64_t, extFloat80_t * );
void i64_to_f128M( int64_t, softfloat128_t * );

/*----------------------------------------------------------------------------
| 16-bit (half-precision) floating-point operations.
*----------------------------------------------------------------------------*/
uint_fast32_t f16_to_ui32( softfloat16_t, uint_fast8_t, bool );
uint_fast64_t f16_to_ui64( softfloat16_t, uint_fast8_t, bool );
int_fast32_t f16_to_i32( softfloat16_t, uint_fast8_t, bool );
int_fast64_t f16_to_i64( softfloat16_t, uint_fast8_t, bool );
uint_fast32_t f16_to_ui32_r_minMag( softfloat16_t, bool );
uint_fast64_t f16_to_ui64_r_minMag( softfloat16_t, bool );
int_fast32_t f16_to_i32_r_minMag( softfloat16_t, bool );
int_fast64_t f16_to_i64_r_minMag( softfloat16_t, bool );
softfloat32_t f16_to_f32( softfloat16_t );
softfloat64_t f16_to_f64( softfloat16_t );
#ifdef SOFTFLOAT_FAST_INT64
extFloat80_t f16_to_extF80( softfloat16_t );
softfloat128_t f16_to_f128( softfloat16_t );
#endif
void f16_to_extF80M( softfloat16_t, extFloat80_t * );
void f16_to_f128M( softfloat16_t, softfloat128_t * );
softfloat16_t f16_roundToInt( softfloat16_t, uint_fast8_t, bool );
softfloat16_t f16_add( softfloat16_t, softfloat16_t );
softfloat16_t f16_sub( softfloat16_t, softfloat16_t );
softfloat16_t f16_mul( softfloat16_t, softfloat16_t );
softfloat16_t f16_mulAdd( softfloat16_t, softfloat16_t, softfloat16_t );
softfloat16_t f16_div( softfloat16_t, softfloat16_t );
softfloat16_t f16_rem( softfloat16_t, softfloat16_t );
softfloat16_t f16_sqrt( softfloat16_t );
bool f16_eq( softfloat16_t, softfloat16_t );
bool f16_le( softfloat16_t, softfloat16_t );
bool f16_lt( softfloat16_t, softfloat16_t );
bool f16_eq_signaling( softfloat16_t, softfloat16_t );
bool f16_le_quiet( softfloat16_t, softfloat16_t );
bool f16_lt_quiet( softfloat16_t, softfloat16_t );
bool f16_isSignalingNaN( softfloat16_t );

/*----------------------------------------------------------------------------
| 32-bit (single-precision) floating-point operations.
*----------------------------------------------------------------------------*/
uint_fast32_t f32_to_ui32( softfloat32_t, uint_fast8_t, bool );
uint_fast64_t f32_to_ui64( softfloat32_t, uint_fast8_t, bool );
int_fast32_t f32_to_i32( softfloat32_t, uint_fast8_t, bool );
int_fast64_t f32_to_i64( softfloat32_t, uint_fast8_t, bool );
uint_fast32_t f32_to_ui32_r_minMag( softfloat32_t, bool );
uint_fast64_t f32_to_ui64_r_minMag( softfloat32_t, bool );
int_fast32_t f32_to_i32_r_minMag( softfloat32_t, bool );
int_fast64_t f32_to_i64_r_minMag( softfloat32_t, bool );
softfloat16_t f32_to_f16( softfloat32_t );
softfloat64_t f32_to_f64( softfloat32_t );
#ifdef SOFTFLOAT_FAST_INT64
extFloat80_t f32_to_extF80( softfloat32_t );
softfloat128_t f32_to_f128( softfloat32_t );
#endif
void f32_to_extF80M( softfloat32_t, extFloat80_t * );
void f32_to_f128M( softfloat32_t, softfloat128_t * );
softfloat32_t f32_roundToInt( softfloat32_t, uint_fast8_t, bool );
softfloat32_t f32_add( softfloat32_t, softfloat32_t );
softfloat32_t f32_sub( softfloat32_t, softfloat32_t );
softfloat32_t f32_mul( softfloat32_t, softfloat32_t );
softfloat32_t f32_mulAdd( softfloat32_t, softfloat32_t, softfloat32_t );
softfloat32_t f32_div( softfloat32_t, softfloat32_t );
softfloat32_t f32_rem( softfloat32_t, softfloat32_t );
softfloat32_t f32_sqrt( softfloat32_t );
bool f32_eq( softfloat32_t, softfloat32_t );
bool f32_le( softfloat32_t, softfloat32_t );
bool f32_lt( softfloat32_t, softfloat32_t );
bool f32_eq_signaling( softfloat32_t, softfloat32_t );
bool f32_le_quiet( softfloat32_t, softfloat32_t );
bool f32_lt_quiet( softfloat32_t, softfloat32_t );
bool f32_isSignalingNaN( softfloat32_t );

/*----------------------------------------------------------------------------
| 64-bit (double-precision) floating-point operations.
*----------------------------------------------------------------------------*/
uint_fast32_t f64_to_ui32( softfloat64_t, uint_fast8_t, bool );
uint_fast64_t f64_to_ui64( softfloat64_t, uint_fast8_t, bool );
int_fast32_t f64_to_i32( softfloat64_t, uint_fast8_t, bool );
int_fast64_t f64_to_i64( softfloat64_t, uint_fast8_t, bool );
uint_fast32_t f64_to_ui32_r_minMag( softfloat64_t, bool );
uint_fast64_t f64_to_ui64_r_minMag( softfloat64_t, bool );
int_fast32_t f64_to_i32_r_minMag( softfloat64_t, bool );
int_fast64_t f64_to_i64_r_minMag( softfloat64_t, bool );
softfloat16_t f64_to_f16( softfloat64_t );
softfloat32_t f64_to_f32( softfloat64_t );
#ifdef SOFTFLOAT_FAST_INT64
extFloat80_t f64_to_extF80( softfloat64_t );
softfloat128_t f64_to_f128( softfloat64_t );
#endif
void f64_to_extF80M( softfloat64_t, extFloat80_t * );
void f64_to_f128M( softfloat64_t, softfloat128_t * );
softfloat64_t f64_roundToInt( softfloat64_t, uint_fast8_t, bool );
softfloat64_t f64_add( softfloat64_t, softfloat64_t );
softfloat64_t f64_sub( softfloat64_t, softfloat64_t );
softfloat64_t f64_mul( softfloat64_t, softfloat64_t );
softfloat64_t f64_mulAdd( softfloat64_t, softfloat64_t, softfloat64_t );
softfloat64_t f64_div( softfloat64_t, softfloat64_t );
softfloat64_t f64_rem( softfloat64_t, softfloat64_t );
softfloat64_t f64_sqrt( softfloat64_t );
bool f64_eq( softfloat64_t, softfloat64_t );
bool f64_le( softfloat64_t, softfloat64_t );
bool f64_lt( softfloat64_t, softfloat64_t );
bool f64_eq_signaling( softfloat64_t, softfloat64_t );
bool f64_le_quiet( softfloat64_t, softfloat64_t );
bool f64_lt_quiet( softfloat64_t, softfloat64_t );
bool f64_isSignalingNaN( softfloat64_t );

/*----------------------------------------------------------------------------
| Rounding precision for 80-bit extended double-precision floating-point.
| Valid values are 32, 64, and 80.
*----------------------------------------------------------------------------*/
extern THREAD_LOCAL uint_fast8_t extF80_roundingPrecision;

/*----------------------------------------------------------------------------
| 80-bit extended double-precision floating-point operations.
*----------------------------------------------------------------------------*/
#ifdef SOFTFLOAT_FAST_INT64
uint_fast32_t extF80_to_ui32( extFloat80_t, uint_fast8_t, bool );
uint_fast64_t extF80_to_ui64( extFloat80_t, uint_fast8_t, bool );
int_fast32_t extF80_to_i32( extFloat80_t, uint_fast8_t, bool );
int_fast64_t extF80_to_i64( extFloat80_t, uint_fast8_t, bool );
uint_fast32_t extF80_to_ui32_r_minMag( extFloat80_t, bool );
uint_fast64_t extF80_to_ui64_r_minMag( extFloat80_t, bool );
int_fast32_t extF80_to_i32_r_minMag( extFloat80_t, bool );
int_fast64_t extF80_to_i64_r_minMag( extFloat80_t, bool );
softfloat16_t extF80_to_f16( extFloat80_t );
softfloat32_t extF80_to_f32( extFloat80_t );
softfloat64_t extF80_to_f64( extFloat80_t );
softfloat128_t extF80_to_f128( extFloat80_t );
extFloat80_t extF80_roundToInt( extFloat80_t, uint_fast8_t, bool );
extFloat80_t extF80_add( extFloat80_t, extFloat80_t );
extFloat80_t extF80_sub( extFloat80_t, extFloat80_t );
extFloat80_t extF80_mul( extFloat80_t, extFloat80_t );
extFloat80_t extF80_div( extFloat80_t, extFloat80_t );
extFloat80_t extF80_rem( extFloat80_t, extFloat80_t );
extFloat80_t extF80_sqrt( extFloat80_t );
bool extF80_eq( extFloat80_t, extFloat80_t );
bool extF80_le( extFloat80_t, extFloat80_t );
bool extF80_lt( extFloat80_t, extFloat80_t );
bool extF80_eq_signaling( extFloat80_t, extFloat80_t );
bool extF80_le_quiet( extFloat80_t, extFloat80_t );
bool extF80_lt_quiet( extFloat80_t, extFloat80_t );
bool extF80_isSignalingNaN( extFloat80_t );
#endif
uint_fast32_t extF80M_to_ui32( const extFloat80_t *, uint_fast8_t, bool );
uint_fast64_t extF80M_to_ui64( const extFloat80_t *, uint_fast8_t, bool );
int_fast32_t extF80M_to_i32( const extFloat80_t *, uint_fast8_t, bool );
int_fast64_t extF80M_to_i64( const extFloat80_t *, uint_fast8_t, bool );
uint_fast32_t extF80M_to_ui32_r_minMag( const extFloat80_t *, bool );
uint_fast64_t extF80M_to_ui64_r_minMag( const extFloat80_t *, bool );
int_fast32_t extF80M_to_i32_r_minMag( const extFloat80_t *, bool );
int_fast64_t extF80M_to_i64_r_minMag( const extFloat80_t *, bool );
softfloat16_t extF80M_to_f16( const extFloat80_t * );
softfloat32_t extF80M_to_f32( const extFloat80_t * );
softfloat64_t extF80M_to_f64( const extFloat80_t * );
void extF80M_to_f128M( const extFloat80_t *, softfloat128_t * );
void
 extF80M_roundToInt(
     const extFloat80_t *, uint_fast8_t, bool, extFloat80_t * );
void extF80M_add( const extFloat80_t *, const extFloat80_t *, extFloat80_t * );
void extF80M_sub( const extFloat80_t *, const extFloat80_t *, extFloat80_t * );
void extF80M_mul( const extFloat80_t *, const extFloat80_t *, extFloat80_t * );
void extF80M_div( const extFloat80_t *, const extFloat80_t *, extFloat80_t * );
void extF80M_rem( const extFloat80_t *, const extFloat80_t *, extFloat80_t * );
void extF80M_sqrt( const extFloat80_t *, extFloat80_t * );
bool extF80M_eq( const extFloat80_t *, const extFloat80_t * );
bool extF80M_le( const extFloat80_t *, const extFloat80_t * );
bool extF80M_lt( const extFloat80_t *, const extFloat80_t * );
bool extF80M_eq_signaling( const extFloat80_t *, const extFloat80_t * );
bool extF80M_le_quiet( const extFloat80_t *, const extFloat80_t * );
bool extF80M_lt_quiet( const extFloat80_t *, const extFloat80_t * );
bool extF80M_isSignalingNaN( const extFloat80_t * );

/*----------------------------------------------------------------------------
| 128-bit (quadruple-precision) floating-point operations.
*----------------------------------------------------------------------------*/
#ifdef SOFTFLOAT_FAST_INT64
uint_fast32_t f128_to_ui32( softfloat128_t, uint_fast8_t, bool );
uint_fast64_t f128_to_ui64( softfloat128_t, uint_fast8_t, bool );
int_fast32_t f128_to_i32( softfloat128_t, uint_fast8_t, bool );
int_fast64_t f128_to_i64( softfloat128_t, uint_fast8_t, bool );
uint_fast32_t f128_to_ui32_r_minMag( softfloat128_t, bool );
uint_fast64_t f128_to_ui64_r_minMag( softfloat128_t, bool );
int_fast32_t f128_to_i32_r_minMag( softfloat128_t, bool );
int_fast64_t f128_to_i64_r_minMag( softfloat128_t, bool );
softfloat16_t f128_to_f16( softfloat128_t );
softfloat32_t f128_to_f32( softfloat128_t );
softfloat64_t f128_to_f64( softfloat128_t );
extFloat80_t f128_to_extF80( softfloat128_t );
softfloat128_t f128_roundToInt( softfloat128_t, uint_fast8_t, bool );
softfloat128_t f128_add( softfloat128_t, softfloat128_t );
softfloat128_t f128_sub( softfloat128_t, softfloat128_t );
softfloat128_t f128_mul( softfloat128_t, softfloat128_t );
softfloat128_t f128_mulAdd( softfloat128_t, softfloat128_t, softfloat128_t );
softfloat128_t f128_div( softfloat128_t, softfloat128_t );
softfloat128_t f128_rem( softfloat128_t, softfloat128_t );
softfloat128_t f128_sqrt( softfloat128_t );
bool f128_eq( softfloat128_t, softfloat128_t );
bool f128_le( softfloat128_t, softfloat128_t );
bool f128_lt( softfloat128_t, softfloat128_t );
bool f128_eq_signaling( softfloat128_t, softfloat128_t );
bool f128_le_quiet( softfloat128_t, softfloat128_t );
bool f128_lt_quiet( softfloat128_t, softfloat128_t );
bool f128_isSignalingNaN( softfloat128_t );
#endif
uint_fast32_t f128M_to_ui32( const softfloat128_t *, uint_fast8_t, bool );
uint_fast64_t f128M_to_ui64( const softfloat128_t *, uint_fast8_t, bool );
int_fast32_t f128M_to_i32( const softfloat128_t *, uint_fast8_t, bool );
int_fast64_t f128M_to_i64( const softfloat128_t *, uint_fast8_t, bool );
uint_fast32_t f128M_to_ui32_r_minMag( const softfloat128_t *, bool );
uint_fast64_t f128M_to_ui64_r_minMag( const softfloat128_t *, bool );
int_fast32_t f128M_to_i32_r_minMag( const softfloat128_t *, bool );
int_fast64_t f128M_to_i64_r_minMag( const softfloat128_t *, bool );
softfloat16_t f128M_to_f16( const softfloat128_t * );
softfloat32_t f128M_to_f32( const softfloat128_t * );
softfloat64_t f128M_to_f64( const softfloat128_t * );
void f128M_to_extF80M( const softfloat128_t *, extFloat80_t * );
void f128M_roundToInt( const softfloat128_t *, uint_fast8_t, bool, softfloat128_t * );
void f128M_add( const softfloat128_t *, const softfloat128_t *, softfloat128_t * );
void f128M_sub( const softfloat128_t *, const softfloat128_t *, softfloat128_t * );
void f128M_mul( const softfloat128_t *, const softfloat128_t *, softfloat128_t * );
void
 f128M_mulAdd(
     const softfloat128_t *, const softfloat128_t *, const softfloat128_t *, softfloat128_t *
 );
void f128M_div( const softfloat128_t *, const softfloat128_t *, softfloat128_t * );
void f128M_rem( const softfloat128_t *, const softfloat128_t *, softfloat128_t * );
void f128M_sqrt( const softfloat128_t *, softfloat128_t * );
bool f128M_eq( const softfloat128_t *, const softfloat128_t * );
bool f128M_le( const softfloat128_t *, const softfloat128_t * );
bool f128M_lt( const softfloat128_t *, const softfloat128_t * );
bool f128M_eq_signaling( const softfloat128_t *, const softfloat128_t * );
bool f128M_le_quiet( const softfloat128_t *, const softfloat128_t * );
bool f128M_lt_quiet( const softfloat128_t *, const softfloat128_t * );
bool f128M_isSignalingNaN( const softfloat128_t * );

#endif

