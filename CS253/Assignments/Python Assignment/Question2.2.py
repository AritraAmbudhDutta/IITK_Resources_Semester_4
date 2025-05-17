# This program calculates various statistical measures of temperature readings
# Statistics calculated include mean, median, standard deviation, and variance

import statistics

def analyze_temperatures(m, temperatures):
    """
    Calculates statistical measures for a list of temperature readings
    
    Args:
        m: Number of temperature readings
        temperatures: List of temperature readings
        
    Returns:
        Tuple containing (mean, median, standard deviation, variance)
    """
    mean = statistics.mean(temperatures)    # Calculate the mean (average)
    median = statistics.median(temperatures)  # Calculate the median (middle value)
    
    # Standard deviation and variance require at least 2 values
    if m <= 1:
        print("Not enough data to calculate standard deviation and variance.")
        stddev = None
        variance = None
    else:
        stddev = statistics.stdev(temperatures)    # Calculate standard deviation
        variance = statistics.variance(temperatures)  # Calculate variance
        
    return mean, median, stddev, variance

def main():
    """
    Main function that:
    1. Gets user input for number of temperature readings
    2. Collects temperature values
    3. Analyzes the data and prints statistics
    """
    try:
        m = int(input("Enter the number of temperature readings: "))
    except ValueError:
        print("Invalid input. Please enter a positive integer.")
        return
    if m <= 0:
        print("Number of readings must be positive.")
        return

    temperatures = []
    print("Enter the temperature readings below.")
    for i in range(m):
        try:
            temp = float(input(f"Enter temperature reading {i+1}: "))
        except ValueError:
            print("Invalid input. Please enter a number.")
            return
        temperatures.append(temp)
        
    mean, median, stddev, variance = analyze_temperatures(m, temperatures)
    
    # Display the results
    print(f"Mean of Temperatures: {mean}")
    print(f"Median of Temperatures: {median}")
    print(f"Standard Deviation of Temperatures: {stddev}")
    print(f"Variance of Temperatures: {variance}")

if __name__ == "__main__":
    main()