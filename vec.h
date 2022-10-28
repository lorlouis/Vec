#ifndef VEC_H
#define VEC_H 1

#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/* defines a struct vec of name `name` that holds `type` */
#define VEC(name, type)\
struct name { \
    /* number of elems in list */ \
    size_t len; \
    /* capacity in number of elems */ \
    size_t capacity; \
    type *data; \
    void (*cleanup_fn)(type*); \
}

/* defines the function prototypes for the vec */
#define VEC_FUNCTIONS(name, type)\
size_t name##_len(struct name * const vec) { \
    return vec->len; \
} \
/* mallocs Vec.data */ \
int name##_init(struct name * const vec, unsigned int initial_capacity, void (*cleanup_fn)(type*)) { \
    type *data = 0; \
    if(initial_capacity) { \
        data = calloc(initial_capacity, sizeof(type)); \
        if(data == 0) return 0; \
    } \
    vec->len = 0; \
    vec->capacity = initial_capacity; \
    vec->data = data; \
    vec->cleanup_fn = cleanup_fn; \
    return 1; \
} \
/* frees the vec */ \
void name##_cleanup(struct name * const vec) { \
    if(vec->cleanup_fn) { \
        for(int i = 0; i < vec->len; i++) { \
            vec->cleanup_fn(vec->data + i); \
        }\
    } \
    free(vec->data); \
    vec->data = 0; \
    vec->len = 0; \
    vec->capacity = 0; \
}\
/* gets a pointer to value at `index` if it exists */ \
type* name##_get(struct name * const vec, int index) { \
    if(index >= vec->len) return 0; \
    return vec->data + index; \
} \
/* returns 0 if it was successful -1 otherwise */ \
int name##_push(struct name * const vec, type data) { \
    /* realloc if the array is full */ \
    if(vec->len >= vec->capacity) { \
        if(((SIZE_MAX / sizeof(data)) / 2) < vec->capacity) return 0; \
        size_t new_cap = (vec->capacity*2); \
        if(!vec->capacity) { \
            new_cap = 4; \
        } \
        type *new_data = realloc(vec->data,  new_cap * sizeof(data)); \
        /* failed to vecloc memory */ \
        if(new_data == 0) return -1; \
        vec->capacity = new_cap; \
        vec->data = new_data; \
    } \
    vec->data[vec->len] = data; \
    vec->len++; \
    return 0; \
} \
/* Removes the last value in the vec and copies it into `buf` if `buf` is not 0
 * Return -1 if vec is of len 0, 1 otherwise */ \
int name##_pop(struct name * const vec, type *buf) { \
    if(vec->len == 0) return -1; \
    if(buf) { \
        memcpy(buf, &vec->data[vec->len-1], sizeof(type)); \
    } \
    else if(vec->cleanup_fn) { \
        vec->cleanup_fn(&vec->data[vec->len-1]); \
    } \
    vec->len -= 1; \
    return 0; \
} \
/* removed the element at `index` by shifting to
 * the left every element after index by one */ \
int name##_remove(struct name * const vec, int index, type *buf) { \
    if(vec->len <= index || vec->len == 0) { \
        return -1; \
    } \
    if(buf) { \
        memcpy(buf, vec->data + index, sizeof(type)); \
    } \
    else if(vec->cleanup_fn) { \
        vec->cleanup_fn(vec->data + index); \
    } \
    vec->len--; \
    memmove(vec->data+index, vec->data+index+1, (vec->len - index)*sizeof(type));\
    return 0; \
} \
/* shrinks the capacity of the vec to it's current length */ \
int name##_shrink(struct name * const vec) { \
    if(vec->capacity == vec->len) { \
        return 0; \
    } \
    type *ret = realloc(vec->data, vec->len * sizeof(type)); \
    if(ret == 0) return -1; \
    vec->capacity = vec->len; \
    vec->data = ret; \
    return 0; \
}

/* defines the function prototypes for the vec */
#define VEC_PROTYPE(name, type) \
size_t name##_len(struct name * const vec); \
/* mallocs vec.data */ \
int name##_init(struct name * const vec, unsigned int initial_capacity, void (*cleanup_fn)(type*)); \
/* frees the vec's data */ \
void name##_cleanup(struct name * const vec); \
/* returns a pointer to the value at index or 0 */ \
type name##_get(struct name * const vec, int index); \
/* returns 0 if it was successful -1 otherwise */ \
int name##_push(struct name * const vec, type data); \
/* Removes the last value in the vec and copies it into `buf` if `buf` is not 0
 * Return -1 if vec is of len 0, 1 otherwise */ \
int name##_pop(struct name * const vec, type *buf); \
/* removed the element at `index` by shifting to
 * the left every element after index by one
 * copies the value removed into `buf` if it is not 0 */ \
int name##_remove(struct name * const vec, int index, type *buf); \
/* shrinks the capacity of the vec to it's current length */ \
int name##_shrink(struct name * const vec)

#endif
