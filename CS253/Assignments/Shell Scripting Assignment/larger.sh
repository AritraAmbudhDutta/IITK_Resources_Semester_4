#!/bin/bash
# filepath: c:\Users\neeld\OneDrive - IIT Kanpur\IITK Courses\Sem 4\CS253\Assignments\Shell Scripting Assignment\larger.sh

# Function to display usage message
usage() {
    echo "Usage: Usage: $0 file1 file2 file1 file2 output_file"
    echo "This script compares two files line by line and outputs the length of common prefixes."
    exit 1
}

# Check if two arguments are provided
if [ $# -ne 2 ]; then
    usage
fi

# Check if both files exist
if [ ! -f "$1" ]; then
    echo "Error: File '$1' does not exist."
    usage
fi

if [ ! -f "$2" ]; then
    echo "Error: File '$2' does not exist."
    usage
fi

# Function to find common prefix length of two strings
find_common_prefix_length() {
    local str1="$1"
    local str2="$2"
    local i=0
    
    # Compare characters one by one until they don't match or one string ends
    while [ $i -lt ${#str1} ] && [ $i -lt ${#str2} ]; do
        if [ "${str1:$i:1}" != "${str2:$i:1}" ]; then
            break
        fi
        ((i++))
    done
    
    echo $i
}

# Process files line by line
while IFS= read -r line1 || [ -n "$line1" ]; do
    # Read corresponding line from second file
    IFS= read -r line2 <&3 || line2=""
    
    # Find common prefix length
    common_length=$(find_common_prefix_length "$line1" "$line2")
    
    # Output the result
    echo $common_length
    
done < "$1" 3< "$2"
