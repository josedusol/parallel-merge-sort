
#!/bin/bash

# Script to generate files filled with random arrays
# Important: For best performance, is much better to use the C version

dir=$1         # Directory
range=${@:2}   # Size range for input files

if [ "$#" -lt 2 ]; then
  echo "--- Illegal number of parameters.";
  exit 1
fi

mkdir -p $dir;

c=0
for n in $range; do
  if [ ! -f "$dir/in_n=$n.txt" ]; then
    echo "--- Creating $dir/in_n=$n.txt with random array of size $n ..." 
    for i in $(seq 1 $n); do
      echo -n "$RANDOM, " 
    done > "$dir/in_n=$n.txt";
    c=$((c+1))
  fi
done

echo "--- End. Created $c new input files in $dir." 