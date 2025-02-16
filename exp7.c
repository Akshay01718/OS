#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define LEFT(philo_num) (philo_num + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS
#define RIGHT(philo_num) (philo_num + 1) % NUM_PHILOSOPHERS

sem_t mutex;
sem_t chopsticks[NUM_PHILOSOPHERS];
// Semaphore to signal when all philosophers have finished eating
sem_t all_done;
// Counter to track the number of philosophers finished eating
int philosophers_finished = 0;

void *philosopher(void *arg)
{
    int philo_num = *((int *)arg);

    while (1)
    {
        printf("Philosopher %d is Thinking\n", philo_num + 1);
        sleep(2);

        sem_wait(&mutex);
        printf("Philosopher %d is Hungry\n", philo_num + 1);
        sem_wait(&chopsticks[philo_num]);
        sem_wait(&chopsticks[RIGHT(philo_num)]);
        sem_post(&mutex);

        printf("Philosopher %d is Eating\n", philo_num + 1);
        sleep(2);

        // Putting down chopsticks
        sem_post(&chopsticks[philo_num]);
        sem_post(&chopsticks[RIGHT(philo_num)]);

        sem_wait(&mutex);
        philosophers_finished++;
        if (philosophers_finished == NUM_PHILOSOPHERS)
        {
            sem_post(&all_done); // Signal all philosophers have finished eating
        }
        sem_post(&mutex);

        printf("Philosopher %d has Finished Eating\n", philo_num + 1);

        // Exit condition to prevent infinite loop (for simulation purposes)
        break;
    }

    return NULL;
}

int main()
{
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philo_ids[NUM_PHILOSOPHERS];

    sem_init(&mutex, 0, 1);
    // Initialize the semaphore for signaling all philosophers finished eating
    sem_init(&all_done, 0, 0);

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        sem_init(&chopsticks[i], 0, 1);
    }
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        philo_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philo_ids[i]);
    }

    // Wait until all philosophers have finished eating
    sem_wait(&all_done);

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        // Stop the philosopher threads
        pthread_join(philosophers[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&all_done);

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        sem_destroy(&chopsticks[i]);
    }

    return 0;
}
