#include <stdio.h>
#include <omp.h>
#include<math.h>
#define THREADS 4

// Each thread does 123...123...123 steps = num of threads left.
int main()
{
	static int totalsteps = 10000;
	double singlestep  = 1.0/(double)totalsteps;
    double pi;
    double value = 0;	
    omp_set_num_threads(THREADS);
    #pragma omp parallel
    {   
        double interm;
		#pragma omp for reduction(+:value)        
        for(int i = 0; i<totalsteps; i++)
        {
            interm = (i + 0.5)*singlestep;
            sum += 4.0/(1.0 + interm*interm);
        }
        
		# pragma omp critical
        pi= sum * singlestep;
   
    }    
	printf("%lf",pi);
    return 0;
}
