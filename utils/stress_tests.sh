#!/bin/bash

src_file="test.txt"

dst_file_1=out1.txt
dst_file_2=out2.txt


pwd=$pwd
main_default=$pwd../build/main_default.out
main_parallel=$pwd../build/main_parallel.out

process_range=20
cnt_records=10**7

if [ -z $1 ]; then
  echo run script with arg - process_range count - count records in array "(./stress_tests N count)"
  process_range=10
else
  process_range=$1
fi
if [ -z $2 ]; then
  cnt_records=10000000
else
  cnt_records=$2
fi

echo STRESS TEST WITH PROCESS RANGE [1:$process_range]
echo COUNT OF RECORDS $cnt_records

if [ ! -f $src_file ]; then
  echo data file generation
  python3 $(pwd)/generate.py $src_file $cnt_records
  if [ $? -ne 0 ]; then
    echo ERROR EXECUTE GENERATE DATAFILE
    exit 1
  else
    echo Done
  fi
else
  echo data file exist
fi

$main_default -f $(pwd)/$src_file -o 0  > $dst_file_1 && $main_default -f $(pwd)/$src_file -o 0  > $dst_file_2
echo program done with status $?

diff $dst_file_1 $dst_file_2
if [ $? -eq 0 ];
then
    echo programs worked equally
fi

echo Linear stress_test
    /usr/bin/time -f "Exit code: %X \nReal time: %E\nMax Memory Usage(KB): %M" $main_default -f $(pwd)/$src_file -o 0 > $dst_file_1
echo

for ((i=1; i < $process_range; i++))
do
    echo $i process
    /usr/bin/time -f "Exit code: %X \nReal time: %E\nMax Memory Usage(KB): %M" $main_parallel -f $(pwd)/$src_file -s $i -o 1 > $i
    echo
done

for (( i=1; i < $process_range; i++ ))
do
    rm $i
done

rm $dst_file_1 $dst_file_2 $src_file
exit 0

