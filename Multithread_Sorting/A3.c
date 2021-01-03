/*
 * This program takes in a text file with up to 500 integers, creates 2 threads, sends half of the original list to
 * each, sorts them in halves within each of the threads, and then sends it to a final thread to have the halves
 * merged into a final sorted array.
 *
 */

#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <stdio.h>

void *sorter(void *parameter_input);    /* thread that performs basic sorting algorithm */
void *merger(void *parameter_input);    /* thread that performs merging of results */

int list[500];
int number_of_elements;
int sorted_list[500];

typedef struct{
    int starting_index;
    int ending_index;
} parameters;

int main (int argc, const char * argv[]){

    // Opening the file IntegerList.txt
    char *token_for_strtok;
    char temp_array[500];
    FILE *integer_list_txt;
    integer_list_txt = fopen("IntegerList.txt", "r");

    // Scanning and placing the contents of IntegerList.txt into a temporary array delimited by commas
    fscanf(integer_list_txt, "%s", temp_array);
    token_for_strtok = strtok(temp_array, ",");
    int q=0;

    // Iterating through the rest of the IntegerList.txt file and force converting strings to integers using Atoi
    while(token_for_strtok != NULL) {
        list[q] = atoi(token_for_strtok);
        token_for_strtok = strtok(NULL, ",");
        q++;
    }

    // This is to track the actual number of elements in the file (up to a maximum of 100 according to the assignment)
    number_of_elements = q;

    // Creating the threads
    pthread_t thread[3];

    /* create the first sorting thread */
    parameters *list_of_numbers = (parameters *) malloc (sizeof(parameters));
    (*list_of_numbers).starting_index = 0;
    (*list_of_numbers).ending_index = number_of_elements / 2;
    pthread_create(&thread[0], 0, sorter, list_of_numbers);

    /* create the second sorting thread */
    list_of_numbers = (parameters *) malloc (sizeof(parameters));
    (*list_of_numbers).starting_index = (number_of_elements / 2 + 1);
    (*list_of_numbers).ending_index = number_of_elements;
    pthread_create(&thread[1], 0, sorter, list_of_numbers);

    // "now wait for the 2 sorting threads to finish"
    int a;
    for (a = 0; a < 3 - 1; a++){
        pthread_join(thread[a], NULL);
    }

    // Freeing memory
    free(list_of_numbers);

    // create the merge thread
    list_of_numbers = (parameters *) malloc(sizeof(parameters));
    (*list_of_numbers).starting_index = 0;
    (*list_of_numbers).ending_index = (499);
    pthread_create(&thread[2], 0, merger, list_of_numbers);

    // "wait for the merge thread to finish"
    pthread_join(thread[2], NULL);

    // Freeing memory
    free(list_of_numbers);


    // "output the sorted array"
    printf("\nThe Output of IntegerList.txt in sorted order is: \n");
    int print=0;

    while(print<500){
        if(sorted_list[print] != 0){
            printf("%d\n", sorted_list[print]);
        }
        print++;
    }
    printf("\n");

    return 0;
}

/* Bubble Sort
 *
 * Since I am not worried about efficiency in this program (due to there being only a maxiumum of 500 input size), I
 * decided to go with a basic brute force algorithm. It iterates through each element, compares it to the next one, then
 * it swaps places with the next item in the list until it is sorted. I could have used a recursive call to do divide
 * and conquer or some other sorting algorithm like mergesort, etc. if I wanted nlog(n) time but this was simpler
 *
 */
void *sorter(void *parameter_input){

    parameters* input = (parameters *)parameter_input;

    //SORT
    int starting_index = (*input).starting_index;
    int ending_index = (*input).ending_index + 1;
    int e= starting_index;
    int f = starting_index;
    int temp_var;

    while(e < ending_index){
        while(f < ending_index - e - 1){
            int next = f + 1;
            if(list[f] > list[next]){
                temp_var = list[f];
                list[f] = list[next];
                list[next] = temp_var;
            }
            f++;
        }
        e++;
    }

    int b;
    for(b=starting_index; b < ending_index; b++){
        sorted_list[b]=list[b] ;
    }
    pthread_exit(0);
}

/* Brute force merging
 *
 * I decided again since the maximum input is 500, to simply use a very basic but inefficient merging algorithm.
 *
 */
void *merger(void *parameter_input){

    parameters* input = (parameters *)parameter_input;
    int starting_index = (*input).starting_index;
    int ending_index = (*input).ending_index + 1;
    int c= starting_index;
    int d = starting_index;
    int temp_var;

    // Doing the actual merging using Brute force
    while(c < ending_index){
        for(d; d < ending_index - c; d++){
            int next = d + 1;
            if(sorted_list[d] > sorted_list[next]){
                temp_var = sorted_list[d];
                sorted_list[d] = sorted_list[next];
                sorted_list[next] = temp_var;
            }
        }

        c++;
    }
    pthread_exit(0);
}
