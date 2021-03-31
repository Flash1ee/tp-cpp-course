#!/bin/bash

src_file="test.txt"

dst_file_1=out1.txt
dst_file_2=out2.txt
dst_file_3=out3.txt

pwd=$pwd
main=$pwd../cmake-build-debug/main.out
process_range=20

if [ -z $1 ]; then
  process_range=10
else
  process_range=$1
fi

echo Count of processes to test [1:$process_range]

if [ ! -f $src_file ]; then
  echo data file generation
  python3 $(pwd)/generate.py $src_file
  echo Done
else
  echo data file exist
fi


$main -f $(pwd)/$src_file -o 1 -s 1  > $dst_file_1
$main -f $(pwd)/$src_file -o 1 -s 2  > $dst_file_2
$main -f $(pwd)/$src_file -o 1 > $dst_file_3

echo program done with status $?

diff temp_out_1 temp_out_2

if [ $? -eq 0 ];
then
    echo program worked equally
fi

for ((i=1; i < $process_range; i++))
do
    echo $i process
    /usr/bin/time -f "Time %E" $main -f $(pwd)/$src_file -s $i -o 1 > $dst_file_$i
    echo
done

for ((i=1; i < $process_range; i++))
do
    rm $dst_file_$i
done

rm $src_file

