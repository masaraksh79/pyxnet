#!/bin/bash

cpus=$1
stage=$2

if [ "$stage" == "1" ]; then
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
elif [ "$stage" == "2" ]; then
	repet=500
	sampl=50
	./run.sh PyxisTraffic25M0 $cpus $repet $sampl
	./run.sh PyxisTraffic25M1 $cpus $repet $sampl
	./run.sh PyxisTraffic25M2 $cpus $repet $sampl
	./run.sh PyxisTraffic25M3 $cpus $repet $sampl
	./run.sh PyxisTraffic30M0 $cpus $repet $sampl
	./run.sh PyxisTraffic30M1 $cpus $repet $sampl
	./run.sh PyxisTraffic30M2 $cpus $repet $sampl
	./run.sh PyxisTraffic30M3 $cpus $repet $sampl
	./run.sh PyxisTraffic35M0 $cpus $repet $sampl
	./run.sh PyxisTraffic35M1 $cpus $repet $sampl
	./run.sh PyxisTraffic35M2 $cpus $repet $sampl
	./run.sh PyxisTraffic35M3 $cpus $repet $sampl
	./run.sh PyxisTraffic40M0 $cpus $repet $sampl
	./run.sh PyxisTraffic40M1 $cpus $repet $sampl
	./run.sh PyxisTraffic40M2 $cpus $repet $sampl
	./run.sh PyxisTraffic40M3 $cpus $repet $sampl
	./run.sh PyxisTraffic45M0 $cpus $repet $sampl
	./run.sh PyxisTraffic45M1 $cpus $repet $sampl
	./run.sh PyxisTraffic45M2 $cpus $repet $sampl
	./run.sh PyxisTraffic45M3 $cpus $repet $sampl
	./run.sh PyxisTraffic50M0 $cpus $repet $sampl
	./run.sh PyxisTraffic50M1 $cpus $repet $sampl
	./run.sh PyxisTraffic50M2 $cpus $repet $sampl
	./run.sh PyxisTraffic50M3 $cpus $repet $sampl
	./run.sh PyxisTraffic55M0 $cpus $repet $sampl
	./run.sh PyxisTraffic55M1 $cpus $repet $sampl
	./run.sh PyxisTraffic55M2 $cpus $repet $sampl
	./run.sh PyxisTraffic55M3 $cpus $repet $sampl
else
	echo "Terminating. Unrecognised step..."
fi

