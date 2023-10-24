#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int thread_count;

void *Thread_sum *(void *rank)
{
    long my_rank = (long)rank;
    double factor;
    long long i;
    long long my_n = n / thread_count;
    long long my_first_i = my_n * my_rank;
    long long my_last_i = my_first_i + my_n;

    if (my_first_i % 2 == 0)
        factor = 1.0;
    else
        factor = -1;

    for (i = my_first_i; i < my_last_i; i++, factor = -factor)
    {
        sum += factor(2 * i + 1);
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    long thread;
    pthread_t *thread_handles;
    int i;

    for (i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
            A[i][j] = 1 + i;
    }

    thread_count = 3;
    printf("Quantia de threads: %d", thread_count);
    thread_handles = malloc(thread_count * sizeof(pthread_t));

    for (thread = 0; thread < thread_count; thread++)
        pthread_create(&thread_handles[thread], NULL, Thread_sum, (void *)thread);
    for (thread = 0; thread < thread_count; thread++)
    {
        pthread_join(thread_handles[thread], NULL);
    }

    free(thread_handles);
    printf("\n");
    for (i = 0; i < N; i++)
    {
        printf("%d\n", y[i]);
    }
    return 0;
}