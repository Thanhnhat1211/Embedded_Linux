#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>     // sleep
#include <stdint.h>     // intptr_t

#define Number_Increments 1000000

long long counter = 0;

pthread_mutex_t counter_mutex =  PTHREAD_MUTEX_INITIALIZER;

static void* thread_handler1(void* arg){
    for(int i = 0; i < Number_Increments; i++){
        pthread_mutex_lock(&counter_mutex);
        counter++;
        pthread_mutex_unlock(&counter_mutex);
    }
    return NULL;
}

static void* thread_handler2(void* arg){
    for(int i = 0; i < Number_Increments; i++){
        pthread_mutex_lock(&counter_mutex);
        counter++;
        pthread_mutex_unlock(&counter_mutex);
    }
    return NULL;
}

static void* thread_handler3(void* arg){
    for(int i = 0; i < Number_Increments; i++){
        pthread_mutex_lock(&counter_mutex);
        counter++;
        pthread_mutex_unlock(&counter_mutex);
    }
    return NULL;
}

int main(){
    pthread_t tid1, tid2, tid3;
    int rc;

    rc = pthread_create(&tid1, NULL, thread_handler1, NULL);
    if(rc != 0) { perror("pthread_create tid_1"); exit(1); };

    rc = pthread_create(&tid2, NULL, thread_handler2, NULL);
    if(rc != 0) { perror("pthread_create tid_1"); exit(1); };

    rc = pthread_create(&tid3, NULL, thread_handler3, NULL);
    if(rc != 0) { perror("pthread_create tid_1"); exit(1); };

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);

    printf("Final counter value: %lld\n", counter);
    printf("Expected value     : %d\n", 3 * Number_Increments);

    pthread_mutex_destroy(&counter_mutex);
    return 0;
}