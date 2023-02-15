#!/bin/bash

# Check if there are 2 arguments
if [ $# -ne 2 ]; then
  echo "Error: script takes 2 arguments: input file and output folder"
  exit 1
fi

# Check if input file exists
if [ ! -f $1 ]; then
  echo "Error: input file $1 does not exist"
  exit 1
fi

# Check if output folder exists
if [ ! -d $2 ]; then
  echo "Error: output folder $2 does not exist"
  exit 1
fi

# Get file name without extension
filename=$(basename "$1")
filename="${filename%.*}"

# Get capitalized header guard
header_guard=$(echo $filename | awk '{print toupper($0)}')

# Clear the files
> "$2/$filename.h"
> "$2/$filename.cpp"

# Split input file into two outputs
echo "#ifndef $header_guard"_H > "$2/$filename.h"
echo "#define $header_guard"_H >> "$2/$filename.h"
echo >> "$2/$filename.h"

header=$(awk '/namespace/{exit} {print $0}' $1 | awk '{print $0}' ORS='\n')

# Copy everything above the namespace to both files
echo "$header" >> "$2/$filename.h"
echo "$header" >> "$2/$filename.cpp"
echo "#include \"$filename.h\"" >> "$2/$filename.cpp"
echo >> "$2/$filename.h"
echo >> "$2/$filename.cpp"

# Add the using namespace std; line to both files
echo "using namespace std;" >> "$2/$filename.h"
echo "using namespace std;" >> "$2/$filename.cpp"
# echo >> "$2/$filename.h"
echo >> "$2/$filename.cpp"

awk '/namespace/{flag=1;next}/::/{flag=2}flag{print >> ("'$2'/'$filename'." (flag==2?"cpp":"h"))}' $1

echo "#endif" >> "$2/$filename.h"

echo "File split into $filename.h and $filename.cpp in $2"
