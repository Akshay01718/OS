#!/bin/bash

# Function to generate the Fibonacci series
fibonacci() {
  local limit=$1
  local a=0
  local b=1
  local next

  echo "Fibonacci series up to $limit:"
  echo -n "$a $b"

  while [ $((a + b)) -le $limit ]; do
    next=$((a + b))
    echo -n " $next"
    a=$b
    b=$next
  done
  echo
}

# Main program
# Step 2: Read the limit from the user
read -p "Enter the limit for the Fibonacci series: " limit

# Step 3: Call the Fibonacci function
fibonacci "$limit"
