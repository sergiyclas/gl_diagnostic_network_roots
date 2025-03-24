#!/bin/bash

TARGET=${1:-example.com}
MAX_HOPS=30
TIMEOUT=1

TARGET_IP=$(getent ahost "$TARGET" | awk '{ print $1 }' | head -n 1)

echo "Running built-in traceroute to $TARGET..."
builtin_output=$(traceroute -I -m $MAX_HOPS "$TARGET")
echo "$builtin_output"

echo "Running custom traceroute to $TARGET..."
custom_output=$(./rooter -m $MAX_HOPS -t $TIMEOUT "$TARGET")
echo "$custom_output"

if echo "$builtin_output" | grep -q "$TARGET" && echo "$custom_output" | grep -q "$TARGET_IP"; then
  echo "Both traceroute tests passed."
else
  echo "One or both traceroute tests failed."
  if ! echo "$builtin_output" | grep -q "$TARGET"; then
    echo "Built-in traceroute test failed."
  fi
  if ! echo "$custom_output" | grep -q "$TARGET_IP"; then
    echo "Custom traceroute test failed."
  fi
  exit 1
fi

echo "All tests completed."
exit 0