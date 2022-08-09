# Fuzzing Demo with Unit Test

This is a simple cpp demo containing a heap-based buffer overflow. A fuzz test, written for [cifuzz](https://github.com/CodeIntelligenceTesting/cifuzz), is included to trigger the buffer overflow. Two unit tests are also included, one ctest and one gtest.

## To run the unit tests
```bash
cmake -S . -B build
cd build
cmake --build .
ctest
```

## To run the fuzz test
```bash
cifuzz init
cifuzz run my_fuzz_test
```

