# Fuzzing Demo with Unit Test

This is a simple cpp demo containing a heap-based buffer overflow. A fuzz test, written for [cifuzz](https://github.com/CodeIntelligenceTesting/cifuzz), is included to trigger the buffer overflow. A unit test is also included.

## To run the unit test
```bash
cmake -S . -B build
cd build
cmake --build .
ctest -R my_unit_test
```

## To run the fuzz test
```bash
cifuzz init
cifuzz run my_fuzz_test
```

