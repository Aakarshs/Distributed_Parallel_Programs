/* 

Pseduocode

pt_cond_wait(cond_var,ml);
pt_cond_signal(cond_var);

DEQUEUE:
lock(ml);
if q(isEmpty()) {
pt_cond_wait(c_v1,ml);
}
remove ();
unlock(ml);
pt_cond_signal(c_v2);

ENQUEUE:
lock(ml);
if q(isFull()) {
pt_cond_wait(c_v2,ml);
}
add(key);
unlock(ml);
pt_cond_signal(c_v1);

when the q is full and the producers are still...
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define SIZE 100

pthread_mutex_t ml;
pthread_cond_t cv_1;
pthread_cond_t cv_2;
pthread_t t1; 
pthread_t t2; 
pthread_t t3;

int Queue[SIZE];
int front = -1;
int rear = -1;

void Add(int element)                          //Adds to the circular queue.
{
  pthread_mutex_lock (&ml);                    //locking the mutex.
    if((front == rear+1) || (front == 0 && rear == SIZE-1)){
      printf("\n Queue is full!! \n");        // if there is a mismatch: wait(if the q is full).
      pthread_cond_wait(&cv_2,&ml);           //waiting if the queue is full.
    } else
    {
      if(rear==SIZE-1 && front!=0)
        rear=-1;
        rear=(rear+1)%SIZE;
        Queue[rear]=element;

        printf("\n Inserted element: %d", element);
        if(front == -1) 
        front = 0;
               
    }
    pthread_mutex_unlock(&ml);               //unlocking the mutex.
    pthread_cond_signal(&cv_1);              //sending the signal.
}

int Remove()                                 //Removes the first element from the circular queue and returns it.
{
    int element;
    pthread_mutex_lock (&ml);                //locking the mutex.
    
    if(front == -1 && rear == -1) {
        printf("\n Queue is empty !! \n");  // if there is a mismatch: wait(if the q is empty).
        pthread_cond_wait(&cv_1, &ml);      //waiting if the queue is empty.
        
    }
    else {
        element=Queue[front];
        if (front==rear){
            front=rear=-1;
        } 
        else {
            front=(front+1)%SIZE; 
        }
        printf("\n Deleted element: %d", element);
        pthread_mutex_unlock(&ml);         //unlocking the mutex.
        pthread_cond_signal(&cv_2);        //sending the signal.
        return(element);
    }
    return 0;
}

int Peek()
{
    if(front == -1) {
      printf(" \n Empty Queue\n"); 
      return(-1);
    }
    else
    {
         printf("\n Element at front: %d ",front);
         return (front);
    }
}


void* p1(void* arg) {
    int i;
    for (i=0;i<5;i++) {
        Add(i);
    }
    pthread_exit(0);
}
 
void* p2(void* arg) {
    int i;
    for (i=0;i<5;i++) {
        Add(i);
    }
    pthread_exit(0);
}
 
void* p3(void* arg) {
    int i=0;
    while(i<5) {
        Remove();
        i++;
    }
    pthread_exit(0);
}
 

int main() { 

    void *r1, *r2, *r3;
    
    pthread_create(&t1, NULL, p1, &r1);     //creating thread.
    pthread_create(&t2, NULL, p2, &r2);     //creating thread.
    pthread_create(&t3, NULL, p3, &r3);     //creating thread.

    pthread_join(t1, &r1);                 //joining thread.
    pthread_join(t2, &r2);                 //joining thread.
    pthread_join(t3, &r3);                 //joining thread.
    pthread_mutex_destroy(&ml);
    return 0; 
}

