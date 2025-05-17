# This program calculates the sum of the first n prime numbers
# It uses the Sieve of Eratosthenes algorithm to efficiently find prime numbers

import math

def find_primes(n):
    """
    Finds and sums the first n prime numbers using the Sieve of Eratosthenes algorithm
    
    Args:
        n: Number of prime numbers to find
        
    Returns:
        Sum of the first n prime numbers
        
    Note:
        Uses the Prime Number Theorem to estimate an upper bound for the nth prime
    """
    # Estimate the upper bound for the nth prime using the Prime Number Theorem
    if n < 6:
        limit = 15  # Small hardcoded limit for small values of n
    else:
        # Prime Number Theorem: nth prime is approximately n*ln(n) + n*ln(ln(n))
        limit = int(n*(math.log(n) + math.log(math.log(n))))
    
    primes = []
    sieve = [True] * (limit + 1)  # Initialize sieve with all numbers potentially prime
    sieve[0:2] = [False, False]   # 0 and 1 are not prime
    
    for i in range(2, limit+1):
        if sieve[i]:  # If i is still marked as prime
            primes.append(i)
            # Mark all multiples of i as non-prime
            for j in range(i*i, limit+1, i):
                sieve[j] = False
        if len(primes) == n:
            break  # Stop once we've found n primes
            
    return sum(primes)  # Return the sum of the first n primes

def main():
    """
    Main function that:
    1. Gets user input for the number of primes to sum
    2. Validates input
    3. Calculates and displays the sum of primes
    """
    try:
        n = int(input("Enter the number of primes you want to sum: "))
    except ValueError:
        print("Invalid input. Please enter a positive integer.")
        return
    if n <= 0:
        print("Number of primes must be positive.")
        return
    
    result = find_primes(n)
    print(f"The sum of the first {n} prime numbers is: {result}")

if __name__ == "__main__":
    main()
