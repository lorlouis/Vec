#ifndef AL_H
#define AL_H 1

#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/* defines a struct arraylist of name `name` that holds `type` */
#define ARRAYLIST(name, type)\
struct name { \
    size_t len; \
    size_t capacity; \
    type *data; \
};

/* defines the function prototypes for the arraylist */
#define ARRAYLIST_FUNCTIONS(name, type)\
struct name* name##_new(unsigned int initial_capacity) { \
    type *data = calloc(initial_capacity, sizeof(type)); \
    if(data == 0) return 0; \
    struct name* al = calloc(sizeof(struct name), 1); \
    if(al == 0) return 0; \
    al->capacity = initial_capacity; \
    al->data = data; \
    return al; \
} \
/* frees the arraylist */ \
void name##_free(struct name *al) { \
    free(al->data);\
    free(al);\
}\
/* gets the value at `index` */ \
type name##_get(struct name *al, int index) { \
    return al->data[index]; \
} \
/* sets the value at `index` to data
 * UB if `index` > al->capacity */ \
type name##_set(struct name* const al, int index, type data) { \
    return al->data[index] = data; \
} \
/* returns 1 if it was successful 0 otherwise */ \
int name##_add(struct name * restrict const al, type data) { \
    /* realloc if the array is full */ \
    if(al->len >= al->capacity) { \
        if(((SIZE_MAX / sizeof(data)) / 2) < al->capacity) return 0; \
        void *new_data = realloc(al->data, (al->capacity*2) * sizeof(data)); \
        /* failed to alloc memory */ \
        if(new_data == 0) return 0; \
        al->capacity *=2; \
        al->data = new_data; \
    } \
    al->data[al->len] = data; \
    al->len++; \
    return 1; \
} \
/* removed the element at `index` by shifting to
 * the left every element after index by one */ \
int name##_remove(struct name * restrict const al, int index) { \
    al->len--; \
    if(index == al->len) { \
        al->data[index] = 0; \
        return 1; \
    } \
    size_t diff = (al->capacity -1) - index; \
    /* TODO only shift up to len and not capacity for better performance */ \
    memmove(al->data+index, al->data+index+1, diff); \
    al->data[al->capacity-1] = 0; \
    return 1; \
}


/* defines the function prototypes for the arraylist */
#define ARRAYLIST_PROTYPE(name, type)\
struct name* name##_new(unsigned int initial_capacity); \
/* frees the arraylist */ \
void name##_free(struct name *al); \
/* gets the value at `index` */ \
type name##_get(struct name *al, int index); \
/* sets the value at `index` to data
 * UB if `index` > al->capacity */ \
type name##_set(struct name* const al, int index, type data); \
/* returns 1 if it was successful 0 otherwise */ \
int name##_add(struct name * restrict const al, type data); \
/* removed the element at `index` by shifting to
 * the left every element after index by one */ \
int name##_remove(struct name * restrict const al, int index);
#endif
