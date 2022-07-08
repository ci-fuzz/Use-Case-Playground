# CI-Fuzz-Playground

Welcome to the CI-Fuzz Playground! This project has been created by Code Intelligence to allow you to learn and explore fuzzing for various use cases and technologies.

## What is fuzzing (in a nutshell)?

Fuzzing is a dynamic code analysis technique that supplies pseudo-random inputs to a software-under-test (SUT), derives new inputs from the behaviour of the program (i.e. how inputs are processed), and monitors the SUT for bugs.

## How does this playground work?

1.	Take a look at the fuzzing playground on [app.code-intelligence.com](https://app.code-intelligence.com), look at the findings and the projects that trigger them. We have examples for C/C+ (API and network socket), Java (API and Web) and Go (API).

2.	Request early access to dive into this [Playground](github.com/ci-fuzz/CI-Fuzz-Playground) to understand the code that causes the findings and the fuzz tests that are used to catch them.

3.	Check out our resources and further reading to understand more about fuzzing or to take the next steps and fuzz your code – either with [Jazzer](github.com/CodeIntelligenceTesting/jazzer) or with a full-blown CI Fuzz version.


## Use Cases:

* [C and C++](https://github.com/ci-fuzz/CI-Fuzz-Playground/tree/main/c_cpp)
  * [API Fuzzing (Plain, Chain, Mocking)](https://github.com/ci-fuzz/CI-Fuzz-Playground/tree/main/c_cpp/api_fuzzing)
  * [Network Socket Fuzzing (Plain, Chain)](https://github.com/ci-fuzz/CI-Fuzz-Playground/tree/main/c_cpp/network_socket/tcp_server)
  <!--- * [Grammar Fuzzing (JSON, XML, Custom)](https://github.com/ci-fuzz/CI-Fuzz-Playground/tree/main/c_cpp)
  * [Custom Sanitizer/Custom Vulnerabilities](https://github.com/ci-fuzz/CI-Fuzz-Playground/tree/main/c_cpp)
  * [Unit Test Runner?](https://github.com/ci-fuzz/CI-Fuzz-Playground/tree/main/c_cpp) -->
* [Java](https://github.com/ci-fuzz/CI-Fuzz-Playground/tree/main/java)
  * [API Fuzzing (Plain, Chain)](https://github.com/ci-fuzz/CI-Fuzz-Playground/tree/main/java/api_fuzzing)
  * [Web App Fuzzing (REST, Web)](https://github.com/ci-fuzz/CI-Fuzz-Playground/tree/main/java/webapp)
  * [gRPC](https://github.com/ci-fuzz/CI-Fuzz-Playground/tree/main/java/grpc)
  <!---* [Custom Sanitizer/Custom Vulnerabilities](https://github.com/ci-fuzz/CI-Fuzz-Playground/tree/main/java) -->

* [Go](https://github.com/ci-fuzz/CI-Fuzz-Playground/tree/main/go)
  * [Go Fuzzing (Plain)](https://github.com/ci-fuzz/CI-Fuzz-Playground/tree/main/go/api_fuzzing)

## Other Resources:
[Code Intelligence Knowledge Base](https://help.code-intelligence.com/)
