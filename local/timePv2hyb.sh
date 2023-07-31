#!/bin/bash

# mpiexec -np 6 ../build/mergeSortPv2_mpi

# mpiexec -np 4 ../build/mergeSortPv2_mpi 30

OMP_NUM_THREADS=4 CUT_OFF_1=80 CUT_OFF_2=8000 mpiexec -np 2 ../build/mergeSortPv2_hyb 100000000 /media/josedu/OS/input/in_n=100000000.txt
