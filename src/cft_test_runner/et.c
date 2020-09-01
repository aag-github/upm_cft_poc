#include <common_c.h>
#include "et.h"

size_t
et_test_case_count(void)
{
    const size_t section_size = (char*)&__stop_et_test_cases - (char*)&__start_et_test_cases;

    return section_size / sizeof(test_case_t);
}

size_t
et_get_all_tests(test_case_t** test_cases, size_t size)
{
    size_t tc_count = 0;
    for (test_case_t* tc = &__start_et_test_cases; tc < &__stop_et_test_cases && tc_count < size; ++tc) {
        test_cases[tc_count++] = tc;
    }
    return tc_count;
}
