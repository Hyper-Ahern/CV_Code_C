#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE *final_output;

/* This function finds the First Come First Server output based on the input in TaskSpec.txt that was given. First it
 * finds the wait times of each task, then adds them to the burst times and finds the average by subtracting the wait
 * times by the arrival times and dividing that sum by the number of tasks present. It takes in 3 arrays of information
 * that was gather by parsing the input file. This was the only function I could get to work as a function*/
void find_FCFS(int *processes, int num, int *burst_times, int *arrival_times){
    char printing_string[255] = {};
    int wait_times[num], turn_around_time[num], total_wait_time = 0, total_turn_around_time = 0;
    int h;
    wait_times[0] = 0;

    h = 1;
    while(h < num){
        wait_times[h] = burst_times[h - 1] + wait_times[h - 1] ;
        h++;
    }

    h = 0;
    while(h < num){
        turn_around_time[h] = burst_times[h] + wait_times[h];
        h++;
    }

    fputs("FCFS:\n", final_output);

    /* Calculate total wait and turnaround time then print them */
    h = 0;
    while (h < num){
        int u = h + 1;
        total_wait_time = total_wait_time + (wait_times[h] - arrival_times[h]);
        total_turn_around_time = total_turn_around_time + turn_around_time[h];
        sprintf(printing_string, "T%d\t%d\t%d\n", u, wait_times[h], turn_around_time[h]);
        fputs(printing_string, final_output);
        h++;
    }

    /* Printing out the waiting times of each task */
    int wait_time;
    h = 0;
    while(h < num){
        int u = h + 1;
        wait_time = (wait_times[h] - arrival_times[h]);
        sprintf(printing_string, "Waiting Time T%d : %d\n", u, wait_time);
        fputs(printing_string, final_output);
        h++;
    }

    /* Printing the average wait time which is forced to a float to have the 2 decimals for the assignment*/
    float s= (float)total_wait_time / (float)num;
    sprintf(printing_string, "Average Waiting Time Is:  %.2f\n", s);
    fputs(printing_string, final_output);
}


/* The order that this main function follows is:
 * 1) declare everything that is necessary (I moved a lot to the top when refactoring)
 * 2) Put the TaskSpec.txt into 3 separate arrays
 * 3) Put the TaskSpec.txt into one 2D array
 * 4) Call the FCFS function and pass it in the 3 separate arrays
 * 5) Do RR
 * 6) Do NPSJF
 * 7) Do PSJF
 * 8) Release all variables and memory
 */

