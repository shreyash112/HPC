#include <stdio.h> 
#include<stdlib.h>
#include <time.h>
#define M 512
#define B 8
double CLOCK() {
        struct timespec t;
        clock_gettime(CLOCK_MONOTONIC,  &t);
        return (t.tv_sec * 1000)+(t.tv_nsec*1e-6);
}

int main(int argc, char **argv)
{
    int i,j,k,jj,kk,en;
    double start, finish, total,start1,finish1,total1;
    float a[M][M], b[M][M], c[M][M],b_t[M][M];
	float sum;
/* Set the seed for the random number generators for the data */
    srand(145);

/* Initialize a, b and c */
    for (i=0; i<M; i++)
       for (j=0; j<M; j++)
          a[i][j] = (float)rand()/(float)RAND_MAX;

    for (i=0; i<M; i++)
       for (j=0; j<M; j++)
           b[i][j] = (float)rand()/(float)RAND_MAX;

    for (i=0; i<M; i++)
       for (j=0; j<M; j++)
           c[i][j] = 0.;

   start = CLOCK();
	for (i =0; i<M; i++){
       for (j=0; j<M; j++){
         for (k=0; k<M; k++){
		 c[i][j] += a[i][k] * b_t[k][j];}
	   }
	}
	finish = CLOCK();
		
	for (i=0; i<M; i++)
       for (j=0; j<M; j++)
           c[i][j] = 0.;

/* Start timing */
    start1 = CLOCK();
/* This is the only portion of the code you should modify to improve performance. */
//Calculate the trasnpose of the B matrix and then multiply to decrease the cache misses
	for(i=0; i<M; i++)
	   for(j=0; j<M; j++)
		  b_t[j][i] = b[i][j]; 
	
	  
//Multiply matriz A and B
     for (i =0; i<M; i++)
       for (j=0; j<M; j++)
         for (k=0; k<M; k++)
	 c[i][j] += a[i][k] * b_t[j][k];
 
//Not able to get correct values in the matrix using blocks for the multiplication 
/*
for (kk = 0; kk < en; kk = kk+B){ 
      for (jj = 0; jj < en; jj = jj+B){      
         for (i = 0; i< M; ++i){     
            for (j = jj; j < jj + B; ++j) {
				sum = c[i][j];
               for (k = kk; k < kk + B; ++k) {
				  printf("i = %li, j = %li; k = %li\n", i, j, k);
                  sum = sum + a[i][j] * b[k][j];
                  }
                 c[i][j] = sum;
               }
			    //printf("%f\n",c[i][j]);
		 }
	  }
	  
	 
}
*/
    finish1 = CLOCK();
/* End timing */
    total = finish - start;
	total1 = finish1 - start1;
    printf("Time for the loop = %4.2f milliseconds\n", total);
	printf("Time for the optmized loop = %4.2f milliseconds\n", total1);
    printf("Element %d,%d = %f\n", 0, 0, c[0][0]); 
    printf("Element %d,%d = %f\n", 63, 63, c[63][63]); 
    printf("Element %d,%d = %f\n", 511, 511, c[511][511]); 
    return 0;
}
