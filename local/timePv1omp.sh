
#!/bin/bash

./genInput ./input $(echo {1000..9999..1000} {10000..99999..10000} {100000..999999..100000} {1000000..9999999..1000000} {10000000..99999999..10000000} {100000000..1000000000..100000000} | tr ' ' ,)

OMP_NUM_THREADS=4 CUT_OFF=80 ./runInput.sh mergeSortPv1_omp 10 timePv1omp-t4-c80.csv ./input

