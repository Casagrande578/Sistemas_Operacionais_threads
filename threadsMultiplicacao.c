#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define M 6
#define N 6
#define T 3
int thread_count;
int A[M][N];
int x[T];
int y[T];

void *Pth_mat_vect(void *rank){
	long my_rank = (long) rank;
	int i,j;
	int local_m = M/thread_count;
	int my_first_row = my_rank*local_m;
	int my_last_row = (my_rank +1) *local_m -1;
	
	for(i = my_first_row; i<=my_last_row;i++){
		y[i] = 0.0;
		for(j=0; j<N; j++)
		y[i] += A[i][j]*x[j];
	}
	return NULL;
}

int main(int argc, char* argv[]){
	long thread;
	pthread_t* thread_handles;
	int i;
	x[0] = 1;
	x[1] = 2;
	x[2] = 3;
	for(i = 0; i<M; i++){
		for(int j=0; j<N; j++)
			A[i][j] = 1+i;
	}

	thread_count = 3;
	thread_handles = malloc(thread_count*sizeof(pthread_t));
	
	for(thread = 0; thread<thread_count; thread++)
		pthread_create(&thread_handles[thread],NULL,Pth_mat_vect, (void *) thread);
	for (thread = 0; thread<thread_count; thread++){
		pthread_join(thread_handles[thread],NULL);
	}

	free(thread_handles);
	printf("\n");
	for(i = 0; i<N; i++){
		printf("%d\n",y[i]);
	}
	return 0;
}
