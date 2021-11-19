#include"bbuff.h"
#include<semaphore.h>
#include <stdio.h>
#include<stdbool.h>
#include<pthread.h>
#include<unistd.h>
#include <stdlib.h>

int in=0;
int out=0;
int count=0;
sem_t full;
sem_t empty;
sem_t mutex;
void* buff[BUFFER_SIZE];



void bbuff_init(void)
{
     sem_init(&empty,0,BUFFER_SIZE);
     sem_init(&full,0,0);
     sem_init(&mutex,0,1);

}
void bbuff_blocking_insert(void* item)
{
	sem_wait(&empty);
    sem_wait(&mutex);
    
buff[in]=&item;
in=(in+1)%BUFFER_SIZE;
count++;
    sem_post(&mutex);
    sem_post(&full);

}
void* bbuff_blocking_extract(void)
{
	sem_wait(&full);
    sem_wait(&mutex);
    void* candy=buff[out];
    out=(out+1)%BUFFER_SIZE;
    count--;
    sem_post(&mutex);
    sem_post(&empty);
    return candy;

}
_Bool bbuff_is_empty(void)
{
	if (count == 0)
		return true;
	else
	return false;
}

	//int num, value;
	//=sem_getvalue(empty);
	//if(num==0)
	//{
	//	return true;
	//}
	//else
		//return false;

