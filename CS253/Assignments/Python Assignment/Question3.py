# This program simulates and visualizes climate/environmental data
# It generates random data based on mathematical functions and provides
# various graphical representations (scatter plots, histograms, box plots, line plots)

import numpy as np
import matplotlib
import matplotlib.pyplot as plt
matplotlib.use('TkAgg')  # Set backend for matplotlib
import random
import math

def set_random_seed(seed=42):
    """
    Set random seed for reproducibility in numpy and random modules
    
    Args:
        seed: Integer value to initialize the random number generator
    """
    np.random.seed(seed)
    random.seed(seed)

def generate_dataset(N, x_min, x_max):
    """
    Generate N random points for X and compute Y using a randomly generated function.
    
    Args:
        N: Number of data points
        x_min: Minimum value for X
        x_max: Maximum value for X
        
    Returns:
        X: Array of X values
        Y: Array of Y values
        func_str: String representation of the generated function
    """
    # Generate X values uniformly distributed in the given range
    X = np.random.uniform(x_min, x_max, N)
    
    # List of possible functions to use in generating Y values
    functions = [
        (np.sin, "sin"),
        (np.cos, "cos"),
        (np.tan, "tan"),
        (lambda x: np.log(np.where(x > 0, x, 0.001)), "log"),  # Handle non-positive values
        (lambda x: x**2, "square"),
        (lambda x: x**3, "cube")
    ]
    
    # Randomly generate coefficients for the combined function
    A = np.random.uniform(-5, 5)
    B = np.random.uniform(-2, 2)
    C = np.random.uniform(-5, 5)
    D = np.random.uniform(-2, 2)
    E = np.random.uniform(-5, 5)
    F = np.random.uniform(-2, 2)
    
    # Randomly choose three functions from the list
    f1_idx = random.randint(0, len(functions) - 1)
    f2_idx = random.randint(0, len(functions) - 1)
    f3_idx = random.randint(0, len(functions) - 1)
    
    f1, f1_name = functions[f1_idx]
    f2, f2_name = functions[f2_idx]
    f3, f3_name = functions[f3_idx]
    
    # Calculate Y values using a combination of the selected functions
    # Y = A*f1(B*X) + C*f2(D*X) + E*f3(F*X)
    Y = A * f1(B * X) + C * f2(D * X) + E * f3(F * X)
    
    # Create function string for display
    func_str = f"Y = {A:.2f}*{f1_name}({B:.2f}*X) + {C:.2f}*{f2_name}({D:.2f}*X) + {E:.2f}*{f3_name}({F:.2f}*X)"
    
    return X, Y, func_str

def plot_scatter(X, Y, func_str):
    """
    Create a scatter plot of X vs Y
    
    Args:
        X: Array of X values
        Y: Array of Y values
        func_str: String representation of the function used to generate Y
    """
    plt.figure(figsize=(10, 6))
    plt.scatter(X, Y, alpha=0.7, color='blue')
    plt.title(f'Scatter Plot of Environmental Data\n{func_str}')
    plt.xlabel('X Variable')
    plt.ylabel('Y Variable')
    plt.grid(True, linestyle='--', alpha=0.7)
    plt.show()

def plot_histogram(X):
    """
    Plot a histogram of X values
    
    Args:
        X: Array of X values
    """
    plt.figure(figsize=(10, 6))
    # Calculate appropriate number of bins using Sturges' rule
    bins = int(1 + 3.322 * np.log10(len(X)))
    plt.hist(X, bins=bins, color='green', alpha=0.7, edgecolor='black')
    plt.title('Histogram of X Variable')
    plt.xlabel('X Value')
    plt.ylabel('Frequency')
    plt.grid(True, linestyle='--', alpha=0.7)
    plt.show()

def plot_box(Y):
    """
    Generate a box plot for Y values to identify outliers
    
    Args:
        Y: Array of Y values
    """
    plt.figure(figsize=(10, 6))
    plt.boxplot(Y, vert=False, patch_artist=True, boxprops=dict(facecolor='lightblue'))
    plt.title('Box Plot of Y Variable (Detecting Outliers)')
    plt.xlabel('Y Value')
    plt.grid(True, linestyle='--', alpha=0.7)
    plt.show()

def plot_line(X, Y):
    """
    Create a line plot of sorted X against corresponding Y
    
    Args:
        X: Array of X values
        Y: Array of Y values
    """
    # Sort X and Y together based on X values
    sorted_indices = np.argsort(X)
    X_sorted = X[sorted_indices]
    Y_sorted = Y[sorted_indices]
    
    plt.figure(figsize=(10, 6))
    plt.plot(X_sorted, Y_sorted, color='red', linewidth=2)
    plt.title('Line Plot of Sorted X vs Y')
    plt.xlabel('X Variable (Sorted)')
    plt.ylabel('Y Variable')
    plt.grid(True, linestyle='--', alpha=0.7)
    plt.show()

def analyze_climate_data():
    """
    Main function for climate data analysis:
    1. Get user parameters for data generation
    2. Generate synthetic climate data
    3. Create and display visualizations
    """
    print("\n=== Climate Data Analysis Tool ===\n")
    
    # Get user input for random seed
    while True:
        try:
            custom_seed = input("Enter random seed for reproducibility (press Enter for default=42): ")
            if custom_seed.strip():
                seed = int(custom_seed)
            else:
                seed = 42
            set_random_seed(seed)
            print(f"Random seed set to: {seed} for reproducibility")
            break
        except ValueError:
            print("Invalid seed. Please enter a valid integer.")
    
    # Get user input for data generation parameters
    while True:
        try:
            N = int(input("Enter the number of data points (N): "))
            if N <= 0:
                print("Number of data points must be positive.")
                continue
            
            x_min = float(input("Enter minimum value for X: "))
            x_max = float(input("Enter maximum value for X: "))
            
            if x_max <= x_min:
                print("Maximum X must be greater than minimum X.")
                continue
            
            break
        except ValueError:
            print("Invalid input. Please enter valid numbers.")
    
    # Generate dataset using the provided parameters
    X, Y, func_str = generate_dataset(N, x_min, x_max)
    print("\nGenerated function:", func_str)
    
    # Generate and display all visualizations
    print("\nGenerating visualizations...")
    plot_scatter(X, Y, func_str)
    plot_histogram(X)
    plot_box(Y)
    plot_line(X, Y)
    
    print("\nVisualization complete!")

def main():
    """
    Main menu function that provides options to analyze data or exit
    """
    while True:
        print("1. Analyze Climate Data")
        print("2. Exit")
        
        choice = input("Enter your choice (1-2): ")
        
        if choice == "1":
            analyze_climate_data()
        elif choice == "2":
            print("Exiting program. Goodbye!")
            break
        else:
            print("Invalid choice. Please enter 1 or 2.")

if __name__ == "__main__":
    main()