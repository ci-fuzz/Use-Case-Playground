# CI-Fuzz-Playground

This project is a fuzzing playground which aims to show different use cases of fuzzing.

## What is fuzzing (in a nutshell)?

Fuzzing is a dynamic code analysis technique that supplies pseudo-random inputs to a software-under-test (SUT), derives new inputs from the behaviour of the program (i.e. how inputs are processed), and monitors the SUT for bugs.

## Use Cases:

* C_and_C++
  * API Fuzzing
    * Plain
    * Chain
    * Mocking
  * Network Socket Fuzzing
    * Plain
    * Chain (with response parsing, TCP and UDP)
  * (Grammar Fuzzing)
    * JSON
    * XML
    * Custom (if possible)
  * Custom Sanitizer/Custom Vulnerabilities
  * Unit Test Runner?
* Java
  * API Fuzzing
    * Plain
    * Chain
  * Web API Fuzzing
    * REST
      * Sringboot
      * OpenAPI
    * Web
    * gRPC
  * Custom Sanitizer/Custom Vulnerabilities
