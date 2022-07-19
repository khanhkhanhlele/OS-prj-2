#include <semaphore.h>
#include <sys/types.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int readCounter = 0;
sem_t semReader, semWriter;

void *read1(void *val)
{
    while (1)
    {

        sem_wait(&semReader);
        readCounter++;
        if (readCounter == 1)
        {

            sem_wait(&semWriter);
        }
        sem_post(&semReader);
        printf("reader\n");
        sem_wait(&semReader);
        readCounter--;
        if (readCounter == 0)
        {

            sem_post(&semWriter);
        }
        sem_post(&semReader);
        sleep(1);
    }
}
void *write1(void *val)
{
    while (1)
    {
        sem_wait(&semWriter);
        printf("writer\n");
        sem_post(&semWriter);
        sleep(1);
    }
}

int main()
{
    void *status;
    pthread_t reader1, reader2, writer;
    sem_init(&semReader, 0, 1);
    sem_init(&semWriter, 0, 1);
    pthread_create(&reader1, NULL, read1, NULL);
    pthread_create(&reader2, NULL, read1, NULL);
    pthread_create(&writer, NULL, write1, NULL);
    
    pthread_join(reader1, &status);
    pthread_join(reader2, &status);
    pthread_join(writer, &status);
    sem_destroy(&semReader);
    sem_destroy(&semWriter);
    return 0;
}

//commands

//1)gcc rw.c -pthread -o rw
//2)./rw
