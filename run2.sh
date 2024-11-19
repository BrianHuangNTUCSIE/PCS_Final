#!/bin/bash

g++ main.cpp -o main
./main 100 0.1 52 > data1.txt
./main 200 0.1 52 > data2.txt
./main 500 0.1 52 > data3.txt
./main 1000 0.1 52 > data4.txt

python3 plot.py