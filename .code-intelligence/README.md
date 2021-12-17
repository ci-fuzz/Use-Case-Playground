![Flowchart](https://raw.githubusercontent.com/ci-fuzz/Use-Case-Playground/main/.code-intelligence/Entwurf.png "Flowchart")

# Use Case Playground

Welcome to the Use Case Playground! This project allows you to learn and explore fuzzing for various use cases and technologies.

## What is fuzzing?

Fuzzing is a dynamic code analysis technique that supplies pseudo-random inputs to a software-under-test (SUT), derives new inputs from the behaviour of the program (i.e. how inputs are processed), and monitors the SUT for bugs.

Check out our [resources](https://help.code-intelligence.com/getting-started) and [further reading](https://www.code-intelligence.com/blog/fuzzing-101-the-basics) to understand more about fuzzing or to take the next steps and fuzz your code – either with [Jazzer](https://github.com/CodeIntelligenceTesting/jazzer) or with a full-blown CI Fuzz version.

## Where can you use fuzzing?

* [C and C++](https://github.com/ci-fuzz/Use-Case-Playground/tree/main/c_cpp)
  * [API Fuzzing (Plain, Chain, Mocking)](https://github.com/ci-fuzz/Use-Case-Playground/tree/main/c_cpp/api_fuzzing)
  * [Network Socket Fuzzing (Plain, Chain)](https://github.com/ci-fuzz/Use-Case-Playground/tree/main/c_cpp/network_socket/tcp_server)
* [Java](https://github.com/ci-fuzz/Use-Case-Playground/tree/main/java)
  * [API Fuzzing (Plain, Chain)](https://github.com/ci-fuzz/Use-Case-Playground/tree/main/java/api_fuzzing)
  * [Web App Fuzzing (REST, Web)](https://github.com/ci-fuzz/Use-Case-Playground/tree/main/java/webapp)
  * [gRPC](https://github.com/ci-fuzz/Use-Case-Playground/tree/main/java/grpc)
