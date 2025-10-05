#include <check.h>
#include <stdlib.h>

/* Declarations of suite factories */
Suite* smoke_suite(void);
Suite* calendar_suite(void);

int main(void)
{
    int failed = 0;
    SRunner *sr = srunner_create(smoke_suite());
    srunner_add_suite(sr, calendar_suite());

    srunner_run_all(sr, CK_NORMAL);
    failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
