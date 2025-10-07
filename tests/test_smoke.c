#include <assert.h>
#include "notes.h"

/* This file only tests the pure helpers (no I/O). */

static void test_days_in_month(void) {
    assert(days_in_month(1, 2025) == 31);
    assert(days_in_month(2, 2024) == 29);   // leap year
    assert(days_in_month(2, 1900) == 28);   // century, NOT leap
    assert(days_in_month(2, 2000) == 29);   // divisible by 400, leap
    assert(days_in_month(12, 2025) == 31);
    assert(days_in_month(13, 2025) == 0);   // invalid month -> 0
}

static void test_is_valid_date(void) {
    assert(is_valid_date(31, 1, 2025) == 1);
    assert(is_valid_date(31, 4, 2025) == 0);   // April has 30
    assert(is_valid_date(29, 2, 2024) == 1);   // leap ok
    assert(is_valid_date(29, 2, 2023) == 0);   // non-leap
    assert(is_valid_date(32,12, 2023) == 0);
    assert(is_valid_date( 0,12, 2023) == 0);
    assert(is_valid_date( 1,13, 2023) == 0);
    assert(is_valid_date( 1, 1,    0) == 0);   // year must be >= 1
}

int main(void) {
    test_days_in_month();
    test_is_valid_date();
    return 0;  // if any assert fails, program aborts non-zero
}
