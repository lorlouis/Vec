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
    ASSERT(intv.capacity != 0);
    ASSERT(intv.len == 3);
    ASSERT(intv.data[0] == 42);
    ASSERT(intv.data[1] == 5);
    ASSERT(intv.data[2] == 7);
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
    ASSERT(intv.capacity != 0);
    ASSERT(intv.len == 1);
    ASSERT(intv.data[0] == 42);
cleanup:
    int_vec_cleanup(&intv);
}

void int_get_test(void) {
    struct int_vec intv = {0};
    int_vec_init(&intv, 0, 0);
    int_vec_push(&intv, 42);
    ASSERT(*int_vec_get(&intv, 0) == 42);
    ASSERT(int_vec_get(&intv, 1) == 0);
cleanup:
    int_vec_cleanup(&intv);
}

void int_pop_test(void) {
    int buf = 0;
    struct int_vec intv = {0};
    int_vec_init(&intv, 0, 0);
    int_vec_push(&intv, 42);
    int_vec_push(&intv, 24);
    ASSERT(intv.data[0] == 42);
    ASSERT(intv.data[1] == 24);
    ASSERT(intv.len == 2);
    ASSERT(int_vec_pop(&intv, 0) == 0);
    ASSERT(int_vec_get(&intv, 1) == 0);
    ASSERT(intv.len == 1);
    ASSERT(int_vec_pop(&intv, &buf) == 0);
    ASSERT(intv.len == 0);
    ASSERT(int_vec_get(&intv, 0) == 0);
    ASSERT(buf == 42);
cleanup:
    int_vec_cleanup(&intv);
}

void int_remove_test(void) {
    int buf = 0;
    struct int_vec intv = {0};
    int_vec_init(&intv, 0, 0);
    int_vec_push(&intv, 42);
    int_vec_push(&intv, 24);
    int_vec_push(&intv, 88);
    ASSERT(intv.data[0] == 42);
    ASSERT(intv.data[1] == 24);
    ASSERT(intv.data[2] == 88);
    ASSERT(intv.len == 3);
    ASSERT(int_vec_remove(&intv, 3, 0) == -1);
    ASSERT(intv.data[0] == 42);
    ASSERT(intv.data[1] == 24);
    ASSERT(intv.data[2] == 88);
    ASSERT(intv.len == 3);
    ASSERT(int_vec_remove(&intv, 2, 0) == 0);
    ASSERT(intv.data[0] == 42);
    ASSERT(intv.data[1] == 24);
    ASSERT(intv.len == 2);
    ASSERT(int_vec_remove(&intv, 0, 0) == 0);
    ASSERT(intv.data[0] == 24);
    ASSERT(intv.len == 1);
    ASSERT(int_vec_remove(&intv, 0, &buf) == 0);
    ASSERT(intv.data[0] == 24);
    ASSERT(buf == 24);
    ASSERT(intv.len == 0);
    ASSERT(int_vec_remove(&intv, 0, &buf) == -1);
    ASSERT(intv.len == 0);
cleanup:
    int_vec_cleanup(&intv);
}

void int_shrink_test(void) {
    struct int_vec intv = {0};
    int_vec_init(&intv, 0, 0);
    int_vec_push(&intv, 42);
    ASSERT(intv.len == 1);
    ASSERT(intv.capacity != 1);
    ASSERT(int_vec_shrink(&intv) == 0);
    ASSERT(intv.len == 1);
    ASSERT(intv.capacity == 1);
cleanup:
    int_vec_cleanup(&intv);
}

/* make sure poped values are freed if `buf` is null and
 * the cleanup function is not null */
void int_pop_free_test(void) {
    struct int_vec intv = {0};
    test_cleanup_called = 0;
    int_vec_init(&intv, 0, test_cleanup);
    int_vec_push(&intv, 42);
    int_vec_pop(&intv, 0);
    ASSERT(test_cleanup_called == 1);
cleanup:
    int_vec_cleanup(&intv);
}

/* make sure removed values are freed if `buf` is null and
 * the cleanup function is not null */
void int_remove_free_test(void) {
    struct int_vec intv = {0};
    test_cleanup_called = 0;
    int_vec_init(&intv, 0, test_cleanup);
    int_vec_push(&intv, 42);
    int_vec_push(&intv, 24);
    int_vec_remove(&intv, 0, 0);
    ASSERT(test_cleanup_called == 1);
cleanup:
    int_vec_cleanup(&intv);
}
