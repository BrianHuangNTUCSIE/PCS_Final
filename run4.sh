#!/bin/bash
times=100000
g++ main2.cpp -o main2 -fopenmp
./main2 100 0.1 52 $times > 100m
./main2 200 0.1 52 $times > 200m
./main2 500 0.1 52 $times > 500m
./main2 1000 0.1 52 $times > 1000m

python3 plot.py