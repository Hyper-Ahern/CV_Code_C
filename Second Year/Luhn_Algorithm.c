#include <stdio.h>

int main(){

  int x, y, z, n, i, j;
  int count=0;
  long long int q=1;

  scanf("%d", &n);

  long long int testArr[n];
  int countArr[n];

  for(i = 0; i < n; i++){
    scanf("%lld", &testArr[i]);
  }

  for(i = 0; i < n; i++){
    q = testArr[i];
    count = 0;
    while(!(q==0)){
      q= q/10;
      count++;
    }
    countArr[i]=count;
  }

  for(i = 0; i < n; i++){
    q = testArr[i];
    long long int xArr[countArr[i]];
    
    for(j=0; j <= countArr[i]-1; j++){
	xArr[j] = q%10;
	q = q/10;
    }

    for(j=0; j <= countArr[i]-1; j++){
      if(j%2!=0){
	xArr[j]= xArr[j]*2;
      }
    }

    for(j=0; j <= countArr[i]-1; j++){
      if(xArr[j] >= 10){
	q = xArr[j];
	xArr[j] = xArr[j]/10 + q%10;
      }
    }

    int sum =0;

    for(j=countArr[i]-1; j >= 0; j--){
      sum = sum + xArr[j];
    }

    if(sum%10==0){
      printf("valid\n");
    } else {
      printf("invalid\n");
    }
  }





  return 0;
}
