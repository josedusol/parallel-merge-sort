#!/bin/bash
#SBATCH --job-name=speedupPv1omp
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=39
#SBATCH --mem=16384
#SBATCH --time=02:00:00
#SBATCH --partition=normal
#SBATCH --qos=normal
#SBATCH --mail-type=ALL
#SBATCH --mail-user=josedusolsona@gmail.com
#SBATCH --exclude=node31

cd ~/work/cuy

CUT_OFF=800 ../speedupOMP.sh ../build/mergeSortPv1_omp 5 speedupPv1omp-n10e9-c800.csv ../input/in_n=1000000000.txt {37..39}
