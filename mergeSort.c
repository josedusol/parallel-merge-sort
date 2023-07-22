#include <string.h>
#include <time.h>

#include "utils.c"

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

void sort(int* A, int n, int* T) {
   mergeSort(A, 0, n-1, T); 
}

int main(int argc, char** argv) { 
   if (argc < 2)
     return -1;
   int   n        = atoi(argv[1]);  
   char* filePath = argc >= 3 ? argv[2] : NULL;  

   //--------- set up initial array
   int* A; 
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

   //--------- do timed sorting
   dbg_print("%s\n", "Sorting ...");
   double start, end, elapsed;
   int *T = malloc(n*sizeof(int));
   start = getWallTime();
   sort(A, n, T);
   end   = getWallTime();
   elapsed = end - start;

   //--------- show results
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

   free(A);   
   free(T); 
   return 0;   
}