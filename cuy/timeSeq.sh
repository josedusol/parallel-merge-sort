#!/bin/bash
#SBATCH --job-name=timeSeq
#SBATCH --ntasks=1
#SBATCH --mem=12288
#SBATCH --time=12:00:00
#SBATCH --partition=normal
#SBATCH --qos=normal
#SBATCH --mail-type=ALL
#SBATCH --mail-user=josedusolsona@gmail.com

cd ~/work/cuy

../runInput.sh ../build/mergeSort 10 timeSeq.csv ../input
