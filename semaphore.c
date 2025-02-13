#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2
#define NUM_ITEMS 10

// Shared buffer and related variables
int buffer[BUFFER_SIZE];
int in = 0;  // index for adding items
int out = 0; // index for removing items

// Semaphores
sem_t empty; // counts empty buffer slots
sem_t full;  // counts full buffer slots
sem_t mutex; // for mutual exclusion

// Function to produce an item
void produce_item(int producer_id, int item)
{
    printf("Producer %d produced item: %d\n", producer_id, item);
}

// Function to consume an item
void consume_item(int consumer_id, int item)
{
    printf("Consumer %d consumed item: %d\n", consumer_id, item);
}

// Producer thread function
void *producer(void *arg)
{
    int producer_id = *((int *)arg);

    for (int i = 0; i < NUM_ITEMS; i++)
    {
        int item = rand() % 100; // Generate random item

        // Wait for empty slot
        sem_wait(&empty);
        // Wait for mutex
        sem_wait(&mutex);

        // Critical section
        produce_item(producer_id, item);
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;

        // Release mutex
        sem_post(&mutex);
        // Signal full slot
        sem_post(&full);

        // Sleep for random time
        usleep(rand() % 500000);
    }

    return NULL;
}

// Consumer thread function
void *consumer(void *arg)
{
    int consumer_id = *((int *)arg);

    for (int i = 0; i < NUM_ITEMS; i++)
    {
        // Wait for full slot
        sem_wait(&full);
        // Wait for mutex
        sem_wait(&mutex);

        // Critical section
        int item = buffer[out];
        consume_item(consumer_id, item);
        out = (out + 1) % BUFFER_SIZE;

        // Release mutex
        sem_post(&mutex);
        // Signal empty slot
        sem_post(&empty);

        // Sleep for random time
        usleep(rand() % 500000);
    }

    return NULL;
}

int main()
{
    // Initialize random seed
    srand(time(NULL));

    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    // Create producer and consumer threads
    pthread_t producers[NUM_PRODUCERS];
    pthread_t consumers[NUM_CONSUMERS];
    int producer_ids[NUM_PRODUCERS];
    int consumer_ids[NUM_CONSUMERS];

    // Create producer threads
    for (int i = 0; i < NUM_PRODUCERS; i++)
    {
        producer_ids[i] = i + 1;
        pthread_create(&producers[i], NULL, producer, &producer_ids[i]);
    }

    // Create consumer threads
    for (int i = 0; i < NUM_CONSUMERS; i++)
    {
        consumer_ids[i] = i + 1;
        pthread_create(&consumers[i], NULL, consumer, &consumer_ids[i]);
    }

    // Wait for producer threads to finish
    for (int i = 0; i < NUM_PRODUCERS; i++)
    {
        pthread_join(producers[i], NULL);
    }

    // Wait for consumer threads to finish
    for (int i = 0; i < NUM_CONSUMERS; i++)
    {
        pthread_join(consumers[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}