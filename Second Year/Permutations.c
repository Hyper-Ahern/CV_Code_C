#include <stdio.h>
#include <string.h>
#include <stdlib.h>

  // Swaps individual numbers for eventual permutation
  void moveValues(char *first, char *second) {
    char tempValue;
    tempValue = *first;
    *first = *second;
    *second = tempValue;
  }

  // Creates the number to have permutation done to it based off
  // of the passed in argv value when running the program
  int createNumber(int num) {

    long long int result = num;
    int i;
    long long int temp = num;

    // Using math to create the number (3 -> 321 as an example)
    for(i = 0; i < num-1; i++){
      result = result * 10;
      result = result + (temp-1);
      temp--;
    }

    return result;
  }

  // This does permutation by swaping numbers around and recursively
  // calling itself as many times as there are numbers.
  void permutation(char *number, int count, int length) {
    
    if (!(length == count)) {
      int j; 
      for (j = count; j <= length; j++) {

        // Pointer arithmetic to swap the next number 
        //with the one + current j position then permute
        //again
        moveValues((number+count), (number+j));
        permutation(number, count+1, length);
        moveValues((number+count), (number+j));
      } 
    } else {

      //TRY TO CHANGE THIS TO AN INT THEN ORDER THEM??
	printf("%s \n", number);
    }
  }

  // Main method
  int main(int argc, char **argv) {
    char number[100];
    long long int num;

    // Changing a string to an int
    num = atoi(argv[1]);
    num = createNumber(num);

    // Changing it back to a string for easier permutation
    sprintf(number, "%d", num);
    int length = strlen(number);

    permutation(number, 0, length-1);

    return 0;
  }
