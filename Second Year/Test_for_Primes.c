#include <stdio.h>

int main(){

  // Making sure the variable can handle 64 bit input
  unsigned long long int num;
  int check;

  // Asking the user for input
  printf("Enter a number: ");
  scanf("%lld",&num);
  int num_check = num - 1;

  /* Running a for loop starting at 2 to see if the number is prime by
     checking each number in the loop modulo the number given by the user
     and if that eauals 0 then there is a divisor other than 1. */
  for ( check = 2; check <= num_check; check++ ){
    if( num % check == 0 || num == 0 || num == 1 || num == 2 ){
      printf("%lld is not a prime number.\n", num);
      break;
    }
    else if ( check + 1 == num ){
      printf("%llu is a prime number.\n", num);
      break;
    }
  }

  return 0;
}
