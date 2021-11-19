#include "klock.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>

int count=0;
//int resourcearr[500];
//int threadarr[500];
int resourcearrcount=0;
int threadcount=0;
Node* resource_list[1500];
Node* thread_list[1500];
sem_t mut;



    bool detector(Node* begin)
    {
          Node* iterator=begin;
          while(iterator->link != NULL)
          {
          	iterator=iterator->link;
          	if(iterator->processid==begin->processid && iterator->type == begin->type)
          		return true;
          }
          return false;
    }



void init_lock(SmartLock* lock) {
	
	Node* resource=malloc(sizeof(Node));
	resource->resourceid=count;
	lock->id=count;
	pthread_mutex_init(&(lock->mutex), NULL);
	

	resource->type=0;
	resource->processid=0;
	resource->link=NULL;
	//resourcearr[resourcearrcount]=resource->resourceid;
	resource_list[resourcearrcount]=resource;
	resourcearrcount=resourcearrcount+1;
	count=count+1;
    
}

int lock(SmartLock* lock) {
	sem_init(&mut,0,1);
	
  long id=pthread_self();
  bool create=true;
 int trackthread;
  
  for(int i=0;i<threadcount;i++)
  {   
  	
  	 if(thread_list[i]->processid==id)
  	{
  		trackthread=i;
  		create=false;
  		break;
  	}
 }
 	
  if(create==true){
    Node* thread=malloc(sizeof(Node));
	thread->resourceid=0;
	thread->type=1;
	thread->processid=id;
	thread->link=NULL;
	sem_wait(&mut);
	//threadarr[threadcount]=id;
	thread_list[threadcount]=thread;

	trackthread=threadcount;
    threadcount=threadcount+1;

    sem_post(&mut);
	}
    
  // Node* newresource2;
    int track;
	for(int l=0;l<resourcearrcount;l++)
	{
		if(lock->id == resource_list[l]->resourceid)
		{
             track=l;  
             break;  
		}
	}

	thread_list[trackthread]->link=resource_list[track];

	bool result= detector(thread_list[trackthread]);

	if(result==true)
	{
		thread_list[trackthread]->link=NULL;
		return 0;
	}

	else
	{  
		    pthread_mutex_lock(&(lock->mutex));
			printf("%lu locking\n",pthread_self());
			resource_list[track]->link=thread_list[trackthread];
			thread_list[trackthread]->link=NULL;
			return 1;
	}



	
}

void unlock(SmartLock* lock) {
	int tracker = 0;

	for(int i=0;i<=resourcearrcount;i++)
	{
		if(resource_list[i]->resourceid==lock->id)
			tracker=i;
		break;
	}
	resource_list[tracker]->link=NULL;
	pthread_mutex_unlock(&(lock->mutex));
}

/*
 * Cleanup any dynamic allocated memory for SmartLock to avoid memory leak
 * You can assume that cleanup will always be the last function call
 * in main function of the test cases.
 */
void cleanup() {

	for(int i=0;i<threadcount;i++)
	
		free(thread_list[i]);
	

	for(int j=0;j<resourcearrcount;j++)
		free(resource_list[j]);

}
























