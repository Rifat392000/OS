#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

int num_users;
int num_tickets;

pthread_mutex_t mutex;
sem_t semaphore;

void *book_show(void *arg)
{
    int thread_id = (int) arg;

    pthread_mutex_lock(&mutex);
    if (num_tickets > 0)
    {
        printf("User %d:  ticket booked...\n",(thread_id+1));
        num_tickets--;
    }
    else
    {
        printf("User %d: not ticket booked...\n",(thread_id+1));
    }
    pthread_mutex_unlock(&mutex);
    sem_post(&semaphore);

    pthread_exit(NULL);  // Terminate thread
}

int main()
{
    int value=0;
    
     printf("\nWelcome to Ticket Booking System\n\n");
    do
    {
       
        printf("Input for Number of Users : ");
        scanf("%d",&num_users);
        printf("Input for Number of Tickets : ");
        scanf("%d",&num_tickets);

        // Initialize mutex and semaphore
        pthread_mutex_init(&mutex, NULL);
        sem_init(&semaphore, 0, 0);

        // Create user threads
        pthread_t threads[num_users];
        for (int i = 0; i < num_users; i++)
        {
            pthread_create(&threads[i], NULL, book_show, (void *)i);
        }

        // Wait for user threads to finish booking shows
        for (int i = 0; i < num_users; i++)
        {
            sem_wait(&semaphore);
        }

        // Clean up and exit
        pthread_mutex_destroy(&mutex);
        sem_destroy(&semaphore);
        printf("\n------------------------------------------------------------\n");
        printf("Do you want to exit the System ?\n 1.Yes\n 2.No\nEnter the value : ");
        scanf("%d",&value);
        printf("\n------------------------------------------------------------\n\n");

    }
    while(value!=1);
    printf("!!!Thank You!!!\n");
    return 0;
}
