#include <string.h>
#include <time.h>

#include "utils.c"

void insertionSort(int* A, int n) {
   for (int i = 1; i < n; i++) {
      int k = A[i];
      int j = i - 1;
      while (j >= 0 && A[j] > k) {
         A[j + 1] = A[j];
         j = j - 1;
      }
      A[j + 1] = k;
   }
}

void merge(int* A, int l, int m, int r, int* T) {
   int n = r-l+1, i = l, j = m+1, k = 0;

   while (i <= m && j <= r)    
      if (A[i] <= A[j])
         T[k++] = A[i++];
      else
         T[k++] = A[j++];

   while (i <= m)    
      T[k++] = A[i++];
   while (j <= r)    
      T[k++] = A[j++];   

   for (k = 0; k < n; k++)
      A[l+k] = T[k];
}

int* readOrCreate(int n, int n2, char* filePath) {
   int* A;
   if (filePath != NULL) {
      dbg_print("Reading sorted array of length %d from %s ...\n", n, filePath);   
      A = readArrayFromfile(filePath, n);
      if (A == NULL) {
         dbg_print("%s\n", "File not found, aborting ...");   
         exit(1);
      }
      if (!isSorted(A, n)) {
         printf("Array is not sorted, aborting ...\n");   
         exit(1);
      }
   } else { 
      dbg_print("Creating random sorted array of length %d ...\n", n);   
      A = malloc(n*sizeof(int));
      for (int i = 0; i < n; i++)		
         A[i] = rand() % (n+n2);
      insertionSort(A,n);   
   }
   return A;
}

int main(int argc, char** argv) { 
   if (argc < 3)
     return -1;
   int   n1        = atoi(argv[1]);  
   int   n2        = atoi(argv[2]);  
   char* filePath1 = argc >= 3 ? argv[3] : NULL;  
   char* filePath2 = argc >= 4 ? argv[4] : NULL;  

   //--------- set up initial arrays
   srand(time(NULL));
   int* A = readOrCreate(n1, n2, filePath1);
   int* B = readOrCreate(n2, n1, filePath2);
   if (n1+n2 < 100) {
     dbg_print("%s\n", "First array: ");   
     dbg_printArray(A, n1);
     dbg_print("%s\n", ""); 
     dbg_print("%s\n", "Second array: ");   
     dbg_printArray(B, n2);
     dbg_print("%s\n", ""); 
   }

   //--------- do timed merge
   dbg_print("%s\n", "Merging ...");
   double start, end, elapsed;
   int* C = malloc((n1+n1)*sizeof(int));
   int* T = malloc((n1+n1)*sizeof(int));
   int k = 0;
   for (int i = 0; i < n1; i++,k++)
      T[k] = A[i];
   for (int i = 0; i < n2; i++,k++)
      T[k] = B[i];   
   start = getWallTime();
   merge(T, 0, n1-1, n1+n2-1, C);
   end   = getWallTime();
   elapsed = end - start;

   //--------- show results
   if (DBG_TEST) {
      if (isSorted(C, n1+n2))
         printf("Result is OK:\n");   
      else 
         printf("Result is BAD:\n");   
   }
   if (n1+n2 < 100) { 
      dbg_printArray(C, n1+n2);
      dbg_print("%s\n", "");
   }
   dbg_print("%s\n", "Elapsed time:");
   printf("%g\n", elapsed);

   free(A);   
   free(B);
   free(C);      
   return 0;   
}