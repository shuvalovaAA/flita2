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
                //{
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
                //}
        }
        fputc ('}',f2);
        fprintf (f2,"%c",'\n');
        fclose(f2);
        //free up memory
        free ( a );
        system ("dot f2.dot -Tpng -o f2.png");
        return 0;
}

