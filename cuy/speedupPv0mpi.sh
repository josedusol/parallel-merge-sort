#!/bin/bash
#SBATCH --job-name=speedupPv0mpi
#SBATCH --ntasks=16
#SBATCH --mem=16384
#SBATCH --time=06:00:00
#SBATCH --partition=normal
#SBATCH --qos=normal
#SBATCH --mail-type=ALL
#SBATCH --mail-user=josedusolsona@gmail.com
#SBATCH --exclude=node31

source /etc/profile.d/modules.sh
#module load mpi/mpich-3.2-x86_64
module load mpi/openmpi-x86_64

cd ~/work/cuy

../speedupMPI.sh ../build/mergeSortPv0_mpi 5 speedupPv0mpi-n10e9.csv ../input/in_n=1000000000.txt {2,4,5,8,10,16}
