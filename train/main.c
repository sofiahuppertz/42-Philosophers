#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

pthread_mutex_t mutex;


void *thread(void *arg) {
    int *value = (int *)arg;
    
    pthread_mutex_lock(&mutex);
    printf("Thread %d\n", *value);
    pthread_mutex_unlock(&mutex);
    free(value);
    return NULL;
}

int main(void)
{
    pthread_t th[10];
    pthread_attr_t detached_thread;
    int *value;
    int i;

    pthread_attr_init(&detached_thread);
    pthread_attr_setdetachstate(&detached_thread, PTHREAD_CREATE_DETACHED);
    pthread_mutex_init(&mutex, NULL);
    for (i = 0; i < 10; i++){
        value = calloc(sizeof(int), 1);
        *value = i;
        if (pthread_create(&th[i], &detached_thread, &thread, (void *)value)) {
            perror("Failed to create thread");
            exit (EXIT_FAILURE);
        }
    }
    pthread_mutex_destroy(&mutex);
    pthread_attr_destroy(&detached_thread);
    pthread_exit(0);
    return (0);
}

/*
int primes[20] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
                  31, 37, 41, 43, 47, 53, 59, 61, 67, 71};

void *thread(void *arg) {
    int *prime = (int *)arg;

    printf("%d\n", *prime);
    free(prime);
    return NULL;

}

int main(int argc, char *argv[]) {
    pthread_t th[20];

    for (int i = 0; i < 20; i++){
        int *a = calloc(sizeof(int), 1);
        *a = primes[i];
        if (pthread_create(&th[i], NULL, &thread, (void *)a)){
            perror("pthread_create");
            return (EXIT_FAILURE);
        }
        printf("Thread %d created\n", i);
    }
    for (int i = 0; i < 20; i++){
        if (pthread_join(th[i], NULL)){
            perror("pthread_join");
            return (EXIT_FAILURE);
        }
        printf("Thread %d joined\n", i);
    }

    return (EXIT_SUCCESS); 
}*/




















/*
pthread_mutex_t mutex;

void *roll_dice(){
    int value;
    int *result;
    int lock_status;

    result = calloc(sizeof(int), 1);
    if (!result) {
        perror("malloc");
        return (NULL);
    }
    lock_status = pthread_mutex_lock(&mutex);
    if (lock_status != 0) {
        perror("pthread_mutex_lock");
        free(result);
        return (NULL);
    }
    value = (rand() % 6) + 1;
    *result = value;
    lock_status = pthread_mutex_unlock(&mutex);
    if (lock_status != 0) {
        free(result);
        perror("pthread_mutex_unlock");
        return (NULL);
    }
    printf("Dice value inside thread: %d\n", value);
    return (void *)result;
}

int main(int argc, char *argv[]) {
    pthread_t th[4];
    int *value;

    srand(time(NULL));
    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < 4; i++) {
        if (pthread_create(&th[i], NULL, &roll_dice, NULL)){
            perror("pthread_create");
            return (EXIT_FAILURE);
        }
    }
    for (int i = 0; i < 4; i++){
        if (pthread_join(th[i], (void **)&value)){
            perror("pthread_join");
            return (EXIT_FAILURE);
        }
        printf("Dice value: %d\n", *value);
        free(value);
    }
    pthread_mutex_destroy(&mutex);
    return (EXIT_SUCCESS);
}
*/













/*
int mails = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *thread(void *arg) {
    int i;
    while (i < 1000000) {
        pthread_mutex_lock(&mutex);
        mails += 1;
        pthread_mutex_unlock(&mutex);
        i += 1;
    }

    return NULL;
}


int main() {
    pthread_t th[9];
    pthread_mutex_init(&mutex, NULL);
    
    for (int i = 0; i < 4; i++){
        if (pthread_create(&th[i], NULL, &thread, NULL)){
            perror("pthread_create");
            return (EXIT_FAILURE);
        }
        printf("Thread %d created\n", i);
    }
    for (int i = 0; i < 4; i++){
        if (pthread_join(th[i], NULL)){
            perror("pthread_join");
            return (EXIT_FAILURE);
        }
        printf("Thread %d joined\n", i);
    }
    printf("Mails: %d\n", mails);
    return (EXIT_SUCCESS);
}
*/