int main() {

// *********** 1) DECLARATION OF ALL THE NECESSARY VARIABLES ***************

    int trigger;
    int current_time = 0;
    float average_wait_time = 0;
    int arrival_time;
    int previous_task_name;
    int timer_start = 0;
    int timer_finish = 0;
    int current_task = 0;
    int curr_task_name = 0;
    int is_empty = 0;
    int next_task = 0;
    int task_completion_time = 0;
    int timer_wait = 0;
    int previous_task = -1;
    int char_size = sizeof(char);
    static int END_OF_QUEUE = -2;
    char printing_string [255] = {};
    int data_array[255][255];
    int initial_data_array[255][255];
    char buff[255];
    char lines[255][255];
    int num_of_tasks;
    int minimum_burst_time;
    int i = 0;
    int q = 0;
    int l = 0;
    int m = 0;
    int n = 0;
    int k;
    int h = 0;
    int z = 0;
    char *token_for_strtok;
    char* file_input;


// ********************** 2) FIRST PULL FROM TASKSPEC.TXT FOR 3 SEPARATE ARRAYS *****************************


    /* This parse of the input file creates 3 seperate arrays (tasks, burst times, and arrival times) and then uses
     * that to send to the FCFS function. It does this by opening the file, then copying the string line by line then
     * chopping that up again into 3 seperate arrays denoted by the array name followed by a "2". This uses strtok and
     * atoi to parse and force the data into integers for the int arrays I use many different letters because I want to
     * keep h and k the same to assist with the creation of arrays at the end*/
    final_output = fopen("Output.txt", "w");
    FILE *fp;
    fp = fopen("TaskSpec.txt", "r");

    while (fgets(buff, 512, fp) != NULL) {
        int j;
        for(j = 0; j < 255; j++) {
            if(strncmp(&buff[j], "\n", 1) != 0) {
                lines[h][j] = buff[j];
            }
        }
        h++;
    }

    /* Creating arrays that are the size of the number of tasks */
    char *processes_array[h];
    char *arrival_time_array[h];
    char *burst_time_array[h];

    /* Spliting the input into 3 arrays here and shaving off the "T" in tasks */
    for (k = 0;  k < h; k++) {
        token_for_strtok = strtok(lines[k], ",");
        int r = 0;
        while (token_for_strtok != NULL) {
            if(r == 0) {
                processes_array[l] = token_for_strtok;
                l++;
            }
            else if(r == 1) {
                arrival_time_array[m] = token_for_strtok;
                m++;
            }
            else {
                burst_time_array[n] = token_for_strtok;
                n++;
            }
            token_for_strtok = strtok(NULL, ",");
            q++;
            r++;
        }
    }

    /* also creating arrays the size of an int multiplied by how many tasks */
    int array_size = sizeof(processes_array) / 8;
    int processes2 [array_size];
    int arrival_time2 [array_size];
    int burst_time2 [array_size];

    while(z < h) {
        processes2[z] = z + 1;
        arrival_time2[z] = atoi(arrival_time_array[z]);
        burst_time2[z] = atoi(burst_time_array[z]);
        z++;
    }


// ********************** 3) SECOND PULL FROM TaskSpec.txt FOR A 2D ARRAY *****************************

    /* Pulling a second time form TaskSpec.txt and putting the values into a 2d int array by forcing the
     * initial_data_array to int using atoi and also scraping the "T" from the initial_data_array file because it is an
     * int array. This singular 2d array is the basis for the other 3 algorithms found in the main. I would have
     * extracted them into functions but I couldnt figure our how. This takes the same input file and splits it into a
     * 2d array in one block. */
    fp = fopen("TaskSpec.txt", "r");
    file_input = (char*)malloc((256) * char_size);

    /* Forcing to int with atoi() while creating the 2D array */
    while (fgets(file_input, 100, fp)) {
        initial_data_array[i][0] = i + 1;
        strtok(file_input, ",");
        token_for_strtok = strtok(NULL, ",");
        initial_data_array[i][1] = atoi(token_for_strtok);
        token_for_strtok = strtok(NULL, ",");
        initial_data_array[i][2] = atoi(token_for_strtok);
        i++;
    }

    /* This is the as "h" from the first pull but it never hurts to double check */
    num_of_tasks = i;


// *********************** 4) FCFS *****************************************************************


    find_FCFS(processes2, array_size, burst_time2, arrival_time2);


// *********************** 5) RR *******************************************************************


    /* This is the round robin algorithm. It is implemented with a ready queue and it keeps iterating until either the
     * queue is empty or the end of the tasks. The new tasks that are arriving are placed in a ready state queue and
     * continues to check if all tasks are done every iteration in accordance with the time quantum which in this case
     * is 4. Once there are no more, the trigger "is_empty" is set to 1 and it starts to break the loop. The tasks are
     * done in the round robin fashion in accordance with their respective bursts. Finally, the output is printed to the
     * final output file.*/
    sprintf(printing_string, "\nRR:\n");
    fputs(printing_string, final_output);

    i = 0;
    while(255 > i ){
        data_array[i][4] = 0;
        data_array[i][3] = 0;
        i++;
    }

    /* Continue this giant loop while there are still tasks present (which is the same as the queue not being empty) */
    while(is_empty != 1 || current_task != num_of_tasks){
        i = current_task;
        while(num_of_tasks - 1 >= i) {
            trigger = initial_data_array[i][2] > 0 && current_time >= initial_data_array[i][1];
            switch (trigger){
                case 0:
                    break;
                case 1:
                    arrival_time = initial_data_array[i][1];
                    curr_task_name = initial_data_array[i][0];
                    previous_task_name = curr_task_name - 1;
                    data_array[previous_task_name][4] = 1;
                    data_array[previous_task_name][0] = initial_data_array[i][0];
                    data_array[curr_task_name][0] = END_OF_QUEUE;
                    data_array[previous_task_name][3] = current_time - arrival_time;
                    data_array[previous_task_name][2] = initial_data_array[i][2];
                    data_array[previous_task_name][1] = initial_data_array[i][1];
                    current_task++;
                    break;
            }
            i++;
        }

        /* Are all the tasks complete? if not continue if yes then set empty to true */
        int y = 0;
        i = previous_task;
        i++;
        while(num_of_tasks > y && END_OF_QUEUE != data_array[i - 1][0]){
            int w = i % current_task;
            i = w;
            if (!(data_array[i][4] == 1)) {
                is_empty = 1;
            }
            else{
                next_task = i;
                w = next_task % current_task;
                next_task = w;
                is_empty = 0;
                break;
            }
            i++;
            y = y + 1;
        }

        trigger = is_empty;
        switch (trigger){
            case 0:
                break;
            case 1:
                current_time++;
                break;
        }

        /* using the time quantum (4) to see if the task has less than the tim quantum number of bursts left. If so then
         * the time is going to be equal to the quantum + the next task but if not then the time taken will be equal to
         * that quantum. */
        data_array[next_task][2] = data_array[next_task][2] - 4;
        trigger = 0 <= data_array[next_task][2];
        switch (trigger){
            case 0:
                task_completion_time = 4 + data_array[next_task][2];
                data_array[next_task][2] = 0;
                break;
            case 1:
                task_completion_time = 4;
                break;
        }

        i = 0;
        while(data_array[i][0] != END_OF_QUEUE){

            trigger = i != next_task && 0 < data_array[i][2];
            switch (trigger){
                case 0:
                    break;
                case 1:
                    data_array[i][3] = data_array[i][3] + task_completion_time;
            }
            i++;
        }

        /* using variables and the task time to create a cycle that keeps track of when the next task must begin and
         * when the old task is done as well as other assorted time components to the algorithm */
        timer_start = current_time;
        curr_task_name = data_array[next_task][0];
        timer_finish = timer_start + task_completion_time;


        if (is_empty != 1){
            sprintf(printing_string, "T%d\t%d\t%d\n", curr_task_name, timer_start, timer_finish);
            fputs(printing_string, final_output);
        }

        current_time = timer_finish;
        data_array[next_task][1] = current_time;

        trigger = data_array[next_task][2] == 0;
        switch (trigger){
            case 0:
                break;
            case 1:
                data_array[next_task][4] = 0;
        }
        previous_task = next_task;
    }

    /* Printing out the waiting times of each task */
    i = 0;
    while(i < num_of_tasks){
        sprintf(printing_string, "Waiting Time T%d : %d\n", data_array[i][0], data_array[i][3]);
        fputs(printing_string, final_output);
        average_wait_time = (float) average_wait_time + (float) data_array[i][3];
        i++;
    }

    /* Printing the average wait time which is forced to a float to have the 2 decimals for the assignment*/
    average_wait_time = (float) average_wait_time / (float)num_of_tasks;
    sprintf(printing_string, "Average Waiting Time Is:  %.2f\n", average_wait_time);
    fputs(printing_string, final_output);


// ********************************** 6) NPSJF ****************************


    /* This is the Non Preemptive Shortest Job First algorithm. It sets up a ready queue similar to the round robin
     * that was looked at before and puts arriving tasks into them. Again it has a check to see if all tasks have been
     * completed. While they haven't the shortest task available at any given time will be the one that is processed. It
     * locates the shortest task through a simple complete iterative while loop and then keeps track of the shortest task
     * if the new task being compared is shorter it will update teh shortest task variable and continue until there are
     * no more comparisons. At this time it has the newest shortest task and will process that until it is done. Finally,
     * it prints to the final output file.*/

    /* Resetting all the relevant variables to be able to preform the next algorithm and printing title*/
    printing_string[255];
    sprintf(printing_string, "\nNPSJF:\n");
    fputs(printing_string, final_output);

    previous_task = -1;
    current_task = 0;
    next_task = 0;
    is_empty = 0;
    average_wait_time = 0;
    current_time = 0;

    /* Use this big while loop to continue until there are no more tasks to be done */
    while(is_empty != 1 || num_of_tasks != current_task){
        i = current_task;
        while(num_of_tasks - 1 >= i ) {
            trigger = current_time >= initial_data_array[i][1];
            switch (trigger){
                case 0:
                    break;
                case 1:
                    curr_task_name = initial_data_array[i][0];
                    previous_task_name = curr_task_name - 1;
                    data_array[previous_task_name][1] = initial_data_array[i][1];
                    data_array[previous_task_name][0] = initial_data_array[i][0];
                    data_array[curr_task_name][0] = END_OF_QUEUE;
                    data_array[previous_task_name][2] = initial_data_array[i][2];
                    current_task++;
                    break;
            }
            i++;
        }

        /* Are all the tasks done yet? If not then continue but if so set the empty variable to indicate that */
        for(i = 0; data_array[i][0] != - 2; i++){
            if (!(data_array[i][2] != 0)){
                is_empty = 1;
            }
            else{
                is_empty = 0;
                break;
            }
        }

        /* Random large number to make sure that the first trigger is hit in order to find the shortest task and run it.
         * I suspected no task would be more than 10,000 time units. It then keeps the clock running while it searches
         * for new arriving tasks.*/
        minimum_burst_time = 10000;
        i = 0;
        while (END_OF_QUEUE != data_array[i][0]){
            trigger = minimum_burst_time > data_array[i][2] && 0 < data_array[i][2] ;
            switch (trigger){
                case 0:
                    break;
                case 1:
                    next_task = i;
                    minimum_burst_time = data_array[i][2];
                    break;
            }
            i++;
        }

        trigger =  previous_task != next_task;
        switch (trigger){
            case 0:
                (current_time++);
                break;
            case 1:
                curr_task_name = data_array[next_task][0];
                timer_wait = current_time - initial_data_array[next_task][1];
                timer_start = current_time;
                data_array[next_task][3] = timer_wait;
                int c_time = data_array[next_task][2] + current_time;
                timer_finish = c_time;
                current_time = c_time;
                data_array[next_task][2] = 0;
                previous_task = next_task;
                sprintf(printing_string, "T%d\t%d\t%d\n", curr_task_name, timer_start, timer_finish);
                fputs(printing_string, final_output);
        }
    }

    /* Printing out the waiting times of each task */
    i = 0;
    while(num_of_tasks > i){
        sprintf(printing_string, "Waiting Time T%d : %d\n", data_array[i][0], data_array[i][3]);
        fputs(printing_string, final_output);
        average_wait_time = (float) average_wait_time + (float) data_array[i][3];
        i++;
    }

    /* Printing the average wait time which is forced to a float to have the 2 decimals for the assignment*/
    average_wait_time = (float) average_wait_time / (float)num_of_tasks;
    sprintf(printing_string, "Average Waiting Time Is:  %.2f\n", average_wait_time);
    fputs(printing_string, final_output);


// ************************************** 7) PSJF *************************************

    /* This is the Preemptive Shortest Job First algorithm. It is very similar to the previous algorithm we looked at so
     * I wont explain everything again. There is still a ready queue, a chedck for all tasks being completed, and a check
     * for finding the shortest task. The order is always the same, get the information, check if all tasks are complete,
     * if not find the shortest task, execute the task, and then once all of them are done, print the result to the
     * final output file. The difference here is we can have partially completed tasks.*/

    /* Resetting all the relevant variables to be able to preform the next algorithm and printing title*/
    printing_string[255];
    sprintf(printing_string, "\nPSJF:\n");
    fputs(printing_string, final_output);

    previous_task = -1;
    timer_finish = 0;
    minimum_burst_time;
    current_time = 0;
    is_empty = 0;
    average_wait_time = 0;
    current_task = 0;
    timer_start = 0;

    i = 0;
    while(num_of_tasks + 1 > i){
        data_array[i][3] = 0;
        i++;
    }

    /* This loop will keep going until there are no more next tasks to complete and it loads them into the queue.*/
    while(!is_empty || num_of_tasks != current_task){
        int the_next_task = num_of_tasks + 1;
        next_task = the_next_task;
        for (i = current_task; num_of_tasks - 1 >= i; i++) {
            if(!(initial_data_array[i][1] <= current_time)){
                break;
            }
            else{
                curr_task_name = initial_data_array[i][0];
                previous_task_name = curr_task_name - 1;
                data_array[previous_task_name][2] = initial_data_array[i][2];
                data_array[previous_task_name][0] = initial_data_array[i][0];
                data_array[curr_task_name][0] = END_OF_QUEUE;
                data_array[previous_task_name][1] = initial_data_array[i][1];
                current_task++;
            }
        }

        /* Are there any tasks left to complete here? If so continue otherwise set the empty vaiable to true */
        is_empty = 1;
        for(i = 0; END_OF_QUEUE != data_array[i][0]; i++){
            if (!(data_array[i][2] > 0)){
                is_empty = 1;
            }
            else{
                is_empty = 0;
                break;
            }
        }

        trigger = is_empty;
        switch (trigger){
            case 0:
                break;
            case 1:
                current_time++;
                break;
        }

        /* The idea here is to find the shortest task that still remains. I used 10,000 as a huge number to ensure the
         * first task would always happen because I dont think there will be a burst of more than 10,000 in this
         * assignment. */
        minimum_burst_time = 10000;
        i = 0;
        while(data_array[i][0] != END_OF_QUEUE){
            trigger = minimum_burst_time > data_array[i][2] && 0 < data_array[i][2];
            switch (trigger){
                case 0:
                    break;
                case 1:
                    next_task = i;
                    minimum_burst_time = data_array[next_task][2];
                    break;
            }
            i++;
        }

        i = 0;
        while(data_array[i][0] != END_OF_QUEUE){
            trigger = i != next_task && 0 < data_array[i][2] ;
            switch (trigger){
                case 0:
                    break;
                case 1:
                    data_array[i][3] = data_array[i][3] + 1;
                    break;
            }
            i++;
        }

        /* The idea here is to keep checking which task has the smallest burst time so that task can begin. If there is
         * a switch of tasks, there is a print statement and a transition block to keep a record of which tasks are
         * swapping off and which tasks are starting. These are essentially partially completed jobs and will end in
         * storing the current time and the previous task as the finish time and next task respectively. */
        trigger = previous_task != next_task  && 0 != data_array[previous_task][0];
        switch(trigger){
            case 0:
                data_array[next_task][2]--;
                timer_finish++;
                break;
            case 1:
                sprintf(printing_string, "T%d\t%d\t%d\n", data_array[previous_task][0], timer_start, timer_finish);
                data_array[next_task][2]--;
                timer_start = current_time;
                timer_finish++;
                data_array[next_task][1] = timer_start;
                fputs(printing_string, final_output);
                break;
        }
        previous_task = next_task;
        current_time = timer_finish;
    }
    sprintf(printing_string, "T%d\t%d\t%d\n", data_array[previous_task][0], timer_start, timer_finish);

    /* Printing out the waiting times of each task */
    i = 0;
    while(num_of_tasks > i){
        average_wait_time = (float) average_wait_time + (float) data_array[i][3];
        sprintf(printing_string, "Waiting Time T%d :  %d\n", data_array[i][0], data_array[i][3]);
        fputs(printing_string, final_output);
        i++;
    }

    /* Printing the average wait time which is forced to a float to have the 2 decimals for the assignment*/
    average_wait_time = (float) average_wait_time / (float)num_of_tasks;
    sprintf(printing_string, "Average Waiting Time Is:  %.2f\n", average_wait_time);
    fputs(printing_string, final_output);


// ************************* 8) END *********************


    // Freeing Variables and memory as well as closing files
    free(file_input);
    fclose(final_output);
    fclose(fp);
}
