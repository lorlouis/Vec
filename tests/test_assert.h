#ifndef TEST_ASSERT_H
#define TEST_ASSERT_H 1

struct {
    int line;
    const char *func;
    const char *file;
    char *assertion;
} test_failed_data;

#define ASSERT(assert) do { \
    if(!(assert)) { \
        test_failed_data.line = __LINE__; \
        test_failed_data.func = __FUNCTION__; \
        test_failed_data.file = __FILE__; \
        test_failed_data.assertion = #assert; \
        goto cleanup; \
    } \
} while(0)

#endif
