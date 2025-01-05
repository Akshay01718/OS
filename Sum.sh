#!/bin/bash

# Function to calculate the sum of digits
sum_of_digits() {
  local num=$1
  local sum=0
  local digit=0

  # Repeat while num > 0
  while [ "$num" -gt 0 ]; do
    digit=$((num % 10))  # Get the last digit
    sum=$((sum + digit)) # Add the digit to sum
    num=$((num / 10))    # Remove the last digit
  done

  echo $sum
}

# Main program
# Step 2: Read number from user
read -p "Enter a number: " number

# Step 3: Call the function sum_of_digits and store the result
result=$(sum_of_digits "$number")

# Step 4: Print the result
echo "The sum of the digits of $number is: $result"
