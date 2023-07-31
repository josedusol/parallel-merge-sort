#!/bin/bash

# mpiexec -np 6 ../build/mergeSortPv1_mpi

# mpiexec -np 5 ../build/mergeSortPv1_mpi 10

mpiexec -np 4 ../build/mergeSortPv1_mpi 100000000 /media/josedu/OS/input/in_n=100000000.txt
