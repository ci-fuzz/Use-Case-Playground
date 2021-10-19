docker run -p 80:8888 -p 8080:8080 -p 9090:9090 -e TZ=Europe/Amsterdam -v /opt/ci-fuzz-2.23.0/lib/code-intelligence:/cibin webgoat_instrumented
