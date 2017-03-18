#!/bin/bash

project=pyxnet

# Args
# app [scenario_name] [cpus] [repetitions] [samplesize]
res=$1
if [ x"$res" == "x-h" ]; then
	echo "app [scenario_name] [cpus] [repetitions] [samplesize]"
	exit
fi

core=$2
sim=./out/gcc-debug/$project
opp=./../../bin/opp_runall
$sim -a
export NEDPATH=/home/matusovsky/omnetpp-5.0/samples/$project;
repmin=0
repmax=$(($3-1))

ini=omnetpp.ini

$opp -j$core -- $sim -r $repmin..$repmax -u Cmdenv -c $res -f $ini --debug-on-errors=auto

# parse the results using sample size arg
./parse.sh $res $3 $4
# remove result files
./parse.sh remove $res $repmin $repmax
