#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define BATCH_SIZE 10

int data[BATCH_SIZE];   // chứa 10 giá trị
int data_ready = 0;     // 0 = chưa sẵn sàng, 1 = đã đủ 10 giá trị

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond  = PTHREAD_COND_INITIALIZER;

// PRODUCER
void* producer(void* arg) {
    for (int batch = 0; batch < 3; batch++) {   // ví dụ tạo 3 batch
        pthread_mutex_lock(&mutex);

        while (data_ready == 1) {
            pthread_cond_wait(&cond, &mutex);   // chờ consumer lấy xong batch trước
        }

        printf("\n[Producer] Generating batch %d ...\n", batch + 1);

        for (int i = 0; i < BATCH_SIZE; i++) {
            data[i] = rand() % 100;
            printf("  Produced: %d\n", data[i]);
            usleep(50 * 1000);   // dễ nhìn
        }

        data_ready = 1;                  // báo đã đủ 10 phần tử
        pthread_cond_signal(&cond);      // báo consumer
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

// CONSUMER
void* consumer(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);

        while (data_ready == 0) {
            pthread_cond_wait(&cond, &mutex);
        }

        printf("\n[Consumer] Received batch:\n");
        for (int i = 0; i < BATCH_SIZE; i++) {
            printf("  Consumed: %d\n", data[i]);
        }

        data_ready = 0;                // cho phép producer tạo batch mới
        pthread_cond_signal(&cond);    // đánh thức producer
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

int main() {
    pthread_t prod_tid, cons_tid;

    srand(time(NULL));

    pthread_create(&prod_tid, NULL, producer, NULL);
    pthread_create(&cons_tid, NULL, consumer, NULL);

    pthread_join(prod_tid, NULL);

    // Consumer chạy vô hạn → detach nó để không block main
    pthread_cancel(cons_tid);
    pthread_detach(cons_tid);

    return 0;
}
