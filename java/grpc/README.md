# Java-gRPC Fuzzing

## What is gRPC?
gRPC is a modern open source high performance Remote Procedure Call (RPC) framework.

## What is a Java-gRPC application?
That's a java based service that exposes an API using the gRPC framework.

## How Java-gRPC Fuzzing works?
The most commonly used Interface Definition Language of gRPC is Protobuf. Fuzzing is 
targeting the mutation and transmission of protobuffers.  

## How to write fuzz tests for Java-gRPC applications?
It is only necessary to compile the protobuffer description files (.proto) of the target 
application with ci-protoc of Code Intelligence. Everything else is done by CI Fuzz.

```
Usage: ci-protoc STUB_OUT_PATH [--field_hint=name=value] PROTOC_ARGS...
```
## Example vulnerable Java-grpc Service
This project contains a vulnerable grpc server application. Parts of the application are protected by an access token.

The source code of the application can be found in:
* [VulnerableGrpcServer.java](https://github.com/ci-fuzz/CI-Fuzz-Playground/edit/main/java/grpc/src/com/example/VulnerableGrpcServer.java)

There are two protobuf description files defined for the API of the application:
* [greeter_messages.proto](https://github.com/ci-fuzz/CI-Fuzz-Playground/edit/main/java/grpc/proto/greeter_messages.proto)
* [greeter_service.proto](https://github.com/ci-fuzz/CI-Fuzz-Playground/edit/main/java/grpc/proto/greeter_service.proto) 

To compile the Protobuf description files the following parameter can be used:
```
ci-protoc libproto_stub.so -Iproto proto/greeter_service.proto proto/greeter_messages.proto --field_hint=authentication.access_token=let_me_in  --field_hint=authentication.access_token=backdoor
```
In addition to the fuzzing of unauthenticated parts of the application, we set so-called field hints **--field_hint** for the access_token to let the fuzzer also explore authenticated parts of the application.

