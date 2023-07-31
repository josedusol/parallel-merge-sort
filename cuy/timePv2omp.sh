#!/bin/bash
#SBATCH --job-name=timePv2omp
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=18
#SBATCH --mem=12288
#SBATCH --time=03:00:00
#SBATCH --partition=normal
#SBATCH --qos=normal
#SBATCH --mail-type=ALL
#SBATCH --mail-user=josedusolsona@gmail.com

cd ~/work/cuy

OMP_NUM_THREADS=18 CUT_OFF_1=800 CUT_OFF_2=80000 ../runInput.sh ../build/mergeSortPv2_omp 10 timePv2omp-t18-c800_80000.csv ../input