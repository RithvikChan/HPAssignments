#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#define N 5
#define FS 38
#define NMAX 10

struct node {
   int data;
   int fib;
   struct node* next;
};

int fibonacci(int n) {
   int x, y;
   if (n < 2) {
      return (n);
   } else {
      x = fibonacci(n - 1);
      y = fibonacci(n - 2);
    return (x + y);
   }
}

void update(struct node* temp) 
{
   int n;
   n = temp->data;
   temp->fib = fibonacci(n);
}


struct node* init_list(struct node* p) {
    int i;
    struct node* head = NULL;
    struct node* temp = NULL;
    
    head = malloc(sizeof(struct node));
    p = head;
    p->data = FS;
    p->fib = 0;
    for (i=0; i< N; i++) {
       temp  = malloc(sizeof(struct node));
       p->next = temp;
       p = temp;
       p->data = FS + i + 1;
       p->fib = i+1;
    }
    p->next = NULL;
    return head;
}

int main(int argc, char *argv[]) {
     double start, end;
     struct node *p=NULL;
     struct node *temp=NULL;
     struct node *head=NULL;
     struct node *parr[NMAX]; 
     int i, count=0;
     
     p = init_list(p);
     head = p;
     start = omp_get_wtime();

	#pragma omp parallel 
	{
		#pragma omp single
		{
			p=head;
			while (p) {
				#pragma omp task firstprivate(p)
				{
					update(p);
				}
			  p = p->next;
		   }
		}
	}


     end = omp_get_wtime();
     p = head;
	 while (p != NULL) {
        printf("%d : %d\n",p->data, p->fib);
        temp = p->next;
        free (p);
        p = temp;
     }  
     free (p);

     printf("Time: %f seconds\n", end - start);

     return 0;
}
