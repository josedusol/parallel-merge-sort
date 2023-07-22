
#!/bin/bash

###############################################################################
# e.g.
# $ CUT_OFF=80 ./speedup.sh mergeSortPv1_omp 10 speedupPv1omp-n10e9-c80.csv ./input/in_n=1000000000.txt {1..36}
# $ CUT_OFF_1=80 CUT_OFF_2=8000 ./speedup.sh mergeSortPv2_omp 10 speedupPv2omp-n10e9-c80_8000.csv ./input/in_n=1000000000.txt {1..36}
###############################################################################

target=$1       # Executable file to run
reps=$2         # Num. of repetitions
output=$3       # Output file name
file=$4         # Path to input file
threads=${@:5}  # Range of threads

if [ "$#" -lt 5 ]; then
  echo "--- Illegal number of parameters.";
  exit 1
fi
if [ ! -f "$target" ]; then
  echo "--- Target file $target not found.";
  exit 1
fi
if [ ! -f "$file" ]; then
  echo "--- Input file $file not found.";
  exit 1
fi

START_TIME=$(date +%s)
echo "--- Starting executions of $target on $file ...";   
for t in $threads; do
  n=$(echo $file | sed -n "s/^.*=\([0-9]\+\).txt/\1/p");
  echo "--- Run using $t threads for $reps times ...";
  echo -n "$t, " >> ./"$output";
  for k in $(seq 1 $reps); do
    time=$(OMP_NUM_THREADS="$t" ./"$target" "$n" "$file");
    if [ "$k" -eq "$reps" ]; then 
      echo "$time " >> ./"$output"
    else 
      echo -n "$time, " >> ./"$output"
    fi
  done  
done 
ELAPSED=$(($(date +%s) - START_TIME))
echo "--- End. Time elapsed: $(date -d@$ELAPSED -u +%H\h\ %M\m\ %S\s).";