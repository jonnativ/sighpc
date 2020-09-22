#!/bin/bash
export OMP_NUM_THREADS=40
gcc -fopenmp $1 
