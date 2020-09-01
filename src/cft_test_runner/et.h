#ifndef CFT_TEST_RUNNER_ET_H_
#define CFT_TEST_RUNNER_ET_H_

#include "stddef.h"

struct test_case_s {
    char name[150];
    void (*func)();
    size_t num_workers;
};
typedef struct test_case_s test_case_t;

size_t et_test_case_count();
size_t et_get_all_tests();

//private
extern test_case_t __start_et_test_cases;
extern test_case_t __stop_et_test_cases;
#define ET_TC_SECTION "et_test_cases"
#define ET_TC_ATTR __attribute__((aligned(8), used, section(ET_TC_SECTION)))

#define ET_STR_IMPL(a) #a
#define ET_STR(a) ET_STR_IMPL(a)
#define ET_TEST_CASE_BASE(tc_, num_workers_)                          \
    static void tc_ (void);                                                               \
    ET_TC_ATTR static test_case_t et_test_case_ ## tc_ = {                                \
        .name          = ET_STR(tc_),                                                     \
        .func          = tc_,                                                             \
        .num_workers   = num_workers_                                                     \
    };                                                                                    \
    __attribute__((used))

#define TEST(tc_, num_workers_) ET_TEST_CASE_BASE(tc_, num_workers_) \
        static void tc_ (void)

#endif /* CFT_TEST_RUNNER_ET_H_ */
