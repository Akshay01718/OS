

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

// Define buffer size
#define BUFFER_SIZE 5

// Shared memory structure
typedef struct {
    int buffer[BUFFER_SIZE];
    int in;
    int out;
    sem_t full;
    sem_t empty;
    sem_t mutex;
} SharedMemory;

void producer(SharedMemory *shm) {
    int item;
    while (1) {
        sleep(1); // Simulate production delay
        item = rand() % 100; // Produce an item

        sem_wait(&shm->empty);  // Wait for an empty slot
        sem_wait(&shm->mutex); // Lock access to the buffer

        // Produce item
        shm->buffer[shm->in] = item;
        printf("Producer produced: %d\n", item);
        shm->in = (shm->in + 1) % BUFFER_SIZE;

        sem_post(&shm->mutex); // Unlock access to the buffer
        sem_post(&shm->full);  // Signal that buffer has a full slot
    }
}

void consumer(SharedMemory *shm) {
    int item;
    while (1) {
        sleep(2); // Simulate consumption delay

        sem_wait(&shm->full);  // Wait for a full slot
        sem_wait(&shm->mutex); // Lock access to the buffer

        // Consume item
        item = shm->buffer[shm->out];
        printf("Consumer consumed: %d\n", item);
        shm->out = (shm->out + 1) % BUFFER_SIZE;

        sem_post(&shm->mutex); // Unlock access to the buffer
        sem_post(&shm->empty); // Signal that buffer has an empty slot
    }
}

int main() {
    // Generate unique key
    key_t key = ftok("shmfile", 65);

    // Allocate shared memory
    int shmid = shmget(key, sizeof(SharedMemory), 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // Attach shared memory
    SharedMemory *shm = (SharedMemory *)shmat(shmid, NULL, 0);
    if (shm == (void *)-1) {
        perror("shmat");
        exit(1);
    }

    // Initialize shared memory variables
    shm->in = 0;
    shm->out = 0;
    sem_init(&shm->full, 1, 0);            // Semaphore for full slots
    sem_init(&shm->empty, 1, BUFFER_SIZE); // Semaphore for empty slots
    sem_init(&shm->mutex, 1, 1);           // Semaphore for mutual exclusion

    // Create producer and consumer threads
    pid_t pid = fork();
    if (pid == 0) {
        // Child process: Consumer
        consumer(shm);
    } else if (pid > 0) {
        // Parent process: Producer
        producer(shm);
    } else {
        perror("fork");
        exit(1);
    }

    // Detach shared memory
    shmdt(shm);

    // Cleanup shared memory (only the parent process should do this)
    if (pid > 0) {
        wait(NULL);
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}
