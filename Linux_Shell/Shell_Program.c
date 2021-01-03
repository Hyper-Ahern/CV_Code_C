/*
 * This program serves as a shell for Linux that accepts commands, executes them using a separate process, stores the
 * last 10 commands, and allows the user to see their history or choose form a previously used command.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#define MAX_LINE 80 /* The maximum length command */
static char * history[10];
static int history_counter = 0;

/*
 * This function is meant to create the history functionality ensuring that there are never more than 10 previous
 * commands and keeping track of the number of elements there are in the history array.
 */
static void create_history(char * command){

  /* If the number of previous commands is equal to 9 then it is time to move the elements in the array to
     accommodate the new incoming command. In this way, the newest commands always have space. */
  if(history_counter == (9)){
    int y = 1;

    /*move the elements in the history array to be able to add a new one once the total reaches 9
      we start at 1 because that is easier for the index but you could do y = 0 and history[y] */
    while(y < history_counter){
      history[y-1] = history[y];
      y++;
    }

    // If this is not here or is inside the loop, the first command will be executed with "!!" not the last
    history_counter--;
  }

  // Add the user input to the array in the correct order (history_counter), then increment it to keep track.
  history[history_counter] = strdup(command);
  history_counter++;
}

/*
 * This function is meant to print out the users history up to the last 10 commands. It is a very simple print statement
 */
static void print_history(){
  pid_t pid;
  printf("ID   PID  Command  \n");

  // You have to go backwards on this loop because the newest command is always on top.
  int h = history_counter - 1;
  while(h>= 0){
    printf("%d    %d    %s\n", h+1, pid, history[h]);
    h--;
  }
}

