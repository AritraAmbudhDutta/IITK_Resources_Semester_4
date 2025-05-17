# This program processes a string based on a unique registration number
# The processing involves string manipulation techniques such as reversal, vowel capitalization, 
# substring extraction, and sorting operations

def validate_input(n, s):
    """
    Validates the input parameters
    Args:
        n: Integer representing a unique registration number (must be non-negative)
        s: String that must contain only alphabetic characters
    Returns:
        Boolean indicating if inputs are valid
    """
    if n < 0:
        return False
    if type(s) != str or not s.isalpha():  # Ensures s is a non-empty alphabetic string
        return False
    return True

def process_string(n, s):
    """
    Processes the string based on the registration number
    Args:
        n: Unique registration number
        s: Input string to process
    Returns:
        Processed string based on whether n is even or odd
    """
    if not validate_input(n, s):
        return "Invalid input"
    if n % 2 == 0:
        return s[::-1]  # Reverse the string if n is even
    else:
        s = s.lower()
        for x in s:
            if x in "aeiou":  # Capitalize vowels if n is odd
                s = s.replace(x, x.upper())
        return s

def count_set_bits(n):
    """
    Counts the number of set (1) bits in the binary representation of n
    Args:
        n: Integer whose binary representation is to be analyzed
    Returns:
        Count of set bits (1s) in the binary representation of n
    """
    count = 0
    while n:
        count += n & 1  # Check if the least significant bit is 1
        n >>= 1         # Right shift by 1 bit
    return count

def extract_substrings(s, k):
    """
    Extracts all possible substrings of length k from string s
    Args:
        s: Source string
        k: Length of substrings to extract
    Returns:
        List of all possible substrings of length k
    """
    substrings = []
    for i in range(len(s)-k+1):
        substrings.append(s[i:i+k])
    return substrings

def sort_or_reverse(s, n, substrings):
    """
    Either sorts or reverses the list of substrings based on bitwise AND of n and length of s
    Args:
        s: Original string
        n: Registration number
        substrings: List of substrings to be sorted or reversed
    Returns:
        Processed list of substrings
    """
    if (n & len(s)) == 0:  # Bitwise AND operation to determine sorting method
        substrings.sort()   # Sort alphabetically if result is 0
    else:
        substrings = substrings[::-1]  # Reverse the list otherwise
    return substrings

def main():
    """
    Main function that orchestrates the program flow:
    1. Get user inputs
    2. Validate inputs
    3. Process the string based on the registration number
    4. Extract substrings of length equal to the set bits in n
    5. Sort or reverse the substrings
    6. Print the result
    """
    try:
        n = int(input("Enter your Unique Registration Number: "))
    except ValueError:
        print("Invalid input. Please enter a positive integer.")
        return
    if n <= 0:
        print("Invalid input. Please enter a positive integer.")
        return
    s = input("Enter Content String: ")
    if not validate_input(n, s):
        print("Invalid input. Please enter a valid non-empty string containing only letters.")
        return
    s = process_string(n, s)
    k = count_set_bits(n)
    substrings = extract_substrings(s, k)
    substrings = sort_or_reverse(s, n, substrings)
    for s in substrings:
        print(s, end=' ')

if __name__ == "__main__":
    main()