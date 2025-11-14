#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>     // sleep
#include <stdint.h>     // intptr_t

static void* thread_handler(void* arg) {
    int my_id = (int)(intptr_t)arg;      // id do main truyền vào (1 hoặc 2)
    pthread_t tid = pthread_self();

    printf("Thread_%d with TID=%lu is running!\n", my_id, (unsigned long)tid);

    // giả sử làm việc gì đó...
    sleep(1);

    // trả về mã thoát tương ứng (1 hoặc 2)
    pthread_exit((void*)(intptr_t)my_id);
    // hoặc: return (void*)(intptr_t)my_id;
}

int main(void) {
    pthread_t tid_1, tid_2;
    void *retval_1 = NULL, *retval_2 = NULL;

    int rc;

    rc = pthread_create(&tid_1, NULL, thread_handler, (void*)(intptr_t)1);
    if (rc != 0) { perror("pthread_create tid_1"); exit(1); }

    sleep(3); 

    rc = pthread_create(&tid_2, NULL, thread_handler, (void*)(intptr_t)2);
    if (rc != 0) { perror("pthread_create tid_2"); exit(1); }

    rc = pthread_join(tid_1, &retval_1);
    if (rc != 0) { perror("pthread_join tid_1"); exit(1); }

    sleep(1); 
    rc = pthread_join(tid_2, &retval_2);
    if (rc != 0) { perror("pthread_join tid_2"); exit(1); }

    printf("Main: thread_1 exited with code %ld\n", (long)(intptr_t)retval_1);
    printf("Main: thread_2 exited with code %ld\n", (long)(intptr_t)retval_2);

    return 0;
}
