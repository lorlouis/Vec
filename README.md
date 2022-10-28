# vec.h A generic vector using the C preprocessor

## includes

* \_len(\*vec)
* \_init(initial\_capacity)
* \_cleanup(\*vec)
* \_get(\*vec, index)
* \_push(\*vec, data)
* \_pop(\*vec, index, \*buf)
* \_remove(\*vec, index, \*buf)
* \_shrink(\*vec)

## How to use

```c
#include <assert.h>

#include "vec.h"

VEC(vecd, double);

VEC_FUNCTIONS(vecd, double);

int main(int argc, const char **argv) {
    struct vecd vecd;
    /* initialise the list with an initial capacity of 2
     * 0 because doubles do not have a special free method*/
    vecd_init(&vecd, 2, 0);
    /* add elements to the list */
    vecd_push(&vecd, 42.0f);
    vecd_push(&vecd, 24.0f);
    /* get the number of elements in the list */
    assert(vecd_len(&vecd) == 2);
    /* or */
    assert(vecd.len == 2);

    /* access the elements in the list */
    assert(*vecd_get(&vecd, 1) == 24.0f);
    assert(*vecd_get(&vecd, 0) == 42.0f);

    /* will resizes to a capacity of 4 */
    vecd_push(&vecd, 88.0f);
    assert(vecd_len(&vecd) == 3);
    assert(*vecd_get(&vecd, 2) == 88.0f);

    /* set the value at index 1 to 77 */
    vecd.data[1] = 77.0f;
    assert(*vecd_get(&vecd, 1) == 77.0f);

    /* remove index 1 */
    double buf = 0;
    vecd_remove(&vecd, 1, &buf);
    assert(buf == 77.0f);

    assert(vecd_len(&vecd) == 2);

    /* shrink the capacity to 2 */
    vecd_shrink(&vecd);

    /* cleanup */
    vecd_cleanup(&vecd);
}
```
