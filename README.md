# al.h A generic arraylist using the C preprocessor

## includes

* \_len(\*arraylist)
* \_init(initial\_capacity)
* \_free(\*arraylist)
* \_get(\*arraylist, index)
* \_getref(\*arraylist, index) \*
* \_add(\*arraylist, data)
* \_set(\*arraylist, index, data)
* \_remove(\*arraylist, index)
* \_shrink(\*arraylist)

\* storing the result of getref is discouraged as the pointer can go stale when the arraylist is resized

## How to use

```c
#include <stdio.h>

#include <assert.h>

#include "al.h"

ARRAYLIST(double_al, double);

ARRAYLIST_FUNCTIONS(double_al, double);

int main(int argc, const char **argv) {
    struct double_al dal;
    /* initialise the list with an initial capacity of 2 */
    double_al_init(&dal, 2);
    /* add elements to the list */
    double_al_add(&dal, 42.0f);
    double_al_add(&dal, 24.0f);
    /* get the number of elements in the list */
    assert(double_al_len(&dal) == 2);

    /* access the elements in the list */
    assert(double_al_get(&dal, 1) == 24.0f);
    assert(double_al_get(&dal, 0) == 42.0f);

    /* will resizes to a capacity of 4 */
    double_al_add(&dal, 88.0f);
    assert(double_al_len(&dal) == 3);
    assert(double_al_get(&dal, 2) == 88.0f);

    /* set the value at index 1 to 77 */
    double_al_set(&dal, 1, 77.0f);
    assert(double_al_get(&dal, 1) == 77.0f);

    /* remove index 1 */
    assert(double_al_remove(&dal, 1) == 77.0f);

    assert(double_al_len(&dal) == 2);

    /* shrink the capacity to 2 */
    double_al_shrink(&dal);

    /* cleanup */
    double_al_free(&dal);
}
```
