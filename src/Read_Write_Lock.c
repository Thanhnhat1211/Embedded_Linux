#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

int shared_data = 0;

pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;

void* reader_thread(void *arg){
    int id = (intptr_t)arg;
    
    for(int i = 0; i < 5; i++){
        pthread_rwlock_rdlock(&rwlock);
        printf("[Reader %d] Đọc giá trị: %d\n", id, shared_data);
        pthread_rwlock_unlock(&rwlock);
        usleep(100*1000);
    }
    pthread_exit(NULL);
}

void* writer_thread(void* arg){
    int id = (intptr_t)arg;
    for(int i = 0; i < 5; i++){
        pthread_rwlock_wrlock(&rwlock);
        shared_data++;
        printf(">>> [Writer %d] GHI, tăng shared_data lên: %d\n", id, shared_data);
       pthread_rwlock_unlock(&rwlock);
       usleep(150*1000);
    }
    pthread_exit(NULL);
}

int main(void){
    pthread_t readers[5];
    pthread_t writers[2];
    // Tạo reader threads
    for (int i = 0; i < 5; i++) {
        if (pthread_create(&readers[i], NULL, reader_thread, (void*)(intptr_t)(i+1)) != 0) {
            perror("pthread_create reader");
            exit(1);
        }
    }

    // Tạo writer threads
    for (int i = 0; i < 2; i++) {
        if (pthread_create(&writers[i], NULL, writer_thread, (void*)(intptr_t)(i+1)) != 0) {
            perror("pthread_create writer");
            exit(1);
        }
    }

    // Join tất cả các thread
    for (int i = 0; i < 5; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < 2; i++) {
        pthread_join(writers[i], NULL);
    }

    pthread_rwlock_destroy(&rwlock);

    printf("Kết thúc chương trình, shared_data cuối cùng = %d\n", shared_data);
    return 0;
}
