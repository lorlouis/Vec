#include "test_assert.h"
#include "../vec.h"

VEC(int_vec, int);
VEC_FUNCTIONS(int_vec, int);


static int test_cleanup_called = 0;
void test_cleanup(int *_i) {
    test_cleanup_called += 1;
}

void int_init_test(void) {
    struct int_vec intv = {0};
    int_vec_init(&intv, 0, test_cleanup);
    int_vec_push(&intv, 42);
    int_vec_push(&intv, 5);
    int_vec_push(&intv, 7);
    ASSERT(intv.capacity == 0);
    ASSERT(intv.len == 3);
    ASSERT(intv.data[0] == 42);
    ASSERT(intv.data[0] == 5);
    ASSERT(intv.data[0] == 7);
    int_vec_cleanup(&intv);
    ASSERT(test_cleanup_called == 3);
    /* skip cleanup to not double free */
    return;
cleanup:
    int_vec_cleanup(&intv);
}

void int_push_test(void) {
    struct int_vec intv = {0};
    int_vec_init(&intv, 0, 0);
    int_vec_push(&intv, 42);
    ASSERT(intv.capacity == 0);
    ASSERT(intv.len == 1);
    ASSERT(intv.data[0] == 42);
cleanup:
    int_vec_cleanup(&intv);
}
