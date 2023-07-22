
#!/bin/bash

target=$1     # Executable file to run
reps=$2       # Num. of repetitions
output=$3     # Output file name
dir=$4        # Directory of input files
range=${@:5}  # (OPTIONAL) Size range for input files

if [ "$#" -lt 4 ]; then
  echo "--- Illegal number of parameters.";
  exit 1
fi
if [ ! -f "$target" ]; then
  echo "--- Target file $target not found.";
  exit 1
fi
if [ ! -d "$dir" ]; then
  echo "--- Directory of input files $dir not found.";
  exit 1
fi

START_TIME=$(date +%s)
echo "--- Starting executions of $target ...";   
for file in $dir/* ; do
  if [ -f "$file" ]; then
    n=$(echo $file | sed -n "s/^.*=\([0-9]\+\).txt/\1/p");
    if [ "$#" -gt 4 ] && [ $(echo $range | grep -ow "$n" | wc -w) -eq 0 ]; then
      continue   # input file is not in the specified range
    fi
    echo "--- Run for $reps times on $file ...";
    echo -n "$n, " >> ./"$output";
    for k in $(seq 1 $reps); do
      time=$(./"$target" "$n" "$file");
      if [ "$k" -eq "$reps" ]; then 
        echo "$time " >> ./"$output"
      else 
        echo -n "$time, " >> ./"$output"
      fi
    done  
  fi
done 
ELAPSED=$(($(date +%s) - START_TIME))
echo "--- End. Time elapsed: $(date -d@$ELAPSED -u +%H\h\ %M\m\ %S\s).";