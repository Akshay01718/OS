#!/bin/bash

# Function to print Floyd's Triangle
floyds_triangle() {
  rows=$1  # Step 2: Read the number of rows

  echo "Floyd's Triangle:"
  
  for ((i=1; i<=rows; i++))  # Step 3: Iterate i from 1 to rows
  do
    # Step 3.1: Print '*'
    echo -n "* "

    # Step 3.2: Iterate j from 1 to (2*i - 3)
    for ((j=1; j<=(2*i - 3); j++))
    do
      # Step 3.2.1: Print '+'
      echo -n "+ "
    done

    # Step 3.3: If i > 1, print '*'
    if ((i > 1)); then
      echo -n "* "
    fi

    # Move to the next line after completing a row
    echo
  done
}

# Step 1: Start
# Step 4: Read the number of rows from the user
read -p "Enter the number of rows: " rows

# Call the function with the given number of rows
floyds_triangle $rows
