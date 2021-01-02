/* This program needs to be run with gcc stats.c -lm to make sure the math library is linked or else
   the square root function will not work. */
#include <stdio.h>
#include <math.h>

int main(){
  // Assigning floats to printed numbers and int to counters (declaring and initializing)
  float arr [10000], num, min, max, avg, count, sum, stdev;
  int  i, n;
  count =0;
  i=0;
  sum=0;
  
  /* Taking in input until there is no more, comparing each number to the min/max, putting
     each number in an array for later calculation, and keeping a running sum/count */
  while ((scanf("%f", &num)) == 1){
    if(i == 0){
      n=num;
    }

    if (i==1){
      max=num;
      min=num;
    }

    if(num > max && i>=1){
      max=num;
    }
    else if(num < min && i>=1){
      min=num;
    }
    else{}

    if (i>=1){
    arr[i-1]=num;
    count++;
    sum = sum + num;   
    }

    i++;
  }

  // Creating the average and initializing variable for the "for" loop
  avg = (sum / count);
  int j = 0;
  
  // Computing the standard deviation of the numbers
  for (j; j < count ; j++){
    float temp = arr[j];
    float temp2 = (temp - avg);
    float temp3 = temp2*temp2;
    stdev  = stdev + temp3;
  }

  // Finishing the standard deviation calculations then printing out values to 3 decimal places
  stdev =  (stdev / n);
  stdev = sqrt(stdev);

  printf("m = %.3f\nM = %.3f\na = %.3f\ns = %.3f\n", min, max, avg, stdev);
}
