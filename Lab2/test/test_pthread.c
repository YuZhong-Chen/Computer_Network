#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define COUNT_MAX 10

pthread_mutex_t lock;

int CurrentCount = 0;
bool isLoss(double P);
void* count();

int main() {
    CurrentCount = 0;
    pthread_mutex_init(&lock, NULL);
    pthread_t Thread_1, Thread_2;

    pthread_create(&Thread_1, NULL, count, NULL);
    pthread_create(&Thread_2, NULL, count, NULL);

    pthread_join(Thread_1, NULL);
    pthread_join(Thread_2, NULL);

    pthread_mutex_destroy(&lock);

    printf("End : %d\n", CurrentCount);
    return 0;
}

bool isLoss(double P) {
    if (P >= 1.0)  // All packets are loss.
        return true;
    else
        return (rand() <= (P * RAND_MAX));
}

void* count() {
    while (true) {
        pthread_mutex_lock(&lock);

        int temp = CurrentCount++;
        if (CurrentCount > COUNT_MAX) {
            pthread_mutex_unlock(&lock);
            break;
        }

        pthread_mutex_unlock(&lock);

        while (!isLoss(0.5)) {
            sleep(1);
        }

        printf("%d\n", temp);
    }

    pthread_exit(NULL);
    return NULL;
}