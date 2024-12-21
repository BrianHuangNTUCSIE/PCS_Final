#!/bin/bash

g++ main.cpp -o main
./main 100 0.1 17.24137931 > 100m_theoretical
./main 200 0.1 17.24137931 > 200m_theoretical
./main 500 0.1 17.24137931 > 500m_theoretical
./main 1000 0.1 17.24137931 > 1000m_theoretical

times=100000
g++ main2.cpp -o main2 -fopenmp
./main2 100 0.1 17.24137931 $times > 100m_experimental
./main2 200 0.1 17.24137931 $times > 200m_experimental
./main2 500 0.1 17.24137931 $times > 500m_experimental
./main2 1000 0.1 17.24137931 $times > 1000m_experimental

python3 plot.py
rm *_theoretical
rm *_experimental
rm main
rm main2