# Go Fuzzing
Golang was the first programming language to support fuzzing as a first-class experience in version 1.18. This made it really easy for developers to write fuzz tests. Golang 1.14 introduced native compiler instrumentation for libFuzzer, which enables the use of libFuzzer to fuzz Go code. libFuzzer is one of the most advanced and widely used fuzzing engines and provides the most effective method to fuzz Go code.

In this playground we would like to show you the Code Intelligence improved Go fuzzing. Our improved instrumentation enhances libFuzzer with better signals to guide its mutation and thus explore the tested code more effectively. 

For more information, please have a look at our [blog post](https://www.code-intelligence.com/blog/fuzzing-golang-1.19).

* [Go API Fuzzing](https://github.com/ci-fuzz/CI-Fuzz-Playground/tree/main/go/api_fuzzing) that targets application testing on function-level