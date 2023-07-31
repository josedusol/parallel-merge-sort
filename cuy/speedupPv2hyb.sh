#!/bin/bash
#SBATCH --job-name=speedupPv2hyb
#SBATCH --ntasks=16
#SBATCH --ntasks-per-node=8
#SBATCH --cpus-per-task=4
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

OMP_NUM_THREADS=4 CUT_OFF_1=800 CUT_OFF_2=80000 ../speedupMPI.sh ../build/mergeSortPv2_hyb 5 speedupPv2hyb-n10e9-c800_80000.csv ../input/in_n=1000000000.txt {1..16}
