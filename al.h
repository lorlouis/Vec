#ifndef AL_H
#define AL_H 1

#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/* defines a struct arraylist of name `name` that holds `type` */
#define ARRAYLIST(name, type)\
struct name { \
    /* number of elems in list */ \
    size_t len; \
    /* capacity in number of elems */ \
    size_t capacity; \
    type *data; \
}

/* defines the function prototypes for the arraylist */
#define ARRAYLIST_FUNCTIONS(name, type)\
size_t name##_len(struct name * const al) { \
    return al->len; \
} \
/* mallocs ArrayList.data */ \
int name##_init(struct name * const al, unsigned int initial_capacity) { \
    type *data = calloc(initial_capacity, sizeof(type)); \
    if(data == 0) return 0; \
    al->len = 0; \
    al->capacity = initial_capacity; \
    al->data = data; \
    return 1; \
} \
/* frees the arraylist */ \
void name##_free(struct name * const al) { \
    free(al->data);\
}\
/* gets the value at `index` */ \
type name##_get(struct name * const al, int index) { \
    return al->data[index]; \
} \
/* gets a pointer to value at `index` */ \
type* name##_getref(struct name * const al, int index) { \
    return al->data+index; \
} \
/* returns 1 if it was successful 0 otherwise */ \
int name##_add(struct name * const al, type data) { \
    /* realloc if the array is full */ \
    if(al->len >= al->capacity) { \
        if(((SIZE_MAX / sizeof(data)) / 2) < al->capacity) return 0; \
        type *new_data = realloc(al->data, (al->capacity*2) * sizeof(data)); \
        /* failed to alloc memory */ \
        if(new_data == 0) return 0; \
        al->capacity *=2; \
        al->data = new_data; \
    } \
    al->data[al->len] = data; \
    al->len++; \
    return 1; \
} \
/* sets the value at `index` to data
 * fails if index > len */ \
int name##_set(struct name* const al, int index, type data) { \
    if(index == al->len) { \
        return name##_add(al, data); \
    } \
    else if(index > al->len) return 0; \
    al->data[index] = data; \
    return 1; \
} \
/* removed the element at `index` by shifting to
 * the left every element after index by one */ \
type name##_remove(struct name * const al, int index) { \
    type data = al->data[index]; \
    al->len--; \
    if(index == al->len) { \
        return data; \
    } \
    memmove(al->data+index, al->data+index+1, (al->len - index)*sizeof(type));\
    return data; \
} \
/* shrinks the capacity of the list to fit the number of elems present */ \
int name##_shrink(struct name * const al) { \
    type *ret = realloc(al->data, al->len * sizeof(type)); \
    if(ret == 0) return 0; \
    al->capacity = al->len; \
    al->data = ret; \
    return 1; \
}

/* defines the function prototypes for the arraylist */
#define ARRAYLIST_PROTYPE(name, type) \
size_t name##_len(struct name * const al); \
/* mallocs al.data */ \
int name##_init(struct name * const al, unsigned int initial_capacity); \
/* frees the arraylist's data */ \
void name##_free(struct name * const al); \
/* gets the value at `index` */ \
type name##_get(struct name * const al, int index); \
/* gets a pointer to value at `index` */ \
type* name##_getref(struct name * const al, int index); \
/* returns 1 if it was successful 0 otherwise */ \
int name##_add(struct name * const al, type data); \
/* sets the value at `index` to data
 * fails if index > len */ \
int name##_set(struct name * const al, int index, type data); \
/* removed the element at `index` by shifting to
 * the left every element after index by one
 * returns the removed element */ \
type name##_remove(struct name * const al, int index); \
/* shrinks the capacity of the list to fit the number of elems present */ \
int name##_shrink(struct name * const al)

#endif
