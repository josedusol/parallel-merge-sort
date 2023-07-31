#include <math.h>
#include <mpi.h>

#include "utils.c"

static int WORLD_RANK;
static int WORLD_SIZE;
static int WORLD_MAX_RANK;

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

// return the top level of the process tree in which the process participates
int topmostLevel(int rank) {
    int level = 0;
    while (pow(2, level) <= rank)
        level++;
    return level;
}

// MPI merge sort
void sortParallel(int* A, int n, int* T, int level, MPI_Comm comm) {
    int helper_rank = WORLD_RANK + pow(2, level);
    if (helper_rank > WORLD_MAX_RANK) {   // if no more processes available 
        dbg_print("No more processes available, on rank %d\n", WORLD_RANK);
        mergeSort(A, 0, n-1, T);
    } else {
        dbg_print("Process %d has helper %d\n", WORLD_RANK, helper_rank);
        MPI_Request request;
        MPI_Status status;
        const int m = n/2;
        //--------- Send second half, asynchronous
        MPI_Isend(A+m, n-m, MPI_INT, helper_rank, 0, comm, &request);
        //--------- Sort first half
        sortParallel(A, m, T, level+1, comm);       
        //--------- Receive second half sorted
        MPI_Request_free(&request);
        MPI_Recv(A+m, n-m, MPI_INT, helper_rank, 0, comm, &status);
        //--------- Merge the two sorted sub-arrays
        merge(A, 0, m-1, n-1, T);
    }
}

// Helper process code
void sortHelper(MPI_Comm comm) {
    int level = topmostLevel(WORLD_RANK);
    dbg_print("Helper process %d on level %d\n", WORLD_RANK, level);
    //--------- Probe for a message and determine its size and sender
    MPI_Status status;
    int size;
    MPI_Probe(MPI_ANY_SOURCE, 0, comm, &status);
    MPI_Get_count(&status, MPI_INT, &size);
    int parent_rank = status.MPI_SOURCE;  
    //--------- Receive sub-array and sort
    int* chunk = malloc(size*sizeof(int));
    int* tempArray = malloc(size*sizeof(int));
    MPI_Recv(chunk, size, MPI_INT, parent_rank, 0, comm, &status);
    sortParallel(chunk, size, tempArray, level, comm);
    //--------- Send sorted array to parent process
    MPI_Send(chunk, size, MPI_INT, parent_rank, 0, comm);
    free(chunk);   
    free(tempArray);  
}

void sort(int* A, int n, int* T) {
    if (WORLD_RANK == 0)
        sortParallel(A, n, T, 0, MPI_COMM_WORLD);
    else
        sortHelper(MPI_COMM_WORLD);
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
    WORLD_MAX_RANK = WORLD_SIZE - 1;

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
    int* T;
    if (WORLD_RANK == 0) {
        dbg_print("%s\n", "Sorting ...");
        T = malloc(n*sizeof(int)); 
    }
    double start, end, elapsed;
    MPI_Barrier(MPI_COMM_WORLD); 
    start = MPI_Wtime();
    sort(A, n, T);
    MPI_Barrier(MPI_COMM_WORLD);
    end = MPI_Wtime();
    elapsed = end - start;

    //--------- Show results at root
    if (WORLD_RANK == 0) {
        if (DBG_TEST) {
            if (isSorted(A, n))
                printf("Result is OK:\n");   
            else 
                printf("Result is BAD:\n");   
        }   
        if (n < 100) {
            dbg_printArray(A, n);
            dbg_print("%s\n", "");
        }
        dbg_print("%s\n", "Elapsed time:");
        printf("%g\n", elapsed);
    }

    //--------- Clean up and Finalize MPI
    if (WORLD_RANK == 0) {
        free(A);   
        free(T);  
    }
    MPI_Finalize();  
    return 0;   
}