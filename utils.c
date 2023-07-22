#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#ifdef DEBUG
  #define DBG_TEST 1
#else
  #define DBG_TEST 0
#endif
#define dbg_print(fmt, ...) \
   do { if (DBG_TEST) printf(fmt, __VA_ARGS__); } while (0)
#define dbg_printArray(arr, len) \
   if (DBG_TEST) printArray(arr, len)

void printArray(int* arr, int len) {
    for (int i = 0; i < len; i++) 
        printf("%d ", arr[i]);
}

int* readArrayFromfile(const char* filePath, int n) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL)      
        return NULL;       

    int *arr   = malloc(n*sizeof(int));
    for (int i = 0; i < n; i++)
        fscanf(file, "%d,", &arr[i]);

    fclose(file); 
    return arr;   
}

char* concat(char** strs, int n) {
    int len = 0;
    for (int i = 0; i < n; ++i)
      len += strlen(strs[i]);

    char *out = (char*) malloc(len + 1);

    char *dest = out;
    for (int i = 0; i < n; ++i) {
        char *s = strs[i];
        while (*s)
            *dest++ = *s++;
    }
    *dest = '\0';

    return out;
}

bool isSorted(int* arr, int len) {
    int prev = arr[0];
    bool ret = true;
    for (int i=1; i < len; i++) {
        if (arr[i] < prev) {
            ret = false;
            break;
        }
        prev = arr[i];
    }
    return ret;
}

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int max(int a, int b) {
    if (a < b) 
      return b;
    else
      return a;
}

void doStatistics(double* times, int n, double* min, double* max, double* avg) {
    double sum, min_, max_;
    sum  = times[0];
    min_ = times[0];
    max_ = times[0];
    for (int i = 1; i < n; i++) {
        sum = sum + times[i];
        if (times[i] < min_)
            min_ = times[i];
        if (times[i] > max_)
            max_ = times[i];
    }
    *min = min_;
    *max = max_;
    *avg = sum / n;
}

double getWallTime() {
    struct timeval time;
    if (gettimeofday(&time,NULL))
        return 0;
    return (double)time.tv_sec + (double)time.tv_usec * .000001;
}

double getCPUTime() {
    return (double)clock() / CLOCKS_PER_SEC;
}
