

/* If your project has a public header, include it: */
// #include "calendar.h"

/* Fallback prototypes if no public header is available. */
int is_leap_year(int year);
int days_in_month(int month, int year);

/* ---- tests (must be file-scope) ---- */
START_TEST(test_leap_year)
{
    ck_assert_int_eq(is_leap_year(2000), 1); /* divisible by 400 => leap */
    ck_assert_int_eq(is_leap_year(1900), 0); /* divisible by 100 but not 400 => not leap */
    ck_assert_int_eq(is_leap_year(2024), 1); /* typical leap year */
    ck_assert_int_eq(is_leap_year(2023), 0); /* typical non-leap year */
}
END_TEST

START_TEST(test_days_in_month)
{
    ck_assert_int_eq(days_in_month(2, 2024), 29); /* leap */
    ck_assert_int_eq(days_in_month(2, 2023), 28); /* non-leap */
    ck_assert_int_eq(days_in_month(1, 2023), 31);
    ck_assert_int_eq(days_in_month(4, 2023), 30);
}
END_TEST

/* ---- suite factory ---- */
Suite* calendar_suite(void)
{
    Suite *s = suite_create("calendar");
    TCase *tc = tcase_create("core");

    tcase_add_test(tc, test_leap_year);
    tcase_add_test(tc, test_days_in_month);
    suite_add_tcase(s, tc);
    return s;
}
