#!/bin/bash

# Function to print Floyd's Triangle as a pyramid
floyds_triangle() {
  rows=$1  # Step 2: Read the number of rows

  echo "Floyd's Triangle (Pyramid Shape):"

  for ((i=1; i<=rows; i++))  # Outer loop for rows
  do
    # Print leading spaces for alignment
    for ((space=1; space<=rows-i; space++))
    do
      echo -n "  "
    done

    # Print the first '*'
    echo -n "* "

    # Inner loop to print '+' between '*'
    for ((j=1; j<=(2*i - 3); j++))
    do
      echo -n "+ "
    done

    # Print the last '*' if row > 1
    if ((i > 1)); then
      echo -n "* "
    fi

    # Move to the next line after each row
    echo
  done
}

# Step 1: Start
# Step 4: Read the number of rows from the user
read -p "Enter the number of rows: " rows

# Call the function with the given number of rows
floyds_triangle $rows
