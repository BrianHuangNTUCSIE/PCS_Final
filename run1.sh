#!/bin/bash

g++ main.cpp -o main
./main 100 0.1 17.25 > data1.txt
./main 200 0.1 17.25 > data2.txt
./main 500 0.1 17.25 > data3.txt
./main 1000 0.1 17.25 > data4.txt

python3 plot.py