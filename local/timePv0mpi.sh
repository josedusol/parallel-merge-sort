#!/bin/bash

# mpiexec -np 6 ../build/mergeSortPv0_mpi

mpiexec -np 5 ../build/mergeSortPv0_mpi 10

# mpiexec -np 3 ../build/mergeSortPv0_mpi 100000000 /media/josedu/OS/input/in_n=100000000.txt
