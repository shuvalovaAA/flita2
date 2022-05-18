#include <stdio.h>
#include <string.h>
#include <stdlib.h> // for malloc and free
void sort(int n, int *b, int *c);
int main()
{
	int n;
	printf("The number of vertices of the graph: ");
	scanf("%d", &n);
	int *a;
	// allocate memory
	a = ( int * ) malloc ( n * n * sizeof(int) );
	// open file
	FILE *f2;
	f2=fopen("f2.dot", "w");
	printf("Enter data for the matrix :\n");
	int i, j ;
	if( f2 )
		for( i = 0; i < n; i++ )
		{
			for( j = 0; j < n; j++ )
			scanf("%3d", &(a[i*n+j]));
		}
	else printf("file not open \n");
	// write the matrix to a file
	char *text1 = "graph {\n";
	fputs (text1,f2);
	for( i = 0; i < n; i++ ) // input vertex
		fprintf(f2,"%d %s \n", i,";");
	for( j = 0; j < n; j++ ) // input edge
	{
		for( i = 0; i < n; i++ )
			if ( (a[i*n+j] != 0) && (j >= i) )
				fprintf(f2,"%d %s %d %s \n", j,"--", i,";");

	}
	fputs("} \n",f2);
	// sorting an array by vertex degree
	int *b, *c;
  	b = ( int * ) malloc ( n * sizeof(int) );
  	c = ( int * ) malloc ( n * sizeof(int) );
  	int sum;
  	for( j = 0; j < n; j++ )            
  	{ 
    		sum = 0;
    		for(i = 0; i < n; i++) 
      			if( a[i*n+j] != 0 && (j != i)) sum ++;
    		b[j] = sum; 
    		c[j] = j;            
  	} 
  	sort ( n, b, c );
  	printf("Shell sorted vertex(and their degrees):\n ");
  	for( i = 0; i < n; i++ )
    		printf("%3d(%d)",c[i],b[i]);
    	printf("\n");
  	fclose(f2);
  	//free up memory 
  	free ( a );  
  	free ( b );
  	free ( c );
  	system ("dot f2.dot -Tpng -o f2.png");
  	return 0;
}
void sort(int n, int *b, int *c)
{
	int i,j,tmp, tmpi;
  	int step = n/2;
  	while ( step > 0 ) 
  	{
     		for (i = step; i < n; i++)
     		{
       			tmp = b[i];
       			tmpi = c[i];
       			for (j = i; j >= step; j = j-step)
       			{
          			if (tmp > b[j-step])   
          			{
            				b[j] = b[j-step];
            				c[j] = c[j-step]; 
          			}		 
          			else break;
       			}
       			b[j] = tmp;
       			c[j] = tmpi;
     		}
  		step = step/2;
	} 
}
