#include <stdio.h>
#include <string.h>
#include <stdlib.h> // for malloc and free
int main()
{
	int n;
	printf("The number of vertices of the graph : \n");
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
	{
		for( i = 0; i < n; i++ )
		{
			for( j = 0; j < n; j++ )
				scanf("%3d", &(a[i*n+j]));
		}
	}
	else printf("file not open \n");
	// the matrix
	printf("Adjacent matrix :\n");
	for( i = 0; i < n; i++ )
	{
		for( j = 0; j < n; j++ )
			printf("%3d", a[i*n+j]);
		printf("\n");
	}
	// write the matrix to a file
	char *text1 = "digraph {";
        fputs (text1,f2);
        fprintf (f2,"%c",'\n');
        for( i = 0; i < n; i++ )
        {
                fprintf(f2,"%d", i);
                fputc (';',f2);
                fprintf (f2,"%c",'\n');
        }
        int w;
        fprintf (f2,"%c",'\n');
        for( j = 0; j < n; j++ )
        {
                for( i = 0; i < n; i++ )
                    if ( a[i*n+j] != 0 )
                    {
                     w = a[i*n+j];
                     do
                        {
                                fprintf(f2,"%d", j); fputs (" -> ",f2); fprintf(f2,"%d", i);
                                fputc (';',f2);
                                fprintf (f2,"%c",'\n');
                                w--;
                        }
                     while (w!= 0);
                    }
        }
	int v_out, v_in;
	int stop_check = 0;
	j = 0;
	do
	{
		v_out = 0;
		for( i = 0; i < n; i++ ) 
			if ((a[i*n+j] != 0) && (j != i))
				 v_out = 1; //there is a path from the vertices
		if ( v_out == 0 )
			stop_check = 1;
		j++;
	} while ( ( j < n ) && !stop_check );
	int stop_check1 = 0;
	i = 0;
	do
	{
		v_in = 0;
		for( j = 0; j < n; j++ ) 
			if ((a[i*n+j] != 0) && (i != j)) 
				v_in = 1; //there is a path in the vertices
		if ( v_in == 0 ) 
			stop_check1 = 1;
		i++;
	} while ( ( i < n ) && !stop_check1 );
	if ( !stop_check && !stop_check1) 
		printf("For the vertex there is in/out(except i=j)\n");
	else printf("TFor the vertex not in or out \n");
	// checking the connection of vertices
	int b[n-1];
	int k;
	for( k = 0; k < n; k++ ) b[k] = -1;
	int num;
	int bfull = 0;
	j = 0; k = 0;
	int stop = 0;
	int nowr; // don't write vertices number to the array b
	int cyc = n;
        do
	{
		if (stop == 0)
			for( i = 0; i < n; i++ )
			{
				b[0] = 0;
				if ( (a[i*n+j] != 0) && (i != j) && !stop )
				{
					nowr = 0;
					for( num = 1; num < n; num++ ) 
						if( j == b[num] )
							 nowr = 1;
					if (!nowr)
					{
						printf(" Arc to bypass j->i: %d %d\n", j, i);
						b[k] = j;
						k++;
						if( k == n ) stop = 1;
					}
					j = i ;
				}
			}
                cyc--;
		if ( k != n && nowr ) j++;
	} while ( !stop_check && !stop_check1 && !stop && (cyc != 0));
        int mnoc = 0;
        if ( k != n ) mnoc = 1;
        bfull = (mnoc == 0) && stop;
	printf("Connected vertices of the graph:");
	for( num = 0; num < n; num++ ) printf("%3d", b[num]);
	printf("\n");
	if ( !stop_check && !stop_check1 && bfull) printf("The graph is CONNECTED. \n");
	else printf("The graph is NOT CONNECTED. \n");
	fputs ("} \n",f2);
	fclose(f2);
	// free up memory
	free ( a );
	system ("dot f2.dot -Tpng -o f2.png");
	return 0;
}
