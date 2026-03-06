# CS3339_HW2

### Team Members
Jessica Martinez

### How to compile the code
The code can be compiled by using the follow g++ command:

g++ -o fp_overflow_checker fp_overflow_checker.cpp

### How to run the code

./fp_overflow_checker

Example with possible overflow:
./fp_overflow_checker 1e+08 1.0

Example with no overflow:
./fp_overflow_checker 1e+05 2.0
