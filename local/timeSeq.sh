#!/bin/bash

../build/genInput /media/josedu/OS/input $(echo {1000..9999..1000} {10000..99999..10000} {100000..999999..100000} {1000000..9999999..1000000} {10000000..99999999..10000000} {100000000..1000000000..100000000} | tr ' ' ,)

../runInput.sh ../build/mergeSort 10 timeSeq.csv /media/josedu/OS/input

