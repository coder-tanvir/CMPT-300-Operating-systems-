#ifndef __KLOCK_H__
#define __KLOCK_H__

#include <pthread.h>

typedef struct Node{
	long processid;
	int resourceid;
	int type;   // 0 for resource and 1 for locks
	struct Node* link;
}Node;



typedef struct {
	 pthread_mutex_t mutex;
	 int id;
	 struct Node* link;
} SmartLock;



void init_lock(SmartLock* lock);
int lock(SmartLock* lock);
void unlock(SmartLock* lock);
void cleanup();

#endif
