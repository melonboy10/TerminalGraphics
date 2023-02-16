#!/bin/bash

# Check if there are 3 arguments
if [ $# -ne 3 ]; then
  echo "Error: script takes 3 arguments: input file, output folder, and include file"
  exit 1
fi

# Check if input file exists
if [ ! -f $1 ]; then
  echo "Error: input file $1 does not exist"
  exit 1
fi

# Get path without src/
filepath=$(dirname "$1")
filepath="${filepath#src/}"
filepath="${filepath#src}"

# Make folder if it doesn't exist
mkdir -p "$2/$filepath"

# Get file name without extension
filename=$(basename "$1")
filename="${filename%.*}"

# Get capitalized header guard
header_guard=$(echo $filename | awk '{print toupper($0)}')

# Clear the files
> "$2/$filepath/$filename.h"
> "$2/$filepath/$filename.cpp"

# Split input file into two outputs
echo "#ifndef $header_guard"_H > "$2/$filepath/$filename.h"
echo "#define $header_guard"_H >> "$2/$filepath/$filename.h"
echo >> "$2/$filepath/$filename.h"

# Get the header
header=$(awk '/namespace/{exit} {print $0}' $1 | awk '{print $0}' ORS='\n')

# Add the header to both files
echo "$header" >> "$2/$filepath/$filename.h"
echo "$header" >> "$2/$filepath/$filename.cpp"
echo "#include \"$filename.h\"" >> "$2/$filepath/$filename.cpp"

# Add the header to the include file but only the lines that don't have " in them
header=$(echo "$header" | awk '!/"/')
echo "$header" >> "$3"

# Add blank line to both files
echo >> "$2/$filepath/$filename.h"
echo >> "$2/$filepath/$filename.cpp"

# Add the using namespace std; line to both files
echo "using namespace std;" >> "$2/$filepath/$filename.h"
echo "using namespace std;" >> "$2/$filepath/$filename.cpp"
# echo >> "$2/$filename.h"
echo >> "$2/$filepath/$filename.cpp"

# Add the namespace to the header
awk '/namespace/{flag=1;next}/::/{flag=2}flag==1{print >> "'"$3"'"}' $1
awk '/namespace/{flag=1;next}/::/{flag=2}flag{print >> ("'$2'/'$filepath'/'$filename'." (flag==2?"cpp":"h"))}' $1

echo "#endif" >> "$2/$filepath/$filename.h"

echo "File split into $filename.h and $filename.cpp in $2"
