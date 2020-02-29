#!/usr/bin/env bash

make
gcc -o datasingle datasingle.c

echo ------------------------------
echo **Single Thread Small Data Set**

./datasingle smalldata.csv 6
echo ------------------------------
./datasingle smalldata.csv 10
echo ------------------------------
./datasingle smalldata.csv 14
echo ------------------------------
./datasingle smalldata.csv 
echo ------------------------------


echo ------------------------------
echo **Multi Thread Small Data Set**

./dataPar smalldata.csv 6
echo ------------------------------
./dataPar smalldata.csv 10
echo ------------------------------
./dataPar smalldata.csv 14
echo ------------------------------
./dataPar smalldata.csv
echo ------------------------------ 

echo ------------------------------
echo **Single Thread Large Data Set 10 Years**

./datasingle stremflow_time_series.csv

echo ------------------------------
echo **Single Thread Large Data Set Year 2002**

./datasingle 2002data.csv

echo ------------------------------
echo **Multi Thread Large Data Set 10 Years**

./dataPar stremflow_time_series.csv


echo ------------------------------
echo **Multi Thread Large Data Set Year 2002**

./dataPar 2002data.csv


make clean
rm datasingle