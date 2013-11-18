#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t lock;
pthread_cond_t	is_zero;
static int shared_data = 32767;



void *func1(void *arg)
{

	while(shared_data != 0)
	{	
		printf("%s: waitinf for is_zero\n", __func__);
		pthread_cond_wait(&is_zero, &lock);
	}

	printf("%s: got is_zero\n", __func__);
	printf("%s exits\n", __func__);
	
	pthread_exit(NULL);
}

void *func2(void *arg)
{

	while(shared_data > 0)
	{
		pthread_mutex_lock(&lock);
		shared_data -= 1;
		pthread_mutex_unlock(&lock);
		printf("%s: shared_data = %d\n", __func__, shared_data);
	}

	printf("%s: shared_data is zero, broadcast to every waiting threads\n", __func__);
	pthread_cond_broadcast(&is_zero);

	pthread_exit(NULL);
}


int main(void)
{
	pthread_t pid1, pid2;
	void *exit_status;
	int i;

	pthread_mutex_init(&lock, NULL);
	pthread_cond_init(&is_zero, NULL);

	pthread_create(&pid1, NULL, func1, NULL);
	pthread_create(&pid2, NULL, func2, NULL);

	printf("%s: waiting for shared data to zero \n", __func__);
	/* wait for the shared data to zero */
	pthread_mutex_lock(&lock);
	while(shared_data != 0)
	{
		pthread_cond_wait(&is_zero, &lock);
	}
	pthread_mutex_unlock(&lock);


	printf("%s: shared data comes to zero\n", __func__);

	pthread_join(pid1, NULL);
	pthread_join(pid2, NULL);

	pthread_mutex_destroy(&lock);
	pthread_cond_destroy(&is_zero);

	return 0;
}


