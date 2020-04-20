#include <stdio.h>
#include <omp.h>
#include<math.h>
#define THREADS 100

// Each thread does 123...123...123 steps = num of threads left.
int main()
{
	double totalsteps = 10000;
	double singlestep;

    double pi, sum[THREADS];
    int noofthreads;
    int thread = 0;
    singlestep = 1.0/(double)totalsteps;

    omp_set_num_threads(THREADS);
    #pragma omp parallel
    {   
        double interm;
        int threadid = omp_get_thread_num();
        int nt = omp_get_num_threads();
        sum[threadid] = 0.0;
        for (double calcul = threadid; calcul < totalsteps; calcul += nt){
            interm = (double)(calcul+0.5)*singlestep; // Add i+0.5 based on i = 1...4 for each thread same as i
            sum[threadid] += 4.0/(1.0+interm*interm);
        }
        pi += sum[threadid] * singlestep;

    }    
	printf("%lf",pi);
    return 0;
}
