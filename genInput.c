#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#include "utils.c"


void createFile(char* filePath, int n) { 
   FILE* file = fopen(filePath, "w");     
   srand(time(NULL));
   for (int i = 1; i <= n; i++) {
      fprintf(file, "%d,", rand());
   }
   fflush(file);
   fclose(file);
}

int main(int argc, char** argv) { 
   if (argc < 3) {
     printf("--- Illegal number of parameters. \n");  
     return -1;
   }
   char* dir   = argv[1];  
   char* range = argv[2];  

   // create dir if doesn't exists
   struct stat st = {0};
   if (stat(dir, &st) == -1) {
      mkdir(dir, 0700);
   }

   // parse input sizes
   int c = 0;
   char *tok;
   tok = strtok(range,",");
   while (tok != NULL) {
      int n = atoi(tok);
      
      char* strArr[] = {dir, "/in_n=", tok, ".txt"};
      char* filePath = concat(strArr, 4);
      if (access(filePath, F_OK) != 0) {
         printf("--- Creating %s/in_n=%d.txt with random array of size %d ... \n", dir, n, n);     
         createFile(filePath, n);  
         c++;
      }
      free(filePath);

      tok = strtok(NULL, ",");  
   }

   printf("--- End. Created %d new input files in %s. \n", c, dir);  

   return 0;   
}