#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t lock;
static int sharedData;


void *thread_func(void *arg)
{
	unsigned int count;
	count = 0;

	do{

		pthread_mutex_lock(&lock);
		printf("%s got lock\n", __func__);
		pthread_mutex_unlock(&lock);
		//usleep(15000);
		count += 1;
	}while(count < 0xffffffff);

	pthread_exit((void *)0);
}

int main(void)
{
	pthread_t pid;
	int *exit_status;

	unsigned int count = 0;	

	/* Initialize a mutex */
	pthread_mutex_init(&lock, NULL);

	/* create a thread */
	pthread_create(&pid, NULL, thread_func, NULL);

	do{
		pthread_mutex_lock(&lock);
		printf("%s got lock\n", __func__);
		pthread_mutex_unlock(&lock);
		//sleep(1);
		count += 1;
	}while(count < 0xffffffff);


	pthread_join(pid, &exit_status);

	pthread_mutex_destroy(&lock);


	return 0;
}
