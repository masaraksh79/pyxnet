#!/bin/bash

cpus=$1

repet=500
sampl=50

./run.sh PyxisPureScada50 $cpus $repet $sampl
./run.sh PyxisPureScada60 $cpus $repet $sampl
./run.sh PyxisPureScada70 $cpus $repet $sampl
./run.sh PyxisPureScada80 $cpus $repet $sampl
./run.sh PyxisPureScada90 $cpus $repet $sampl
./run.sh PyxisPureScada100 $cpus $repet $sampl
./run.sh PyxisPureScada110 $cpus $repet $sampl
./run.sh PyxisPureScada120 $cpus $repet $sampl



