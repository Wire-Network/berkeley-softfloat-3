#pragma once

#include <cstring>
#include <softfloat_types.h>

#ifndef THREAD_LOCAL
#define THREAD_LOCAL __thread
#endif
extern "C" {
/*----------------------------------------------------------------------------
| Integer-to-floating-point conversion routines.
*----------------------------------------------------------------------------*/
softfloat16_t ui32_to_f16( uint32_t );
softfloat32_t ui32_to_f32( uint32_t );
softfloat64_t ui32_to_f64( uint32_t );
softfloat128_t ui32_to_f128( uint32_t );
void ui32_to_f128M( uint32_t, softfloat128_t * );
softfloat16_t ui64_to_f16( uint64_t );
softfloat32_t ui64_to_f32( uint64_t );
softfloat64_t ui64_to_f64( uint64_t );
softfloat128_t ui64_to_f128( uint64_t );
void ui64_to_f128M( uint64_t, softfloat128_t * );
softfloat16_t i32_to_f16( int32_t );
softfloat32_t i32_to_f32( int32_t );
softfloat64_t i32_to_f64( int32_t );
softfloat128_t i32_to_f128( int32_t );
void i32_to_f128M( int32_t, softfloat128_t * );
softfloat16_t i64_to_f16( int64_t );
softfloat32_t i64_to_f32( int64_t );
softfloat64_t i64_to_f64( int64_t );
softfloat128_t i64_to_f128( int64_t );
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
softfloat128_t f16_to_f128( softfloat16_t );
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
softfloat128_t f32_to_f128( softfloat32_t );

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
softfloat128_t f64_to_f128( softfloat64_t );
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
| 128-bit (quadruple-precision) floating-point operations.
*----------------------------------------------------------------------------*/
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

void f128M_to_extF80M( const softfloat128_t *, extFloat80_t * );
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
bool isNaNF128( const softfloat128_t * );
};

inline bool operator == (const softfloat32_t& lhs, const softfloat32_t& rhs) {
   return f32_eq(lhs, rhs);
}

inline bool operator != (const softfloat32_t& lhs, const softfloat32_t& rhs) {
   return !f32_eq(lhs, rhs);
}

inline bool operator < (const softfloat32_t& lhs, const softfloat32_t& rhs) {
   return f32_lt(lhs, rhs);
}

inline bool operator > (const softfloat32_t& lhs, const softfloat32_t& rhs) {
   return f32_lt(rhs, lhs);
}

inline bool operator <= (const softfloat32_t& lhs, const softfloat32_t& rhs) {
   return f32_le(lhs, rhs);
}

inline bool operator >= (const softfloat32_t& lhs, const softfloat32_t& rhs) {
   return f32_le(rhs, lhs);
}

inline bool operator == (const softfloat64_t& lhs, const softfloat64_t& rhs) {
   return f64_eq(lhs, rhs);
}

inline bool operator != (const softfloat64_t& lhs, const softfloat64_t& rhs) {
   return !f64_eq(lhs, rhs);
}

inline bool operator < (const softfloat64_t& lhs, const softfloat64_t& rhs) {
   return f64_lt(lhs, rhs);
}

inline bool operator > (const softfloat64_t& lhs, const softfloat64_t& rhs) {
   return f64_lt(rhs, lhs);
}

inline bool operator <= (const softfloat64_t& lhs, const softfloat64_t& rhs) {
   return f64_le(lhs, rhs);
}

inline bool operator >= (const softfloat64_t& lhs, const softfloat64_t& rhs) {
   return f64_le(rhs, lhs);
}

inline bool operator == (const softfloat128_t& lhs, const softfloat128_t& rhs) {
   return f128_eq(lhs, rhs);
}

inline bool operator != (const softfloat128_t& lhs, const softfloat128_t& rhs) {
   return !f128_eq(lhs, rhs);
}

inline bool operator < (const softfloat128_t& lhs, const softfloat128_t& rhs) {
   return f128_lt(lhs, rhs);
}

inline bool operator > (const softfloat128_t& lhs, const softfloat128_t& rhs) {
   return f128_lt(rhs, lhs);
}

inline bool operator <= (const softfloat128_t& lhs, const softfloat128_t& rhs) {
   return f128_le(lhs, rhs);
}

inline bool operator >= (const softfloat128_t& lhs, const softfloat128_t& rhs) {
   return f128_le(rhs, lhs);
}

inline bool f32_sign_bit( softfloat32_t f )   { return f.v >> 31; }
inline bool f64_sign_bit( softfloat64_t f )   { return f.v >> 63; }
inline bool f128_sign_bit( softfloat128_t f ) { return f.v[1] >> 63; }

inline bool f32_is_nan( const softfloat32_t f ) {
   return ((f.v & 0x7FFFFFFF) > 0x7F800000);
}
inline bool f64_is_nan( const softfloat64_t f ) {
   return ((f.v & 0x7FFFFFFFFFFFFFFF) > 0x7FF0000000000000);
}
inline bool f128_is_nan( const softfloat128_t& f ) {
   return (((~(f.v[1]) & uint64_t( 0x7FFF000000000000 )) == 0) && (f.v[0] || ((f.v[1]) & uint64_t( 0x0000FFFFFFFFFFFF ))));
}

inline softfloat32_t f32_negative_infinity() {
   return {0xff800000ul};
}
inline softfloat32_t f32_positive_infinity() {
   return {0x7f800000ul};
}
inline softfloat64_t f64_negative_infinity() {
   return {0xfff0000000000000ull};
}
inline softfloat64_t f64_positive_infinity() {
   return {0x7ff0000000000000ull};
}
inline softfloat128_t f128_negative_infinity() {
   return {{0x0ull, 0xffff000000000000ull}};
}
inline softfloat128_t f128_positive_infinity() {
   return {{0x0ull, 0x7fff000000000000ull}};
}

inline softfloat32_t to_softfloat32( float f ) {
   softfloat32_t x;
   std::memcpy(&x, &f, sizeof(f));
   return x;
}
inline softfloat64_t to_softfloat64( double d ) {
   softfloat64_t x;
   std::memcpy(&x, &d, sizeof(d));
   return x;
}
inline float from_softfloat32( softfloat32_t f ) {
   float x;
   std::memcpy(&x, &f, sizeof(f));
   return x;
}
inline double from_softfloat64( softfloat64_t d ) {
   double x;
   std::memcpy(&x, &d, sizeof(d));
   return x;
}
