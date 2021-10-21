# Java Fuzzing
Even in a memory-safe language such as Java, potentially harmful bugs like uncaught exceptions or 
denial of service problems are an issue. Writing a parser is particularly hard, because the developer 
needs to think about all edge cases and invalid inputs in addition to handling correct inputs.

At CI Fuzz we distinguish between:

* [Java API Fuzzing](https://github.com/ci-fuzz/CI-Fuzz-Playground/tree/main/java/api_fuzzing) that targets application testing on function-level
* [Java-gRPC Fuzzing](https://github.com/ci-fuzz/CI-Fuzz-Playground/tree/main/java/grpc) that targets application testing of Java services which exposes a gRPC API
* [Java Web App Fuzzing](https://github.com/ci-fuzz/CI-Fuzz-Playground/tree/main/java/grpc) that targets web application testing
