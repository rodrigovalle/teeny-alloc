#include "../teenyalloc.h"
#include "../teenyalloc_test.h"
#include <stdio.h>
#include <assert.h>

struct data {
    double my_number;
    double more_stuff;
    double my_other_number;
    double this_is_my_data;
    char make_things_weird;
};

int main()
{
    struct data data[10];
    struct data *data_ptrs[10];
    struct data other_data[10];
    struct data *other_data_ptrs[10];

    struct data single;

    mempool_T my_pool = mempool_init(data, sizeof(struct data), 10);
    assert(count_freelist(my_pool) == 10);
    print_freelist(my_pool);

    mempool_T other_pool = mempool_init(other_data, sizeof(struct data), 10);
    assert(count_freelist(other_pool) == 10);
    print_freelist(other_pool);

    mempool_T single_pool = mempool_init(&single, sizeof(struct data), 1);
    print_freelist(single_pool);
    assert(count_freelist(single_pool) == 1);
    struct data *i = mempool_alloc(&single_pool);
    assert(count_freelist(single_pool) == 0);
    assert(mempool_alloc(&single_pool) == NULL);
    mempool_free(&single_pool, i);

    for (int i = 0; i < 5; i++) {
        data_ptrs[i] = mempool_alloc(&my_pool);
        data_ptrs[i]->make_things_weird = 0;
    }
    print_freelist(my_pool);
    
    for (int i = 0; i < 5; i++) {
        other_data_ptrs[i] = mempool_alloc(&other_pool);
    }
    print_freelist(other_pool);

    for (int i = 5; i < 10; i++) {
        data_ptrs[i] = mempool_alloc(&my_pool);
    }
    print_freelist(my_pool);

    for (int i = 5; i < 10; i++) {
        other_data_ptrs[i] = mempool_alloc(&other_pool);
    }
    print_freelist(other_pool);

    assert(count_freelist(my_pool) == 0);
    assert(count_freelist(other_pool) == 0);
    assert(mempool_alloc(&my_pool) == NULL);
    assert(mempool_alloc(&other_pool) == NULL);

    for (int i = 0; i < 5; i++) {
        mempool_free(&my_pool, data_ptrs[i]);
    }
    print_freelist(my_pool);
    
    for (int i = 0; i < 5; i++) {
        mempool_free(&other_pool, other_data_ptrs[i]);
    }
    print_freelist(other_pool);

    for (int i = 5; i < 10; i++) {
        mempool_free(&my_pool, data_ptrs[i]);
    }
    print_freelist(my_pool);
    
    for (int i = 5; i < 10; i++) {
        mempool_free(&other_pool, other_data_ptrs[i]);
    }
    print_freelist(other_pool);
}
