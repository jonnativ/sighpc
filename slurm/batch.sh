#!/bin/sh
#SBATCH --job-name=batch_example 
#SBATCH --partition=skynet
#SBATCH --ntasks=3
#SBATCH --cpus-per-task=2
#SBATCH --time=00:05:00
#SBATCH --output=batch_test.log

# Load modules/software here

# Preprocessing
srun -n 1 echo "preprocess phase"
srun sleep 15

# Processing
srun /bin/hostname
srun sleep 15

# Postprocessing
srun -n 1 echo "postprocess phase"
srun sleep 15
