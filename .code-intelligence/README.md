# Use Case Playground

Welcome to the Use Case Playground! This project allows you to learn and explore fuzzing for various use cases and technologies.

## What is fuzzing (in a nutshell)?

Fuzzing is a dynamic code analysis technique that supplies pseudo-random inputs to a software-under-test (SUT), derives new inputs from the behaviour of the program (i.e. how inputs are processed), and monitors the SUT for bugs.

## How does this playground work?

1.	Take a look at the fuzzing playground on [app.code-intelligence.com](https://app.code-intelligence.com), look at the findings and the projects that trigger them. We have examples for both c and c++ (API and network socket) as well as Java (API and Web).

2.	Request early access to dive into this [Playground](github.com/ci-fuzz/Use-Case-Playground) to understand the code that causes the findings and the fuzz tests that are used to catch them.

3.	Check out our resources and further reading to understand more about fuzzing or to take the next steps and fuzz your code – either with [Jazzer](github.com/CodeIntelligenceTesting/jazzer) or with a full-blown CI Fuzz version.

## Use Cases:

* [C and C++](https://github.com/ci-fuzz/Use-Case-Playground/tree/main/c_cpp)
  * [API Fuzzing (Plain, Chain, Mocking)](https://github.com/ci-fuzz/Use-Case-Playground/tree/main/c_cpp/api_fuzzing)
  * [Network Socket Fuzzing (Plain, Chain)](https://github.com/ci-fuzz/Use-Case-Playground/tree/main/c_cpp/network_socket/tcp_server)
* [Java](https://github.com/ci-fuzz/Use-Case-Playground/tree/main/java)
  * [API Fuzzing (Plain, Chain)](https://github.com/ci-fuzz/Use-Case-Playground/tree/main/java/api_fuzzing)
  * [Web App Fuzzing (REST, Web)](https://github.com/ci-fuzz/Use-Case-Playground/tree/main/java/webapp)
  * [gRPC](https://github.com/ci-fuzz/Use-Case-Playground/tree/main/java/grpc)
