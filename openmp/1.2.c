#include <stdio.h> 
#include <omp.h>

int main()
{
	omp_set_num_threads(4);
	#pragma omp parallel                   
	{
    	printf("Hello world by THREAD: %d\n", omp_get_thread_num());
	} 
}
