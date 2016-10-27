A memory-friendly implementation of a generic fixed-size freelist. Useful when
allocating and freeing several chunks of memory of the same size and don't want
to incur the cost of malloc for each allocation.


Usage
=====
Just drop the header into your project directory and `#include "teenyalloc.h"`.

Declare an array of structs either on the stack or using `malloc`, and pass the
array to `mempool_init` along with the size of a struct and the number of
structs in the array:

NOTE: be sure that the struct is at least the size of a pointer (4 bytes on 
32-bit architectures and 8 bytes on 64-bit, generally).

``` C
struct data empty_objects[10];
// OR
void *empty_objects = malloc(10 * sizeof(struct data));

// then initialize
mempool_T object_pool = mempool_init(empty_objects, sizeof(struct data), 10);

// and allocate all you want (returns NULL when out of memory)
struct data *obj = mempool_alloc(&object_pool);
if (!obj) {
    perror("out of memory");
}

// free unused objects
mempool_free(&object_pool, obj);

// free the mempool if necessary
free(empty_objects);
```


Implementation
==============
`mempool_init`  intializes a linked list inside the array of structs, returns
                mempool_T, which is actually just a pointer to the start of the
                list. [O(n)]

`mempool_alloc` pops a struct off the top of the freelist [O(1)]

`mempool_free`  pushes a struct to the top of the freelist [O(1)]


Performance
===========
Make sure struct arrays are aligned to the size of a pointer, since a freelist
pointer is created at each empty struct's starting address. I'll try to address
this issue later.


Issues
======
teeny-alloc has a lot of the same issues as regular malloc, 
  - double free the same pointer
  - free a pointer not allocated with mempool_allocate()

Also make sure to keep these issues in mind:
  - don't mix mempools (or do, they're just linked lists)
  - not thread safe (yet)
  - mempools can run out of memory (could malloc more memory when none left)
  - can't use structs whose size is less than that of a pointer (since we embed
    pointers into each struct to form the free list)


Learn more 
==========
[Boost pool](http://www.boost.org/doc/libs/1_61_0/libs/pool/doc/html/boost_pool/pool/pooling.html)
