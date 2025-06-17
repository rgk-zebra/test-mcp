# data_processing.py - This file processes a list of numbers but has multiple errors.

def process_numbers(numbers):
    # Initialize variables
    total_sum = 0
    total_product = 1
    
    for num in numbers:
        total_sum += num
        total_product *= num
    
    # Calculate average
    average = total_sum / len(numbers)

    return total_sum, total_product, average

def main():
    # Define a list of numbers
    numbers = [1, 2, 3, 4, 5]
    
    # Process the numbers
    results = process_numbers(numbers)  # Error: 'number' should be 'numbers'
    
    # Print the results
    print("Sum:", results[0])
    print("Product:", results[1])
    print("Average:", results[2])

if __name__ == "__main__":
    main()
