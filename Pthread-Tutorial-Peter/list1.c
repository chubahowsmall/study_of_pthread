#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/*
 * The worker thread. It takes a "void *arg" argument and 
 * return a "NULL"
 */
void *thread_func(void *arg)
{
	int i = 0;
	int exit_status = 100;

	printf("%s: In worker thread \n", __func__);
	printf("%s: Got %d\n", __func__, *(int *)arg);

	do{
		i += 1;
		sleep(1);		
		printf("%s: %d\n", __func__, i);
	}while(i < 10);

	printf("%s: going to exit\n", __func__);
	pthread_exit(&exit_status);
}

int main(void)
{
	pthread_t thread_ID;
	void *exit_status;
	int value;


	/* Create a worker thread */
	printf("%s: Creating worker thread\n", __func__);
	value = 42;
	pthread_create(&thread_ID, NULL, thread_func, &value);

	printf("%s: joining worker thread\n", __func__);
	/* Join the worker thread */
	pthread_join(thread_ID, &exit_status);
	

	printf("%s: going to exit\n", __func__);

	pthread_exit(NULL);
	return 0;
}




