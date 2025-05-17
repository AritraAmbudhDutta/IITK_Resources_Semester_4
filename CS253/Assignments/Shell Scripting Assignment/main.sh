#!/bin/bash
# filepath: c:\Users\neeld\OneDrive - IIT Kanpur\IITK Courses\Sem 4\CS253\Assignments\Shell Scripting Assignment\main.sh

# Function to log a timestamp with a message
log_timestamp() {
    echo "$(date '+%Y-%m-%d %H:%M:%S') - $1" >> "$log_file"
}

# Function to display usage message
usage() {
    echo "Usage: $0 input_file output_file log_timestamp_file"
    echo "This script processes a log file and generates statistics."
    exit 1
}

# Check if three arguments are provided
if [ $# -ne 3 ]; then
    usage
fi

input_file="$1"
output_file="$2"
log_file="$3"

# Check if input file exists
if [ ! -f "$input_file" ]; then
    log_timestamp "Input file not detected"
    echo "Error: Input file '$input_file' does not exist."
    usage
else
    log_timestamp "Input file exists"
fi

# Create or clear output file
> "$output_file"

# Extract unique IP addresses
echo "Unique IP addresses:" >> "$output_file"
awk -F, '{print $1}' "$input_file" | grep -v "^IP$" | sort -u >> "$output_file"
log_timestamp "Unique IP extraction completed"

# Find top 3 HTTP methods
echo -e "\nTop 3 HTTP methods:" >> "$output_file"
awk -F, '{print $3}' "$input_file" | grep -v "^HTTP_method$" | sort | uniq -c | sort -nr | head -3 | 
while read count method; do
    echo "$method: $count" >> "$output_file"
done
log_timestamp "Top 3 HTTP methods identified"

# Count requests per hour
echo -e "\nRequests per hour:" >> "$output_file"
for hour in {0..23}; do
    # Format hour with leading zero if needed
    formatted_hour=$(printf "%02d" $hour)
    
    # Count entries for this hour
    count=$(grep -c " $formatted_hour:" "$input_file")
    
    echo "Hour $hour: $count requests" >> "$output_file"
done
log_timestamp "Hourly request count completed"

# Completion message
log_timestamp "Script execution completed"
echo "Processing complete. Results saved to $output_file"