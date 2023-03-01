#!/bin/bash

# Check for both arguments <path> <outputFile>
if [ $# -ne 2 ]; then
  echo "Usage: $0 <path> <outputFile>"
  exit 1
fi

# Clear the output file or create it if it doesn't exist
echo "Clearing output file: $2"
mkdir -p $(dirname $2)
echo "" > $2

# Find all the .cpp and .h files in the directory and its subdirectories
files=$(find $1 -type f \( -name "*.cpp" -o -name "*.h" \))

# Create an array to hold the unique import statements
unique_imports=()

# Loop through the files and extract the import statements
for file in $files; do
  echo "Processing file: $file"
  while read line; do
    if [[ $line == \#include* ]]; then
      # Extract the file name from the import statement and remove the "#include " prefix
      import=$(echo $line | cut -d'"' -f2 | sed 's/^#include\s*//')
      # Add the import statement to the array if it hasn't been added before
      if ! [[ " ${unique_imports[@]} " =~ " $import " ]]; then
        unique_imports+=("$import")
      fi
    fi
  done < $file
done

# Loop through the unique import statements and copy the contents of the import files if they exist in the current directory
for import in "${unique_imports[@]}"; do
  if [ -e "$1/$import" ]; then
    echo "Copying contents of $import to $2"
    # Create the output file if it doesn't exist
    touch $2
    # Read the contents of the import file
    while read line; do
      # Remove any lines that use an import from the unique_imports list
      if ! [[ "$line" == "#include \""* ]]; then
        echo "$line" >> $2
      fi
    done < "$1/$import"
    # Add a new line at the end of the file
    echo "" >> $2
  fi
done

# End of script
