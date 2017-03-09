#!/bin/bash

averaging()
{
   local res=$1
   local num=$2
   local sample=$3
   local param=$4
   local outf=$5
   local result=,inp=,rate=,str=,avg=
   local i=0
   local j=1
   local a=0
   local avg=0
   echo -n "Processing"
   while [ $i -le $num ]; do
      result=`cat results/${res}-${i}.sca |grep $param`
      inp=$result
      rate=`echo ${inp[0]} |cut -d' ' -f4`
      str="${str} ${rate}"
      if [ $j -eq $sample ];then #start new averaging
         avg=`echo ${str} | awk -v CONVFMT=%.17g 'BEGIN{sum=0;count=1} {for(count;count<=NF;count++){ sum = sum+$count;}} END{ print sum/NF;}'`
         echo ${avg} >> $outf
         str=
         avg=0
         j=0
      fi
      j=$((j+1))
 
      # normal sample count   
      if [ $((i % 10)) -eq 0 ];then
         echo -n "."
      fi
  
      i=$((i+1))
   done
}

res=$1

if [ "x${res}" == "x-h" ]; then
	echo "==========================================================================" 
	echo "= Parsing out violation Rate of multiple scenario files                  =" 				  
	echo "= Specify [arg1=ScenarioName] [arg2=repetitions] [arg3=sample_size]      ="
	echo "= or Specify [arg1=ScenarioName] [arg2=show] to print the output simfile ="
    echo "= Saves data to scenario.sim file under current dir                      ="	 
	echo "==========================================================================" 
	exit
fi 

iter=$2
sample=$3

if [ "x${res}" == "xremove" ]; then
   scen=$iter
   start=$sample
   end=$4
   while [ $start -le $end ]; do
      rm results/${scen}-${start}.sca
      start=$((start+1))
   done
   
   exit
fi

# results
num=$((iter-1))
fname=${res}.sim
if [ "x${iter}" == "xshow" ]; then
	if [ -f ${fname} ]; then
		cat ${fname}
	else
		echo "Simulation file ${res}.sim doesn't exist"
	fi
	exit
fi

param=allocatedBps

f=${fname}.${param}
touch $f
averaging $res $num $sample $param $f
echo "Completed running the simulation scenario $f"

