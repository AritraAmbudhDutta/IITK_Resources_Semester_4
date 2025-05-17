# This program solves a linear system of equations Ax = B
# It uses numpy for matrix operations and linear algebra functions

import numpy as np

def solve_linear_system(N):
    """
    Solves a linear system of equations Ax = B
    
    Args:
        N: Dimension of the square matrix A and vectors B and X
        
    Returns:
        Solution vector X or None if the system can't be solved
    """
    # Create empty matrix A of size N×N
    matrix_A = np.empty([N, N], dtype=float)
    
    # Get matrix A elements from user
    print("Enter the elements of the matrix A row-wise:")
    for i in range(N):
        for j in range(N):
            while True:
                try:
                    matrix_A[i][j] = float(input(f"Enter element [{i+1}][{j+1}]: "))
                    break
                except ValueError:
                    print("Invalid input. Please enter a number.")
    
    # Create empty vector B of size N
    vector_B = np.empty(N, dtype=float)
    
    # Get vector B elements from user
    print("Enter the elements of the Vector B:")
    for i in range(N):
        while True:
            try:
                vector_B[i] = float(input(f"Enter element [{i+1}]: "))
                break
            except ValueError:
                print("Invalid input. Please enter a number.")
                
    # Solve the linear system using matrix inversion
    try:
        matrix_A_inv = np.linalg.inv(matrix_A)  # Calculate inverse of A
    except np.linalg.LinAlgError:
        print("Matrix A is singular and cannot be inverted.")
        return None
        
    # Calculate solution vector X = A^(-1) * B
    return np.dot(matrix_A_inv, vector_B)

def main():
    """
    Main function that:
    1. Gets dimension of the linear system
    2. Gets matrix A and vector B from user
    3. Solves the system and displays the result
    """
    try:
        N = int(input("Enter the Dimension of the Square Matrix: "))
    except ValueError:
        print("Invalid input. Please enter a positive integer.")
        return
    if N <= 0:
        print("Number of Dimension must be positive.")
        return
        
    vector_X = solve_linear_system(N)
    
    if vector_X is not None:
        print("The solution vector X is:")
        print(vector_X)

if __name__ == "__main__":
    main()
