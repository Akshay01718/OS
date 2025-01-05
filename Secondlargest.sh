#!/bin/bash

# Function to find the second largest number
second_largest() {
  local numbers=("$@")
  local largest=-999999
  local second_largest=-999999

  # Loop through the numbers
  for num in "${numbers[@]}"; do
    if [ "$num" -gt "$largest" ]; then
      second_largest=$largest
      largest=$num
    elif [ "$num" -gt "$second_largest" ] && [ "$num" -ne "$largest" ]; then
      second_largest=$num
    fi
  done

  echo "$second_largest"
}

# Main program
# Step 2: Read the numbers from the user (space-separated)
read -p "Enter numbers separated by spaces: " -a numbers

# Step 3: Call the second_largest function
result=$(second_largest "${numbers[@]}")

# Step 4: Print the second largest number
echo "The second largest number is: $result"
