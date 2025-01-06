# @file shell_testing.sh
# @author Brice Anders Evans
# @brief testing for main.c
# @version 0.1
# @date 2025-01-06
# 
# @copyright Copyright (c) 2024

#!/bin/bash


# Variables
SHELL_EXECUTABLE="./shell"           # Path to shell program
TEST_INPUT="test_input.txt"          # File containing test commands
EXPECTED_OUTPUT="expected_output.txt" # File containing expected output
ACTUAL_OUTPUT="actual_output.txt"    # File to store actual output
# Done due to comments causing tests to fail previously when otherwise they would pass
CLEAN_EXPECTED="clean_expected.txt"  # Cleaned expected output (removes comments)
CLEAN_ACTUAL="clean_actual.txt"      # Cleaned actual output (removes comments)

# Test input file
cat <<EOL > $TEST_INPUT
pwd
echo Hello, World!
cd /
pwd
echo Testing shell
exit
EOL

# Run the shell program with the test input
$SHELL_EXECUTABLE < $TEST_INPUT > $ACTUAL_OUTPUT

# Remove comments (lines starting with '#') from expected and actual output
grep -v '^#' $EXPECTED_OUTPUT > $CLEAN_EXPECTED
grep -v '^#' $ACTUAL_OUTPUT > $CLEAN_ACTUAL

# Compare cleaned outputs
if diff $CLEAN_EXPECTED $CLEAN_ACTUAL > /dev/null; then
    echo "All tests passed!"
else
    echo "Test failed. Differences:"
    diff $CLEAN_EXPECTED $CLEAN_ACTUAL
fi

# Clean up (Optional)
rm $TEST_INPUT $ACTUAL_OUTPUT $EXPECTED_OUTPUT $CLEAN_EXPECTED $CLEAN_ACTUAL
