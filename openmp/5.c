#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <math.h>


# define noofpts 1000
# define iterations 1000

struct comp{
   double r;
   double i;
};

struct comp imagnum,c ;
int num = 0;

void calculatefractal(struct comp c)
{

	struct comp test = c;
	int iter;
	double temp;
	omp_set_num_threads(4);
	#pragma omp parallel
	{
		for (iter=0; iter<iterations; iter++)
		{
		temp = (test.r*test.r)-(test.i*test.i)+c.r;
		test.i = test.r*test.i*2+c.i;
		test.r = temp;
		if ((test.r*test.r+test.i*test.i)>4.0) 
		{
			#pragma omp atomic
			num++;
			break;
			}
		}
	}
}



int main()
{
	int i, j;
	double area;
	double exp  = 1.0e-5;

	omp_set_num_threads(4);
	#pragma omp parallel for private(c, j)
	for (i=0; i<noofpts; i++) 
	{
		for (j=0; j<noofpts; j++) 
		{
			c.r = -2.0+2.5*(double)(i)/(double)(noofpts)+exp;
			c.i = 1.125*(double)(j)/(double)(noofpts)+exp;
			calculatefractal(c);
		}
	}
	area=2.0*2.5*1.125*(double)(noofpts*noofpts-num)/(double)(noofpts*noofpts);
	printf("Area %lf\n",area);
	return 0;
}
