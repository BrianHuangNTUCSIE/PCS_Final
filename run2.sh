#!/bin/bash

g++ main.cpp -o main
./main 100 0.1 52 > 100m
./main 200 0.1 52 > 200m
./main 500 0.1 52 > 500m
./main 1000 0.1 52 > 1000m

python3 plot.py