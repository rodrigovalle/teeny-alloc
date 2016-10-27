#include "../teenyalloc.h"
#include <stdio.h>
#include <sys/time.h>

#define TRIALS 100000

struct data {
    int my_int;
    double my_double;
    void *my_pointer;
    char my_char;
};

double print_diff(const struct timeval *tv1, struct timeval *tv2, const char *alloc_type)
{
    double diff = (double) (tv2->tv_usec - tv1->tv_usec) / 1000000 + 
                  (double) (tv2->tv_sec - tv1->tv_sec);
    printf("%d %s allocations took %fs, an average of %.11f per allocation\n",
            TRIALS, alloc_type, diff, diff/TRIALS);
    return diff;
}

int main()
{
    void * volatile p;
    //struct data empty_obj[TRIALS];
    void *empty_obj = malloc(TRIALS * sizeof(struct data));
    mempool_T obj_pool = mempool_init(empty_obj, sizeof(struct data), TRIALS);

    struct timeval start, end;
    gettimeofday(&start, NULL);
    for (int i = 0; i < TRIALS; i++) {
        p = mempool_alloc(&obj_pool);
    }
    gettimeofday(&end, NULL);
    double mempool_perf = print_diff(&start, &end, "mempool");
    free(empty_obj);

    gettimeofday(&start, NULL);
    for (int i = 0; i < TRIALS; i++) {
        p = malloc(sizeof(struct data));
    }
    gettimeofday(&end, NULL);
    double malloc_perf = print_diff(&start, &end, "malloc ");
    printf("speedup: %f\n", malloc_perf/mempool_perf);
}
