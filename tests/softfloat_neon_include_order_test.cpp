#include <arm_neon.h>
#include <softfloat/softfloat.hpp>

#ifndef SOFTFLOAT_DISABLE_LEGACY_TYPE_ALIASES
#error "softfloat target must disable legacy aliases for NEON include-order safety"
#endif

static_assert(sizeof(softfloat16_t) == 2, "softfloat16_t must be 16 bits");
static_assert(sizeof(softfloat32_t) == 4, "softfloat32_t must be 32 bits");
static_assert(sizeof(softfloat64_t) == 8, "softfloat64_t must be 64 bits");
static_assert(sizeof(softfloat128_t) == 16, "softfloat128_t must be 128 bits");

int main()
{
    return 0;
}
