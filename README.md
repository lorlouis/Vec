# al.h A generic arraylist using the C preprocessor

## includes

* \_new(initial\_capacity)
* \_add(\*arraylist, data)
* \_get(\*arraylist, index)
* \_set(\*arraylist, index, data)
* \_remove(\*arraylist, index)
* \_free(\*arraylist)

## How to use

```c
#include "al.h"

ARRAYLIST(dal, double); // define a struct named dal

ARRAYLIST_PROTYPE(dal, double); // defines the functions for dal

int main(int argc, const char \*\*argv) {
    struct dal *cal = dal_new(2); // create an AL with a capacity of 2 elements

    dal_add(cal, 1);
    dal_add(cal, 2);
    dal_add(cal, 3); // doubles the size of the array
    dal_remove(cal, 1); // shifts the elements after index to the left
                        // effectively erasing the element at index

    dal_free(cal); // cleanup

    return 0;
}
```
