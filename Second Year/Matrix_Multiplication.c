#include <stdio.h>
#include <math.h>

int main(){

  int l=0;
  int m=0;
  int n=0;
  int i=0;
  int j=0;
  int k=0;
  
  scanf("%d%d%d", &l, &m, &n);
  //printf("%d,%d,%d", l,m,n);
  float lm[l][m];
  float mn[m][n];
  float product[l][n];
  float rowSum=0;

  for(i = 0; i < l; i++){
    for(j = 0; j < m; j++){
      scanf("%f ", &lm[i][j]);
      // printf("%f\t", lm[i][j]); 
    }
  }

  for(i = 0; i < m; i++){
    for(j = 0; j < n; j++){
      scanf("%f ", &mn[i][j]);
      // printf("%f\t", mn[i][j]);
    }
  }

  for(i = 0; i < l; i++){
    for(j = 0; j < n; j++){
      for(k = 0; k < m; k++){
	rowSum = rowSum + lm[i][k] * mn[k][j];
      }

      product[i][j]= rowSum;
      rowSum = rowSum - rowSum;
    }
  }

  printf("%d %d\n", l,n);

  for(i = 0; i < l; i++){
    for(j = 0; j < n; j++){
      printf("%.2f\t", product[i][j]);
    }
    printf("\n");
  }

  return 0;
}
