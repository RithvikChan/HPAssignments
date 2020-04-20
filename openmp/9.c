#include <stdio.h>
#include <omp.h>
#include<stdlib.h>
#include<math.h>

static double num = 100000.0;

double sigmoid(double x){
	return (1.0 / (1.0 + pow(2.7186,-x)));
}
int main ()
{
   long i;  
   long Ncirc = 0;
   double pi, x, y, test, time;
   double r = 1.0; 
	
   time = omp_get_wtime();
	omp_set_num_threads(10);

   #pragma omp parallel
   {
	  #pragma omp for reduction(+:Ncirc) private(x,y,test)
      for(i=0;i<(int)num; i++)
      {
         x = sigmoid(random()/1640990000.0); 
         y = sigmoid(random()/1640990000.0);
         test = x*x + y*y;
		printf("%lf\n", x);
         if (test <= r*r){
            Ncirc++;
         }
       }
    }
	printf("%ld", Ncirc);
    pi = 4.0 * ((double)Ncirc/num);

    printf("\n PI is %lf ",pi);
    printf("Time %lf\n",omp_get_wtime()-time);

    return 0;
}
