#include  <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int n = 10;
const int m = 10;

void fill_matrix_randomly(int matrix[n][m], int max_value, int x, int y);
void write_matrix(int matrix[n][m], int x, int y);
int find_max(int* vector, int vector_size);
int find_min(int* vector, int vector_size);
void write_vector(int* vector, int vector_size);

int main(int argc, char* argv[])
{
    int my_rank = 0;
    int comm_size = 0;

    int root=0;
    int a[n][m];
    int x,y;
    int receive_buffer[m];
    int partial_max[m];
    int partial_min[m];

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

   /*
    if (comm_size != n)
    {
        printf("Please set process count = %d and run again.", n);
        MPI_Finalize();
        return 0;
    }
    */

    if (my_rank == 0)
    {

    	scanf("%d %d",&x,&y);
    	int count = 5;
    	
        MPI_Bcast(&x, comm_size, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast(&y, comm_size, MPI_INT, 0, MPI_COMM_WORLD);
        fill_matrix_randomly(a, 10, x, y);
        write_matrix(a,x,y);    
    }
    

    
    
    
    
   
    MPI_Scatter(a, m, MPI_INT, receive_buffer, m, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Reduce(receive_buffer, partial_max, n, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
    MPI_Reduce(receive_buffer, partial_min, n, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
    if (my_rank == 0)
    {
        printf("Vector of partial max values.\n");
        write_vector(partial_max, x);
        printf("Vector of partial min values.\n");
        write_vector(partial_min, x);

        int max = find_max(partial_max, x);
        int min = find_min(partial_min, x);
        printf("Matrix boundaries = [%d..%d]\n", min, max);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();

    return 0;
}

int find_max(int* vector, int vector_size)
{
    int max = vector[0];
    int i = 0;  
    for (i = 0; i < vector_size; i++)
    {
        if (vector[i] > max)
        {
            max = vector[i];
        }       
    }
    return max;
}

int find_min(int* vector, int vector_size)
{
    int min = vector[0];
    int i = 0;
    for (i = 0; i < vector_size; i++)
    {
        if (vector[i] < min)
        {
            min = vector[i];
        }
    }
    return min;
}

void fill_matrix_randomly(int matrix[n][m], int max_value, int x, int y)
{
    int i = 0;
    int j = 0; 
    srand(time(NULL));
    for (i = 0; i < x; i++)
    {
        for (j = 0; j < y; j++)
        {
            matrix[i][j] = rand() % max_value;
        }
    }   
}

void write_matrix(int matrix[n][m], int x, int y)
{
    int i = 0;
    int j = 0;
    for (i = 0; i < x; i++)
    {
        for (j = 0; j < y; j++)
        {
            printf("%4d", matrix[i][j]);            
        }
        printf("\n");
    }
}

void write_vector(int* vector, int vector_size)
{
    int i = 0;
    for (i = 0; i < vector_size; i++)
    {
        printf("vector[%d] = %d\n", i, vector[i]);
    }
}
