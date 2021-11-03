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
We prepared a vulnerable grpc server application, that you can use to test java-grpc fuzzing.

### Target Server Setup 

For the example we used a fork of the official [java-grpc](https://github.com/grpc/grpc-java) repository and added a vulnerable server example.


To build the vulnerable server you need to clone the source code first and checkout the vulnerable_server branch with the vulnerabilities included. 
```
git clone https://github.com/ci-fuzz/grpc-java
git checkout vulnerable_server
```
Then you can build the server by the following commands.

```
./gradlew installDist
```

The server then can be started by a bash script:

```
./build/install/examples/bin/vulnerable-server
```

The source code of the server application can be found in:
* [VulnerableServer.java](https://github.com/ci-fuzz/grpc-java/blob/vulnerable_server/examples/src/main/java/io/vulnerable/VulnerableServer.java)

### Protocol Buffer Compilation

There is a protobuf description files defining the API of the application:
* [vulnerable_server.proto](https://github.com/ci-fuzz/CI-Fuzz-Playground/edit/main/java/grpc/proto/vulnerable.proto)

Parts of the application are protected by an access token. To compile the Protobuf description file the following command can be used:
```
ci-protoc libproto_stub.so -Iproto proto/vulnerable_server.proto --field_hint=authentication.access_token=let_me_in  --field_hint=authentication.access_token=backdoor
```
In addition to the fuzzing of unauthorized parts of the application, we set so-called field hints **--field_hint** for the access_token to let the fuzzer also explore authorized parts of the application.

### Fuzzing Connection Setup

To instrument the vulnerable server and set up a connection between CI daemon and vulnerable server we need to add a Java Agent to the target application startup.

The easiest way to add the Java Agent to bash script startup we can use JAVA_OPTS, for example:

```
JAVA_OPTS=-javaagent:$HOME/bin/fuzzing_agent_deploy.jar=instrumentation_includes="io.vulnerable.**",service_name=projects/examples-c97ba8d4/web_services/hellowrld ./build/install/examples/bin/vulnerable-server
```

