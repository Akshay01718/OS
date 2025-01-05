#!/bin/bash

# Function to check if a number is prime
is_prime() {
  local num=$1
  if [ "$num" -le 1 ]; then
    return 1
  fi
  for ((i = 2; i * i <= num; i++)); do
    if [ $((num % i)) -eq 0 ]; then
      return 1
    fi
  done
  return 0
}

# Input: Lower and Upper limits
read -p "Enter lower limit: " lower
read -p "Enter upper limit: " upper

# Check each number in the range
echo "Prime numbers between $lower and $upper are:"
for ((n = lower; n <= upper; n++)); do
  if is_prime "$n"; then
    echo "$n"
  fi
done
