// Rounding mode and exception flags are per-thread: a worker starts from the defaults and its
// state never leaks into the thread that spawned it (THREAD_LOCAL from the softfloat target).
extern "C" {
#include <softfloat.h>
}

#include <cstdint>
#include <cstdio>
#include <thread>

namespace {

int failures = 0;

void expect(bool ok, const char* what)
{
    if (!ok) {
        std::fprintf(stderr, "FAIL: %s\n", what);
        ++failures;
    }
}

const softfloat32_t one = {0x3f800000u};
const softfloat32_t zero = {0u};
const softfloat32_t minus_one = {0xbf800000u};

} // namespace

int main()
{
    expect(softfloat_roundingMode == softfloat_round_near_even, "main starts with round_near_even");
    expect(softfloat_exceptionFlags == 0, "main starts with no exception flags");

    softfloat_roundingMode = softfloat_round_max;
    f32_div(one, zero);
    expect(softfloat_exceptionFlags == softfloat_flag_infinite, "main: 1/0 raises infinite");

    uint_fast8_t worker_mode = 0xff;
    uint_fast8_t worker_flags_before = 0xff;
    uint_fast8_t worker_flags_after = 0;
    std::thread worker([&] {
        worker_mode = softfloat_roundingMode;
        worker_flags_before = softfloat_exceptionFlags;
        softfloat_roundingMode = softfloat_round_minMag;
        f32_sqrt(minus_one);
        worker_flags_after = softfloat_exceptionFlags;
    });
    worker.join();

    expect(worker_mode == softfloat_round_near_even, "worker starts with round_near_even, not main's round_max");
    expect(worker_flags_before == 0, "worker does not see main's infinite flag");
    expect(worker_flags_after == softfloat_flag_invalid, "worker: sqrt(-1) raises invalid");
    expect(softfloat_roundingMode == softfloat_round_max, "main keeps round_max after the worker set round_minMag");
    expect(softfloat_exceptionFlags == softfloat_flag_infinite, "main does not see the worker's invalid flag");

    return failures == 0 ? 0 : 1;
}
