/*
 * This program takes in a user sentence, splits it up based on spaces, writes it to Stdout (the screen)
 * and then writes it to a file called "Output.txt"
 */

#include<stdio.h>
#include<string.h>

/*
 * @Pointer to a Char Array
 * return 0
 *
 * This function receives an array pointer and then splits it up based on spaces as the delimiter and printing it
 *
 */
int Split(char *input){

    // Creating a copy of the input and spliting it because strtok() is destructive and the input will be used again
    char input_copy[10000];
    strcpy(input_copy, input);
    char *token = strtok(input_copy, " ");

    // Printing to the screen through strtok() tokens using the copy to preserve the original user input
    while(token != NULL){
        printf("'%s'\n", token);
        token = strtok(NULL, " ");
    }

    return 0;
}

/*
 * @Pointer to a Char Array
 * return 0
 *
 * This function receives an array pointer and then writes it to a file called "Output.txt" with a space delimiter
 *
 */
int Write(char *input){

    // Creating a copy of the input and spliting it because strtok() is destructive and the input will be used again
    char input_copy[10000];
    strcpy(input_copy, input);
    char *token = strtok(input_copy, " ");

    //Creating and opening the input to a file called "Output.txt"
    FILE *output_file;
    output_file = fopen("Output.txt", "w");

    // Writing to "Output.txt" through strtok() tokens using the copy to preserve the original user input
    while(token != NULL){
        fprintf(output_file, "'%s'\n", token);
        token = strtok(NULL, " ");
    }

    // Making sure to close the files that were open and returning
    fclose(output_file);
    return 0;
}

int main(){

    // Creating an array to store user input
    char sentence[10000];

    // Receiving user input and storing it in the array "sentence"
    printf("Please Enter Your Sentence: ");
    scanf("%[^\n]s", &sentence);

    // Calling the split and write functions to take care of the rest of the processes needed
    Split(sentence);
    Write(sentence);
}
