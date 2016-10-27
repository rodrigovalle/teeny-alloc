#include "../teenyalloc.h"
#include "teenyalloc_test.h"
#include <stdio.h>
#include <assert.h>

struct data {
    char make_things_weird;
    char whatever;
    char ok;
    char cool;

    char thing;
    char other;
    char thingy;
    char there_have_to_be;

    char at_least_eight;
};

int main()
{
    struct data data[10];
    //struct data *data = malloc(10 * sizeof(struct data));
    struct data *data_ptrs[10];
    printf("sizeof(struct data): %lu\n\n", sizeof(struct data));

    mempool_T my_pool = mempool_init(data, sizeof(struct data), 10);
    print_freelist(my_pool);

    for (int i = 0; i < 10; i++) {
        data_ptrs[i] = mempool_alloc(&my_pool);
    }
    print_freelist(my_pool);
    
    for (int i = 0; i < 10; i++) {
        mempool_free(&my_pool, data_ptrs[i]);
    }
    print_freelist(my_pool);
}
