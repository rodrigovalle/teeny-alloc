#ifndef __DEBUG_H
#define __DEBUG_H

#include <stdio.h>
#include <inttypes.h>
#include <stdint.h>
#include "../teenyalloc.h"


void print_freelist(mempool_T pool)
{
    int i = 0;
    for (char *ptr = pool; !__LIST_EMPTY(ptr); ptr = __FOLLOW_LIST(ptr)) {
        printf("0x%016lx\n", (unsigned long)ptr);
        i++;
    }
    printf("%d structs available\n\n", i);
}


int count_freelist(mempool_T pool)
{
    int i = 0;
    for (char *ptr = pool; !__LIST_EMPTY(ptr); ptr = __FOLLOW_LIST(ptr)) {
        i++;
    }
    return i;
}


#endif /* __DEBUG_H */
