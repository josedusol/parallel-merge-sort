#!/bin/bash

OMP_NUM_THREADS=4 CUT_OFF_1=800 CUT_OFF_2=80000 ../speedupMPI.sh ../build/mergeSortPv2_hyb 5 speedupPv2hyb-n10e8.csv /media/josedu/OS/input/in_n=100000000.txt {1..4}
