#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


void *thread_func(void *arg)
{
	int count = 0;
	int val = (int) arg;
	int retval = 0;

	printf("%s %d created\n", __func__, val);
	

	do{
		printf("%s: thread %d\n", __func__, val);
		count += 1;
		sleep(1);

	}while(count < 10);

//	return val;
	pthread_exit((void *)val);
}


int main(void)
{
	pthread_t threads[10];
	int *exit_status;
	int param;
	int count;

	count = 0;
	do{
		pthread_create(&threads[count], NULL, thread_func, (void *)count);
		count += 1;

	}while(count < 10);
#if 0
	pthread_join(threads[0], &exit_status);printf("%s: thread %d exit\n", __func__, *exit_status);
	pthread_join(threads[1], &exit_status);printf("%s: thread %d exit\n", __func__, *exit_status);
	pthread_join(threads[2], &exit_status);printf("%s: thread %d exit\n", __func__, *exit_status);
	pthread_join(threads[3], &exit_status);printf("%s: thread %d exit\n", __func__, *exit_status);
	pthread_join(threads[4], &exit_status);printf("%s: thread %d exit\n", __func__, *exit_status);
	pthread_join(threads[5], &exit_status);printf("%s: thread %d exit\n", __func__, *exit_status);
	pthread_join(threads[6], &exit_status);printf("%s: thread %d exit\n", __func__, *exit_status);
	pthread_join(threads[7], &exit_status);printf("%s: thread %d exit\n", __func__, *exit_status);
	pthread_join(threads[8], &exit_status);printf("%s: thread %d exit\n", __func__, *exit_status);
	pthread_join(threads[9], &exit_status);printf("%s: thread %d exit\n", __func__, *exit_status);
#else
	pthread_join(threads[0], &exit_status);printf("%s: thread %d exit\n", __func__, exit_status);
	pthread_join(threads[1], &exit_status);printf("%s: thread %d exit\n", __func__, exit_status);
	pthread_join(threads[2], &exit_status);printf("%s: thread %d exit\n", __func__, exit_status);
	pthread_join(threads[3], &exit_status);printf("%s: thread %d exit\n", __func__, exit_status);
	pthread_join(threads[4], &exit_status);printf("%s: thread %d exit\n", __func__, exit_status);
	pthread_join(threads[5], &exit_status);printf("%s: thread %d exit\n", __func__, exit_status);
	pthread_join(threads[6], &exit_status);printf("%s: thread %d exit\n", __func__, exit_status);
	pthread_join(threads[7], &exit_status);printf("%s: thread %d exit\n", __func__, exit_status);
	pthread_join(threads[8], &exit_status);printf("%s: thread %d exit\n", __func__, exit_status);
	pthread_join(threads[9], &exit_status);printf("%s: thread %d exit\n", __func__, exit_status);

#endif

	printf("%s: all threads terminated\n", __func__);


	return 0;
}
