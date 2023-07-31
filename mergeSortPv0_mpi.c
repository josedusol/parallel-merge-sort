
#include <mpi.h>

#include "utils.c"

static int WORLD_RANK;
static int WORLD_SIZE;

void merge(int* A, int l, int m, int r, int* T) {
    int i = l, j = m+1, k = l;

    while (i <= m && j <= r)    
        if (A[i] <= A[j])
            T[k++] = A[i++];
        else
            T[k++] = A[j++];

    while (i <= m)    
        T[k++] = A[i++];
    while (j <= r)    
        T[k++] = A[j++];   
    
    for (k = l; k <= r; k++)
        A[k] = T[k];
}

void mergeSort(int* A, int l, int r, int* T) {
    if (l < r) {
        int m = l+(r-l)/2;  // = (l+r)/2, but without overflow 
        mergeSort(A, l, m, T);
        mergeSort(A, m+1, r, T);
        merge(A, l, m, r, T);
    }
}

void sort(int* A, int n, int* B) {
	//--------- Scatter array in equal-sized chunks
	int chunkSize = n/WORLD_SIZE;
	int* chunk = malloc(chunkSize*sizeof(int));
    MPI_Scatter(A, chunkSize, MPI_INT, chunk, chunkSize, MPI_INT, 0, MPI_COMM_WORLD);
	
	//--------- MergeSort on each process
    int* T1 = malloc(chunkSize*sizeof(int));
	mergeSort(chunk, 0, chunkSize-1, T1);
	
	//--------- Gather sorted chunks
	MPI_Gather(chunk, chunkSize, MPI_INT, B, chunkSize, MPI_INT, 0, MPI_COMM_WORLD);
	
	//--------- Final MergeSort at root
	if (WORLD_RANK == 0) {
        int* T2 = malloc(n*sizeof(int));
		mergeSort(B, 0, n-1, T2);
        free(T2);  
    }		

    free(T1);
    free(chunk);    
}

int main(int argc, char** argv) { 
    if (argc < 2)
        return -1;
    int   n        = atoi(argv[1]);  
    char* filePath = argc >= 3 ? argv[2] : NULL;   

    //--------- Initialize MPI
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &WORLD_RANK);
	MPI_Comm_size(MPI_COMM_WORLD, &WORLD_SIZE);

    //--------- Set up initial array at root
    int* A; 
    if (WORLD_RANK == 0) {
        if (filePath != NULL) {
            dbg_print("Reading array of length %d from %s ...\n", n, filePath);   
            A = readArrayFromfile(filePath, n);
            if (A == NULL) {
                dbg_print("%s\n", "File not found, aborting ...");   
                exit(1);
            }
        } else { 
            dbg_print("Creating random array of length %d ...\n", n);   
            A = malloc(n*sizeof(int));
            srand(time(NULL));
            for (int i = 0; i < n; i++)		
                A[i] = rand() % n;
        }
        if (n < 100) {
            dbg_print("%s\n", "Initial array: ");   
            dbg_printArray(A, n);
            dbg_print("%s\n", ""); 
        }
    }

    //--------- Do timed sorting
    int* B;
    if (WORLD_RANK == 0) {
        dbg_print("%s\n", "Sorting ...");
        B = malloc(n*sizeof(int)); 
    }
    double start, end, elapsed;
    MPI_Barrier(MPI_COMM_WORLD); 
    start = MPI_Wtime();
    sort(A, n, B);
    MPI_Barrier(MPI_COMM_WORLD);
    end = MPI_Wtime();
    elapsed = end - start;

    //--------- Show results at root
    if (WORLD_RANK == 0) {
        if (DBG_TEST) {
            if (isSorted(B, n))
                printf("Result is OK:\n");   
            else 
                printf("Result is BAD:\n");   
        }   
        if (n < 100) {
            dbg_printArray(B, n);
            dbg_print("%s\n", "");
        }
        dbg_print("%s\n", "Elapsed time:");
        printf("%g\n", elapsed);
    }

    //--------- Clean up and Finalize MPI
    if (WORLD_RANK == 0) {
        free(A);   
        free(B);  
    }
    MPI_Finalize();  
    return 0;   
}