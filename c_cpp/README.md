# C and C++ Fuzzing
In case of C/C++ applications, CI Fuzz detects and reports memory corruptions, which can originate from programming mistakes in code that employs pointer arithmetics or low level memory operations (such as memcpy, strcpy, ...). These bugs can be exploited to read or even write arbitrary data into the memory, resulting in information leakage (think Heartbleed) or remote code execution.

At CI Fuzz we distinguish between:

* [API Fuzzing](https://github.com/ci-fuzz/CI-Fuzz-Playground/tree/main/c_cpp/api_fuzzing) that targets application testing on function-level
* [Network Socket Fuzzing](https://github.com/ci-fuzz/CI-Fuzz-Playground/tree/main/c_cpp/network_socket) that targets application testing on protocol-level

