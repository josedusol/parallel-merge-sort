#!/bin/bash
#SBATCH --job-name=timePv1omp
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=18
#SBATCH --mem=12288
#SBATCH --time=04:00:00
#SBATCH --partition=normal
#SBATCH --qos=normal
#SBATCH --mail-type=ALL
#SBATCH --mail-user=josedusolsona@gmail.com

cd ~/work/cuy

OMP_NUM_THREADS=18 CUT_OFF=800 ../runInput.sh ../build/mergeSortPv1_omp 10 timePv1omp-t18-c800.csv ../input