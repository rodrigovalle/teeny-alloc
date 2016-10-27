#ifndef __TEENYALLOC_H
#define __TEENYALLOC_H

#include <stdlib.h>

#define __FOLLOW_LIST(ptr)       (*(char **)(ptr))
#define __ELEMENT(arr, size, n)  ((char *)arr + (size)*(n))
#define __LIST_EMPTY(ptr)        (!ptr)

typedef char* mempool_T;


/**
 * mempool_init - initialize a memory pool
 * @arr: an array of empty structs
 * @size: the size of an individual struct
 * @nmemb: the number of structs in the array (where nmemb > 0)
 * @return: mempool handle
 *
 * Embeds a linked list inside of the array, meaning each struct must be at
 * least big enough to hold a pointer. Undefined behavior results when this
 * condition is not met.
 */
static inline mempool_T mempool_init(void *arr, size_t size, size_t nmemb)
{
    char *start = __ELEMENT(arr, size, 1);
    char *last = __ELEMENT(arr, size, nmemb);
    char **iter = arr;

    for (char *ptr = start; ptr != last; ptr += size) {
        *iter = ptr; // dereference to store a pointer value into the array
        iter = (char **)ptr; // update to point to the next array slot
    }
    *iter = NULL;

    return arr; // return the list head
}


/**
 * mempool_alloc - allocate a struct
 * @pool: &mempool_T returned by mempool_init
 * @return: a pointer to a single free struct, NULL if memory ran out
 *
 * Pops a struct off of the free list, and updates the mempool_T handle to
 * point to the next node in the free list.
 */
static inline void *mempool_alloc(mempool_T *pool)
{
    if (__LIST_EMPTY(*pool))
        return NULL;

    void *mem = *pool;
    *pool = __FOLLOW_LIST(*pool);
    return mem;
}


/**
 * mempool_free - free a struct
 * @pool: &mempool_T returned by mempool_init
 * @req: pointer to a struct
 *
 * Pushes the newly freed struct onto the freelist.
 */
static inline void mempool_free(mempool_T *pool, void *req)
{
    char **freed = req;
    *freed = *pool; // make the node point at the list head
    *pool = req;    // make the list head
}

#endif   /* __TEENYALLOC_H */