int main(void){

  // Declaring variables
  int i = 0;
  char* args[MAX_LINE/2 + 1]; /* an array of character strings */
  int should_run = 1; /* flag to determine when to exit program */
  char array_temp[MAX_LINE]; /* Temporary Array to gather user input then parse to the args array */
  char array_temp2[MAX_LINE]; /* Temporary Array to copy user input then parse to the array_history array */
  int k;
  char* array_history[MAX_LINE]; /* Array that holds the 10 last commands */
  int execvp_status;
  int wait_status;
  int done;
  char *command;
  int want_history;
  int want_exclamation;;
  int want_specific_exclamation_1;
  int want_specific_exclamation_2;
  int want_specific_exclamation_3;
  int want_specific_exclamation_4;
  int want_specific_exclamation_5;
  int want_specific_exclamation_6;
  int want_specific_exclamation_7;
  int want_specific_exclamation_8;
  int want_specific_exclamation_9;
  int want_specific_exclamation_10;
  pid_t pid;

  // While the variable "should_run' is 1, continue looping for user input and other tasks.
  while(should_run == 1){

    // This is mostly from the templates given in class to take in user input
    printf("CSCI3120> ");
    fflush(stdout);
    scanf ("%[^\n]%*c", array_temp);
    i = 0;

    // Because strtok() is destructive, I made a copy of the user input to use for the History task
    strncpy(array_temp2, array_temp, MAX_LINE);

    // Populating the args array with user input through strtok()
    args[i] = strtok(array_temp," ");

    while (args[i] != NULL) {
      i++;
      args[i] = strtok(NULL, " ");
    }

    // Populating the array_history with user input through strtok() (the copy)
    array_history[k] = strtok(array_temp2," ");

    while (array_history[k] != NULL) {
      k++;
      array_history[k] = strtok(NULL, " ");
    }

    //allocating memory to the variable that will be passed to different functions (contains the string user input)
    command = (char*) malloc(MAX_LINE);

    // Creating the command variable by concatenating all the user input into one line.
    int u = 0;
    while(args[u] != NULL){
      strcat(command,args[u]);
      strcat(command, " ");
      u++;
    }

    // Declaring and intializaing variables for the main part of the code.
    done = strcmp(args[0], "exit");
    want_history = strcmp(args[0], "history");
    want_exclamation = strcmp(args[0], "!!");
    want_specific_exclamation_1 = strcmp(args[0], "!1");
    want_specific_exclamation_2 = strcmp(args[0], "!2");
    want_specific_exclamation_3 = strcmp(args[0], "!3");
    want_specific_exclamation_4 = strcmp(args[0], "!4");
    want_specific_exclamation_5 = strcmp(args[0], "!5");
    want_specific_exclamation_6 = strcmp(args[0], "!6");
    want_specific_exclamation_7 = strcmp(args[0], "!7");
    want_specific_exclamation_8 = strcmp(args[0], "!8");
    want_specific_exclamation_9 = strcmp(args[0], "!9");
    want_specific_exclamation_10 = strcmp(args[0], "!10");

    // If the user types "exit" the program ends.
    if(done == 0) {
      should_run = 0;
      exit(0);
    }

    // If the user wants to see their history by typing "history", call the print history function
    else if (want_history ==0){
      print_history();
    }

    // If the user types "!!" then execute the last command that was entered.
    else if(want_exclamation == 0){
      if(history[0] == NULL){
	printf("No commands in history!\n");
      }
      else{
	int b = 9;
	while(history[b] == NULL){
	  b--;
	}

	/* printing out the command so the user can see, declaring, initializing, and copying user data and
	   variables to be able to fork and execute a bit further down*/
	printf("%s\n", history[b]);

	char temp[MAX_LINE];
	strncpy(temp, history[b], MAX_LINE);
	int m = 0;
	args[m] = strtok(temp, " ");

	while (args[m] != NULL) {
	  m++;
	  args[m] = strtok(NULL, " ");
	}

	command = (char*) malloc(MAX_LINE);
	int z = 0;
	while(args[z] != NULL){
	  strcat(command,args[z]);
	  strcat(command, " ");
	  z++;
	}

	// fork the process, do some error checking, and execute the execvp with the args from user input
	pid = fork();
	if (pid < 0) {
	  printf("The fork has failed !!\n");
	  return 1;
	}
	else if (pid == 0) {
	  execvp_status = execvp(args[0], args);
	  if (execvp_status == -1) {
	    printf("Invalid Command!\n");
	    exit(1);
	  }
	}
	else {
	  wait(&wait_status);
	}

	// Now that the command is made and the args are executed, add this use command to the history array
	create_history(command);
      }
    }


    /*
     *
     * Start of the 10 IF statements(476 lines, scroll fast) that I couldn't turn into a function but work perfectly
     * nonetheless. If you are reading this code, look at the first IF statement and the next 9 are duplicates with
     * the condition changed by one. This will save you, the reader, time knowing that there are 10 repetitive if
     * statements here because I spent 4 hours trying to figure out how to put this into a function and failed.
     * Please scroll down to line 740.
     *
     */

    // If the user types "!1" then this branch will execute the code at the very bottom.
    else if (want_specific_exclamation_1 == 0){

      //Hard coded this to 0 because there are only 10 of them
      int b = 0;

      // error check for segmentation faults.
      if(history[b] == NULL){
	printf("Such a command is NOT in history!\n");
      }

      /* Do the same thing as earlier, modify the user input and ultimately fork, use execvp, and execute the
	 user command through a child process while the parent waits.*/
      else{
	printf("%s\n", history[b]);

	char temp[MAX_LINE];
	strncpy(temp, history[b], MAX_LINE);
	int m = 0;
	args[m] = strtok(temp, " ");

	while (args[m] != NULL) {
	  m++;
	  args[m] = strtok(NULL, " ");
	}

	command = (char*) malloc(MAX_LINE);
	int z = 0;
	while(args[z] != NULL){
	  strcat(command,args[z]);
	  strcat(command, " ");
	  z++;
	}

	// Error checks for fork() and execvp() also creating a child process
	pid = fork();
	if (pid < 0) {
	  printf("The fork has failed !!\n");
	  return 1;
	}
	else if (pid == 0) {
	  execvp_status = execvp(args[0], args);
	  if (execvp_status == -1) {
	    printf("Invalid Command!\n");
	    exit(1);
	  }
	}

	// Tell the parent to wait for the child to finish
	else {
	  wait(&wait_status);
	}

	// Add this command to the history, then free the memory as good practice
	create_history(command);
	free(command);
      }
    }
    else if (want_specific_exclamation_2 == 0){

      int b = 1;

      if(history[b] == NULL){
	printf("Such a command is NOT in history!\n");
      }
      else{
	printf("%s\n", history[b]);

	char temp[MAX_LINE];
	strncpy(temp, history[b], MAX_LINE);
	int m = 0;
	args[m] = strtok(temp, " ");

	while (args[m] != NULL) {
	  m++;
	  args[m] = strtok(NULL, " ");
	}

	command = (char*) malloc(MAX_LINE);
	int z = 0;
	while(args[z] != NULL){
	  strcat(command,args[z]);
	  strcat(command, " ");
	  z++;
	}

	pid = fork();
	if (pid < 0) {
	  printf("The fork has failed !!\n");
	  return 1;
	}
	else if (pid == 0) {
	  execvp_status = execvp(args[0], args);
	  if (execvp_status == -1) {
	    printf("Invalid Command!\n");
	    exit(1);
	  }
	}
	else {
	  wait(&wait_status);
	}

	// Add this command to the history, then free the memory as good practice
	create_history(command);
	free(command);
      }

    }
    else if (want_specific_exclamation_3 == 0){

      int b = 2;

      if(history[b] == NULL){
	printf("Such a command is NOT in history!\n");
      }
      else{
	printf("%s\n", history[b]);

	char temp[MAX_LINE];
	strncpy(temp, history[b], MAX_LINE);
	int m = 0;
	args[m] = strtok(temp, " ");

	while (args[m] != NULL) {
	  m++;
	  args[m] = strtok(NULL, " ");
	}

	command = (char*) malloc(MAX_LINE);
	int z = 0;
	while(args[z] != NULL){
	  strcat(command,args[z]);
	  strcat(command, " ");
	  z++;
	}

	pid = fork();
	if (pid < 0) {
	  printf("The fork has failed !!\n");
	  return 1;
	}
	else if (pid == 0) {
	  execvp_status = execvp(args[0], args);
	  if (execvp_status == -1) {
	    printf("Invalid Command!\n");
	    exit(1);
	  }
	}
	else {
	  wait(&wait_status);
	}

	// Add this command to the history, then free the memory as good practice
	create_history(command);
	free(command);
      }
    }
    else if (want_specific_exclamation_4 == 0){

      int b = 3;

      if(history[b] == NULL){
	printf("Such a command is NOT in history!\n");
      }
      else{
	printf("%s\n", history[b]);

	char temp[MAX_LINE];
	strncpy(temp, history[b], MAX_LINE);
	int m = 0;
	args[m] = strtok(temp, " ");

	while (args[m] != NULL) {
	  m++;
	  args[m] = strtok(NULL, " ");
	}

	command = (char*) malloc(MAX_LINE);
	int z = 0;
	while(args[z] != NULL){
	  strcat(command,args[z]);
	  strcat(command, " ");
	  z++;
	}

	pid = fork();
	if (pid < 0) {
	  printf("The fork has failed !!\n");
	  return 1;
	}
	else if (pid == 0) {
	  execvp_status = execvp(args[0], args);
	  if (execvp_status == -1) {
	    printf("Invalid Command!\n");
	    exit(1);
	  }
	}
	else {
	  wait(&wait_status);
	}

	// Add this command to the history, then free the memory as good practice
	create_history(command);
	free(command);
      }
    }
    else if (want_specific_exclamation_5 == 0){

      int b = 4;

      if(history[b] == NULL){
	printf("Such a command is NOT in history!\n");
      }
      else{
	printf("%s\n", history[b]);

	char temp[MAX_LINE];
	strncpy(temp, history[b], MAX_LINE);
	int m = 0;
	args[m] = strtok(temp, " ");

	while (args[m] != NULL) {
	  m++;
	  args[m] = strtok(NULL, " ");
	}

	command = (char*) malloc(MAX_LINE);
	int z = 0;
	while(args[z] != NULL){
	  strcat(command,args[z]);
	  strcat(command, " ");
	  z++;
	}

	pid = fork();
	if (pid < 0) {
	  printf("The fork has failed !!\n");
	  return 1;
	}
	else if (pid == 0) {
	  execvp_status = execvp(args[0], args);
	  if (execvp_status == -1) {
	    printf("Invalid Command!\n");
	    exit(1);
	  }
	}
	else {
	  wait(&wait_status);
	}

	// Add this command to the history, then free the memory as good practice
	create_history(command);
	free(command);
      }
    }
    else if (want_specific_exclamation_6 == 0){

      int b = 5;

      if(history[b] == NULL){
	printf("Such a command is NOT in history!\n");
      }
      else{
	printf("%s\n", history[b]);

	char temp[MAX_LINE];
	strncpy(temp, history[b], MAX_LINE);
	int m = 0;
	args[m] = strtok(temp, " ");

	while (args[m] != NULL) {
	  m++;
	  args[m] = strtok(NULL, " ");
	}

	command = (char*) malloc(MAX_LINE);
	int z = 0;
	while(args[z] != NULL){
	  strcat(command,args[z]);
	  strcat(command, " ");
	  z++;
	}

	pid = fork();
	if (pid < 0) {
	  printf("The fork has failed !!\n");
	  return 1;
	}
	else if (pid == 0) {
	  execvp_status = execvp(args[0], args);
	  if (execvp_status == -1) {
	    printf("Invalid Command!\n");
	    exit(1);
	  }
	}
	else {
	  wait(&wait_status);
	}

	// Add this command to the history, then free the memory as good practice
	create_history(command);
	free(command);
      }
    }
    else if (want_specific_exclamation_7 == 0){

      int b = 6;

      if(history[b] == NULL){
	printf("Such a command is NOT in history!\n");
      }
      else{
	printf("%s\n", history[b]);

	char temp[MAX_LINE];
	strncpy(temp, history[b], MAX_LINE);
	int m = 0;
	args[m] = strtok(temp, " ");

	while (args[m] != NULL) {
	  m++;
	  args[m] = strtok(NULL, " ");
	}

	command = (char*) malloc(MAX_LINE);
	int z = 0;
	while(args[z] != NULL){
	  strcat(command,args[z]);
	  strcat(command, " ");
	  z++;
	}

	pid = fork();
	if (pid < 0) {
	  printf("The fork has failed !!\n");
	  return 1;
	}
	else if (pid == 0) {
	  execvp_status = execvp(args[0], args);
	  if (execvp_status == -1) {
	    printf("Invalid Command!\n");
	    exit(1);
	  }
	}
	else {
	  wait(&wait_status);
	}

	// Add this command to the history, then free the memory as good practice
	create_history(command);
	free(command);
      }
    }
    else if (want_specific_exclamation_8 == 0){

      int b = 7;

      if(history[b] == NULL){
	printf("Such a command is NOT in history!\n");
      }
      else{
	printf("%s\n", history[b]);

	char temp[MAX_LINE];
	strncpy(temp, history[b], MAX_LINE);
	int m = 0;
	args[m] = strtok(temp, " ");

	while (args[m] != NULL) {
	  m++;
	  args[m] = strtok(NULL, " ");
	}

	command = (char*) malloc(MAX_LINE);
	int z = 0;
	while(args[z] != NULL){
	  strcat(command,args[z]);
	  strcat(command, " ");
	  z++;
	}

	pid = fork();
	if (pid < 0) {
	  printf("The fork has failed !!\n");
	  return 1;
	}
	else if (pid == 0) {
	  execvp_status = execvp(args[0], args);
	  if (execvp_status == -1) {
	    printf("Invalid Command!\n");
	    exit(1);
	  }
	}
	else {
	  wait(&wait_status);
	}

	// Add this command to the history, then free the memory as good practice
	create_history(command);
	free(command);
      }
    }
    else if (want_specific_exclamation_9 == 0){

      int b = 8;

      if(history[b] == NULL){
	printf("Such a command is NOT in history!\n");
      }
      else{
	printf("%s\n", history[b]);

	char temp[MAX_LINE];
	strncpy(temp, history[b], MAX_LINE);
	int m = 0;
	args[m] = strtok(temp, " ");

	while (args[m] != NULL) {
	  m++;
	  args[m] = strtok(NULL, " ");
	}

	command = (char*) malloc(MAX_LINE);
	int z = 0;
	while(args[z] != NULL){
	  strcat(command,args[z]);
	  strcat(command, " ");
	  z++;
	}

	pid = fork();
	if (pid < 0) {
	  printf("The fork has failed !!\n");
	  return 1;
	}
	else if (pid == 0) {
	  execvp_status = execvp(args[0], args);
	  if (execvp_status == -1) {
	    printf("Invalid Command!\n");
	    exit(1);
	  }
	}
	else {
	  wait(&wait_status);
	}

	// Add this command to the history, then free the memory as good practice
	create_history(command);
	free(command);
      }
    }
    else if (want_specific_exclamation_10 == 0){

      int b = 9;

      if(history[b] == NULL){
	printf("Such a command is NOT in history!\n");
      }
      else{
	printf("%s\n", history[b]);

	char temp[MAX_LINE];
	strncpy(temp, history[b], MAX_LINE);
	int m = 0;
	args[m] = strtok(temp, " ");

	while (args[m] != NULL) {
	  m++;
	  args[m] = strtok(NULL, " ");
	}

	command = (char*) malloc(MAX_LINE);
	int z = 0;
	while(args[z] != NULL){
	  strcat(command,args[z]);
	  strcat(command, " ");
	  z++;
	}

	pid = fork();
	if (pid < 0) {
	  printf("The fork has failed !!\n");
	  return 1;
	}
	else if (pid == 0) {
	  execvp_status = execvp(args[0], args);
	  if (execvp_status == -1) {
	    printf("Invalid Command!\n");
	    exit(1);
	  }
	}
	else {
	  wait(&wait_status);
	}

	// Add this command to the history, then free the memory as good practice
	create_history(command);
	free(command);
      }
    }

    /*
     * --------------------
     * End of the 10 if statements that I couldn't turn into a function but work perfectly nonetheless.
     * -------------------
     */

    /* Assuming no other recognized user inputs were found, then the input is just a regular command so we will
       try and execute it here like above. */
    else {

      // Starting the fork process to create a child process
      pid = fork();

      // Error checks, same as above.
      if (pid < 0) {
	printf("The fork has failed !!\n");
	return 1;
      }
      else if (pid == 0) {

	// This is the child process being created. It will use exit in the event there is an execvp error
	execvp_status = execvp(args[0], args);
	if (execvp_status == -1) {
	  printf("Invalid Command!\n");
	  exit(1);
	}
      }
      else {
	// This is the parent process waiting for the child to complete
	wait(&wait_status);
      }

      // Add this command to the history, then free the memory as good practice
      create_history(command);
      free(command);
    }

    // Resetting the args array to null for the next iteration of the main loop
    int q;
    for(q = 0; q < i; q++) {
      args[q] = NULL;
    }
  }
  return 0;
}
