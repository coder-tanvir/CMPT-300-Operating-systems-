#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<unistd.h>
#include<semaphore.h>
//#include<stats.h>
#include<stdbool.h>
#include"bbuff.h"



typedef struct{
	int factory_number;
	double time_stamp_in_ms;
}candy_t;

double current_time_in_ms(void)
{
    struct timespec now;
    clock_gettime(CLOCK_REALTIME, &now);
    return now.tv_sec * 1000.0 + now.tv_nsec/1000000.0;
}


bool stop=false;

void* produce(void* arg)
{
	int num=*((int*) arg);
	while(!stop){
		srand(time(NULL));
		int newnum=rand()%4;
		printf("\t The Factory %d ships the candy and waits %ds\n",num,newnum);
		 candy_t *c = malloc(sizeof(candy_t));
    c->factory_number = num;
    c->time_stamp_in_ms = current_time_in_ms();
    bbuff_blocking_insert(c);
    sleep(newnum);
	}
	printf("Candy Factory %d which is done",num);
pthread_exit(NULL);
}

void* consume(void* a)
{
	srand(time(NULL));
	while(true)
	{
		candy_t *candy=bbuff_blocking_extract();
		//candy_t *candy=(candy_t*)candyptr;
		printf("this candy got produced by: %d\n in time: %f\n",candy->factory_number,candy->time_stamp_in_ms);
		
		int newnum=rand()%2;
		sleep(newnum);
	}
}






int main(int argc, char* argv[]){

int arg1=atoi(argv[1]); 
int arg2=atoi(argv[2]);
int arg3=atoi(argv[3]);

int idarr[arg1];
for(int j=0;j<arg1;j++)
{
	idarr[j]=j;
}

if((arg1<=0)||(arg2<=0)||(arg3<=0))
{
	printf("Error : invalid argument\n");
	exit(0);
}
	
bbuff_init();

//pthread_t * factory = malloc(sizeof(pthread_t)*arg1);
pthread_t factory[arg1];
for (int i = 0; i < arg1; i++) {

   int value = pthread_create(&factory[i], NULL, produce, &idarr[i]);

    // if(value == 0) {
    //     printf (" pthread created!\n");
    // }

        

        if(value == -1)
        {
        	printf("Error:pthread is not created\n");
        	exit (1);
        }
    }




//pthread_t * kids = malloc(sizeof(pthread_t)*arg2);
pthread_t kids[arg2];
for(int i=0;i< arg2;i++)
{
	int secvalue=pthread_create(&kids[i], NULL, consume, NULL);

   // if(secvalue==0)
    //{
    //	printf("Thread created\n");
    //}

    if(secvalue == -1)
        {
        	printf("Error:pthread is not created\n");
        	exit (1);
        }
}



for(int k=1;k<=arg3;k++)
{
    sleep(1);
    printf("Time\t%ds:\n",k-1);
}

stop=true;
int count=0;
while(count<arg1)
{
	 pthread_join(factory[count], NULL);	
	 ++count;
}

//bool result;
//result=bbuff_is_empty();
while(!bbuff_is_empty())
{
	printf("waiting for the kids to consume all the candies\n");
	sleep(1);
}
count=0;
while(count<arg2)
{
	pthread_cancel(kids[count]);
	pthread_join(kids[count],NULL);
	++count;
}



	return 0;

}



//Mega jhamela
//Tera problems
//laura hai ye duniya 
//dying is much easier
//