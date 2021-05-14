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
\#include <stdio.h>

\#include "al.h"

ARRAYLIST(dal, double); // define a struct named dal

ARRAYLIST\_PROTYPE(dal, double); // defines the functions for dal

int main(int argc, const char \*\*argv) {
    struct dal *cal = dal\_new(2); // create an AL with a capacity of 2 elements

    dal\_add(cal, 1);
    dal\_add(cal, 2);
    dal\_add(cal, 3); // doubles the size of the array
    dal\_remove(cal, 1); // shifts the elements after index to the left
                         // effectively erasing the element at index

    dal\_free(cal); // cleanup

    return 0;
}
    ```
