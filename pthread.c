#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#define SIZE 1024

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

struct data{
	short stats;
	char data[SIZE];
} data;

void * thread_start(void * arg)
{
	while (1)
	{
		usleep(10);
		pthread_mutex_lock(&mutex);
		printf ("input a char :\n");
		fgets(data.data, SIZE, stdin);
		data.stats=1;
		pthread_mutex_unlock(&mutex);
		pthread_cond_signal(&cond);
	}
	return 0;
}

void *func2(void * arg)
{
	while (1)
	{
		pthread_mutex_lock(&mutex);
		if ( 0 ==  data. stats)
		{
			printf ("wait  data\n");
			pthread_cond_wait(&cond, &mutex);
		}
		else {
			printf("func2 :%s\n", data.data);
			data.stats = 0;
		}
		pthread_mutex_unlock(&mutex);
	}
	return 0;
}

struct pinfo {
	pthread_t thread_id;        /* ID returned by pthread_create() */
	int       num;
	char      *arg;
};

int main()
{
	struct pinfo  p_id[2];
	int ret ;

	data.stats = 0;
	p_id[0].num = 1;
	p_id[1].num = 2;

	ret = pthread_create(&p_id[0].thread_id, NULL, thread_start, &p_id[0]);
	if ( ret < 0 ) 
	{
		perror ("create pthread err:");
		return 0;
	}
	usleep(100);
	ret = pthread_create(&p_id[1].thread_id, NULL, func2, &p_id[1]);
	if ( ret < 0 ) 
	{
		perror ("create pthread err:");
		return 0;
	}
	pthread_join(p_id[0].thread_id, NULL);
	pthread_join(p_id[1].thread_id, NULL);

	return 0;
}

