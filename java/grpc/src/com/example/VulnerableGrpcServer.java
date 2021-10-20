package com.example;

import helloworld.a.b.c.d.GreeterGrpc;
import helloworld.a.b.c2.d2.GreeterMessages;
import io.grpc.Context;
import io.grpc.Contexts;
import io.grpc.Metadata;
import io.grpc.Server;
import io.grpc.ServerBuilder;
import io.grpc.ServerCall;
import io.grpc.ServerCallHandler;
import io.grpc.ServerInterceptor;
import io.grpc.ServerInterceptors;
import io.grpc.Status;
import io.grpc.protobuf.services.ProtoReflectionService;
import io.grpc.stub.StreamObserver;
import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Objects;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.logging.Logger;

public class GreeterServer {
  private static final Logger logger = Logger.getLogger(GreeterServer.class.getName());

  private Server server;

  /**
   * Main launches the server from the command line.
   */
  public static void main(String[] args) throws IOException, InterruptedException {
    final GreeterServer server = new GreeterServer();
    server.start();
    server.blockUntilShutdown();
  }

  private void start() throws IOException {
    /* The port on which the server should run */
    int port = Integer.parseInt(System.getProperty("server.port"));
    server = ServerBuilder.forPort(port)
                 .addService(ServerInterceptors.intercept(new GreeterImpl(), new AuthInterceptor()))
                 .addService(ProtoReflectionService.newInstance())
                 .build()
                 .start();
    logger.info("Server started, listening on " + port);
    Runtime.getRuntime().addShutdownHook(new Thread() {
      @Override
      public void run() {
        // Use stderr here since the logger may have been reset by its JVM shutdown hook.
        System.err.println("*** shutting down gRPC server since JVM is shutting down");
        try {
          GreeterServer.this.stop();
        } catch (InterruptedException e) {
          e.printStackTrace(System.err);
        }
        System.err.println("*** server shut down");
      }
    });
  }

  private void stop() throws InterruptedException {
    if (server != null) {
      server.shutdown().awaitTermination(30, TimeUnit.SECONDS);
    }
  }

  /**
   * Await termination on the main thread since the grpc library uses daemon threads.
   */
  private void blockUntilShutdown() throws InterruptedException {
    if (server != null) {
      server.awaitTermination();
    }
  }

  static class GreeterImpl extends GreeterGrpc.GreeterImplBase {
    // Compare hashes of access tokens so that the fuzzer cannot pass the checks
    // without knowing the token by using feedback from instrumented compares.
    // SHA-256("let_me_in")
    final static private byte[] ACCESS_TOKEN_HASH = new byte[] {(byte) 0xca, 0x16, 0x70, 0x11,
        (byte) 0xd7, (byte) 0x8e, 0x12, 0x41, 0x51, (byte) 0x8b, (byte) 0xc6, (byte) 0x8e,
        (byte) 0xe5, 0x61, 0x76, (byte) 0xb9, (byte) 0x93, (byte) 0xb7, (byte) 0xf1, (byte) 0x96,
        0x70, (byte) 0x95, (byte) 0xd4, (byte) 0xeb, (byte) 0xe5, (byte) 0xbc, 0x70, (byte) 0xf7,
        0x2f, (byte) 0x89, (byte) 0xf5, 0x6b};

    // SHA-256("backdoor")
    final static private byte[] BACKDOOR_HASH = new byte[] {0x32, 0x78, 0x3c, (byte) 0xef, 0x30,
        (byte) 0xbc, 0x23, (byte) 0xd9, 0x54, (byte) 0x96, 0x23, (byte) 0xaa, 0x48, (byte) 0xaa,
        (byte) 0x85, 0x56, 0x34, 0x6d, 0x78, (byte) 0xbd, 0x3c, (byte) 0xa6, 0x04, (byte) 0xf2,
        0x77, (byte) 0xd6, 0x3d, 0x6e, 0x57, 0x3e, (byte) 0x8c, (byte) 0xe0};

    final static private AtomicBoolean shouldRespondSlowly = new AtomicBoolean(true);

    static private boolean hasAccess(String accessToken) {
      int length = accessToken.length();
      if (length > 5 && length != "let_me_in".length() && length != "backdoor".length()) {
        // This slow input is only caught if the fuzzer also fuzzes "fixed" fields,
        // at least sometimes.
        if (shouldRespondSlowly.getAndSet(false)) {
          try {
            // 3s is longer than the time limit for slow inputs when
            // --request_timeout is set to 20s.
            Thread.sleep(3000);
          } catch (InterruptedException ignored) {
          }
          return false;
        }
      }
      try {
        MessageDigest digest = MessageDigest.getInstance("SHA-256");
        byte[] hash = digest.digest(accessToken.getBytes(StandardCharsets.UTF_8));
        if (MessageDigest.isEqual(hash, BACKDOOR_HASH)) {
          // We plant this bug to verify that the fuzzer can use multiple field
          // hints, e.g. both a valid access token and the backdoor token.
          throw new SecurityException("Found the backdoor");
        }
        return MessageDigest.isEqual(hash, ACCESS_TOKEN_HASH);
      } catch (NoSuchAlgorithmException e) {
        return false;
      }
    }

    @Override
    public void sayHello(GreeterMessages.HelloRequest req,
        StreamObserver<GreeterMessages.HelloReply> responseObserver) {
      if (!hasAccess(req.getAuthentication().getAccessToken())) {
        responseObserver.onCompleted();
        return;
      }
      if (req.getName().equals("larry")) {
        throw new NullPointerException("Found larry");
      }
      GreeterMessages.HelloReply reply =
          GreeterMessages.HelloReply.newBuilder().setMessage("Hello " + req.getName()).build();
      responseObserver.onNext(reply);
      responseObserver.onCompleted();
    }

    @Override
    public void sayBye(
        GreeterMessages.ByeRequest req, StreamObserver<GreeterMessages.ByeReply> responseObserver) {
      // Requires Jazzer's ReflectiveCall sanitizer to be found.
      try {
        Class.forName(req.getMouse()).getConstructor().newInstance();
      } catch (InstantiationException | IllegalAccessException | InvocationTargetException
          | NoSuchMethodException | ClassNotFoundException ignored) {
      }
      GreeterMessages.ByeReply reply =
          GreeterMessages.ByeReply.newBuilder().setMessage("Bye " + req.getMouse()).build();
      responseObserver.onNext(reply);
      responseObserver.onCompleted();
    }
  }

  static class AuthInterceptor implements ServerInterceptor {
    private static final Metadata.Key<String> authorizationKey =
        Metadata.Key.of("Authorization", Metadata.ASCII_STRING_MARSHALLER);

    @Override
    public <ReqT, RespT> ServerCall.Listener<ReqT> interceptCall(
        ServerCall<ReqT, RespT> call, Metadata headers, ServerCallHandler<ReqT, RespT> next) {
      if (!Objects.equals(headers.get(authorizationKey), "Bearer letmein")) {
        call.close(Status.UNAUTHENTICATED.withDescription("some more info"), new Metadata());
        return new ServerCall.Listener() {};
      }
      Context context = Context.current();
      return Contexts.interceptCall(context, call, headers, next);
    }
  }
}
