#include <stdio.h>
#include <pthread.h>

pthread_key_t key;
pthread_once_t init_done = PTHREAD_ONCE_INIT;



/* destructor */
void echomsg(void* t)
{
	printf("destructor excuted in thread %u, param=%u\n", pthread_self(), (unsigned int)t);
}

void initFunc(void)
{
	int rc = 0;

	rc = pthread_key_create(&key, echomsg);
	if(rc) printf("%s: caller:%u key fail\n", __func__, pthread_self());
	else printf("%s: caller:%u key:%u OK\n", __func__, pthread_self(), key);
}

void *func1(void *arg)
{
	int val = (int)arg;
	int tmp = 0;

	printf("%s: tid=%u got:%d\n", __func__, pthread_self(), val);	

	pthread_once(&init_done, initFunc);
	pthread_setspecific(key, (void*)pthread_self());

	do{

		printf("%s: tid:%u get %u\n", __func__, pthread_self(), pthread_getspecific(key));
		sleep(1);
		val--;

	}while(val > 0);
	
	return NULL;
}

void *func2(void *arg)
{
	int val = (int)arg;
	int tmp = 0;

	printf("%s: tid=%u got:%d\n", __func__, pthread_self(), val);
	pthread_once(&init_done, initFunc);

	pthread_setspecific(key, (void*)pthread_self());
	do{
		printf("%s: tid=%u get:%u\n", __func__, pthread_self(), pthread_getspecific(key));
		sleep(1);
		val--;

	}while(val > 0);



	return NULL;
}



int main(void)
{
	int count = 10;
	pthread_t tid1 = 0;
	pthread_t tid2 = 0;

	printf("%s: main tid=%u\n", __func__, pthread_self());

	pthread_once(&init_done, initFunc);
	pthread_create(&tid1, NULL, func1, (void*)count);
	pthread_create(&tid2, NULL, func2, (void*)count);

	pthread_setspecific(key, (void*)pthread_self());

	do{
		sleep(1);
		count--;
		printf("%s: tid:%u key get:%u\n", __func__, pthread_self(), pthread_getspecific(key));
	}
	while(count > 0);

	pthread_key_delete(key);
	printf("%s: exit\n", __func__);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	return 0;

}




