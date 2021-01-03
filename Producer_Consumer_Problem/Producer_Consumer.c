/* * This program creates producers and consumers to insert and consume items that are made with a random number
 * generator. It has 4 functions which are to create producers, create consumers, insert items into a buffer, and
 * remover items from a buffer. The buffer is initialized as a circular array with all -1 integers to begin with. The
 * main program sleeps for a given amount of time of the first argument in seconds while the threads pass around
 * semaphores to do the work after sleeping for a random time themselves.*/

#include <semaphore.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

// This is the buffer "Object" being created
typedef int buffer_item;
buffer_item item_buffer[5];

// Declaring all global variables and initializing some of them
int consumer_array[1000];
int producer_array[1000];
int buffer_counter;
int global_remove_counter;
int global_consumer_array_size;
int global_producer_array_size;

// Declaring the variables with respect to the threads and semaphores
sem_t semaphore_full;
sem_t semaphore_empty;
pthread_t thread_ID;
pthread_attr_t attributes;
pthread_mutex_t mutex_lock;

// Declaring the Functions so they can come after main or be used in it.
void *Create_Producer(void *param);
void *Create_Consumer(void *param);
void sleep(int);
int Insert_Next_Item(buffer_item item);
int Remove_Previous_Item(buffer_item *item);


int main(int number_of_arguments, char *argv[]) {
    // Declaring variables
    int n;
    int k;
    int sleep_timer_of_main;
    int number_of_producers;
    int number_of_consumers;

    // Initializing the buffer to be all -1 integers as per the assignment specifications.
    for(k = 0; k < 5; k++){
        item_buffer[k] = -1;
    }

    // Checking the arguments and making sure there were exactly 4
    if(number_of_arguments != 4) {
        fprintf(stderr, "\nPlease use only 3 arguments:  ./A5 <Sleep time> <# of producers> <# of consumers>\n\n");
        exit(0);
    }

    // Checking that the sleep time is a number
    if(atoi(argv[1])){
        int arg1 = atoi(argv[1]);
        sleep_timer_of_main = arg1;
    }
    else{
        fprintf(stderr, "Your first argument is not a number.\n");
    }

    // Checking that the producers are a number
    if(atoi(argv[2])){
        int arg2 = atoi(argv[2]);
        number_of_producers = arg2;
    }
    else{
        fprintf(stderr, "Your second argument is not a number.\n");
    }

    // Checking that the consumers are a number
    if(atoi(argv[3])){
        int arg3 = atoi(argv[3]);
        number_of_consumers = arg3;
    }
    else{
        fprintf(stderr, "Your third argument is not a number.\n");
    }

    // Initializing thread and semaphore variables
    pthread_attr_init(&attributes);
    pthread_mutex_init(&mutex_lock, NULL);
    sem_init(&semaphore_empty, 0, 5);
    sem_init(&semaphore_full, 0, 0);

    // Initialize more variables that couldn't be initialized before.
    int producer_array_size = (number_of_producers + number_of_producers + 1);
    int consumer_array_size = (number_of_consumers + number_of_consumers + 1);
    global_producer_array_size = producer_array_size;
    global_consumer_array_size = consumer_array_size;
    buffer_counter = 0;

    /* This creates producers threads and also initializes an array that helps track the identifier of the producer in
    more human readable terms rather than a large integers (ie: 0,1,2,3 not 98324793487,293842904,9238472394,54535345)*/
    n = 0;
    while(n < number_of_producers){
        /* Create the thread */
        pthread_create(&thread_ID, &attributes, Create_Producer, NULL);
        if(n == 0){
            producer_array[n] = thread_ID;
            producer_array[n + 1] = 0;
        }
        else{
            producer_array[n + n] = thread_ID;
            producer_array[n + n + 1] = n;
        }
        n++;
    }

    /* This creates consumer threads and also initializes an array that helps track the identifier of the consumer in
    more human readable terms rather than a large integers (ie: 0,1,2,3 not 98324793487,293842904,9238472394,54535345)*/
    n = 0;
    while(n < number_of_consumers){
        pthread_create(&thread_ID, &attributes, Create_Consumer, NULL);
        if(n == 0){
            consumer_array[n] = thread_ID;
            consumer_array[n + 1] = 0;
        }
        else{
            consumer_array[n + n] = thread_ID;
            consumer_array[n + n + 1] = n;
        }
        n++;
    }

    // Sleep then Exit the program
    sleep(sleep_timer_of_main);
    exit(0);
}


/* This function takes in a item of type buffer_item and then adds it to the buffer assuming the buffer isn't full if it
 * is full, then return -1 as an error to be caught in the producer function that calls this one*/
int Insert_Next_Item(buffer_item item) {
    buffer_counter = buffer_counter % 5;
    int trigger = buffer_counter < 5;
    switch(trigger){
        case 0:
            return -1;
        case 1:
            item_buffer[buffer_counter] = item;
            buffer_counter++;
            return 0;
    }
}


/* This function takes in a pointer of an item of type buffer_item and then removes it from the buffer assuming the
 * buffer has items. If it does, it will put the index into the global variable for printing, return the item to the
 * consumer function, and fill that buffer slot with a -1 as per the assignment specifications. */
int Remove_Previous_Item(buffer_item *item) {
    int j = 0;
    while(j < 5){
        if (item_buffer[j] != -1){
            *item = item_buffer[j];
            item_buffer[j] = -1;
            global_remove_counter = j;
            return 0;
        }
        j++;
    }
}


/* This function sleeps for a random number of seconds between 0 and 4, then acquires locks, generates random numbers to
 * represent the item to be created, then populates an array with a number of itself for human readability, finally it
 * inserts the item by calling an insert function and releases the locks*/
void *Create_Producer(void *param) {
    buffer_item item;

    while(1 == 1) {
        int sleep_timer = rand() % 4;
        sleep(sleep_timer);

        item = rand();
        sem_wait(&semaphore_empty);
        pthread_mutex_lock(&mutex_lock);

        int producer_number_check = pthread_self();
        int producer_number = -1;
        int q = 0;

        while(q < global_producer_array_size){
            if (producer_number_check == producer_array[q]){
                producer_number = producer_array[q+1];
            }
            q++;
        }

        int trigger = Insert_Next_Item(item);
        switch(trigger){
            case 0:
                printf("Producer %d inserted item %d into buffer[%d]\n", producer_number, item, buffer_counter - 1);
        }

        pthread_mutex_unlock(&mutex_lock);
        sem_post(&semaphore_full);
    }
}


/* This function sleeps for a random number of seconds between 0 and 4, then acquires locks, then populates an array
 * with a number of itself for human readability, finally it removes the item by calling an insert function and releases
 * the locks*/
void *Create_Consumer(void *param) {
    buffer_item item;

    while(1 == 1) {
        int sleep_timer = rand() % 4;
        sleep(sleep_timer);

        sem_wait(&semaphore_full);
        pthread_mutex_lock(&mutex_lock);

        int consumer_number_check = pthread_self();
        int consumer_number = -1;
        int q = 0;

        while(q < global_consumer_array_size){
            if (consumer_number_check == consumer_array[q]){
                consumer_number = consumer_array[q+1];
            }
            q++;
        }

        int trigger = Remove_Previous_Item(&item);
        switch (trigger){
            case 0:
                printf("Consumer %d consumed item %d from buffer[%d]\n", consumer_number, item, global_remove_counter);
        }

        pthread_mutex_unlock(&mutex_lock);
        sem_post(&semaphore_empty);
    }
}
