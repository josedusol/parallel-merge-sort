#!/bin/bash
#SBATCH --job-name=speedupPv1mpi
#SBATCH --ntasks=16
#SBATCH --mem=16384
#SBATCH --time=10:00:00
#SBATCH --partition=normal
#SBATCH --qos=normal
#SBATCH --mail-type=ALL
#SBATCH --mail-user=josedusolsona@gmail.com
#SBATCH --exclude=node31

source /etc/profile.d/modules.sh
#module load mpi/mpich-3.2-x86_64
module load mpi/openmpi-x86_64

cd ~/work/cuy

../speedupMPI.sh ../build/mergeSortPv1_mpi 5 speedupPv1mpi-n10e9.csv ../input/in_n=1000000000.txt {1..16}
